#include "GUIMyFrame1.h"
#include <fstream>
#include <stdlib.h>
#include "vecmat.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/mat.hpp>

#if defined(__WXMSW__)
#ifdef wxHAVE_RAW_BITMAP
#include "wx/rawbmp.h"
#endif
#endif

#include "wx/image.h"
#include "wx/graphics.h"

#include <iostream>
//#include <stdio.h>
#include <string>
#include <stdlib.h>

#define PI 3.14159265

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
    wxImage original = wxImage(m_panel1->GetSize());
    wxImage shifted = wxImage(m_panel1->GetSize());
    wxImage copy = wxImage(m_panel1->GetSize());
    wxImage mask = wxImage(m_panel1->GetSize());

    curr_x = 0;
    curr_y = 0;

    count_scrollBar->SetScrollbar(0, 0, 20, 1, true);
    angle_scrollBar->SetScrollbar(0, 1, 360, 1, true);
    x_scrollBar->SetScrollbar(100, 1, 201, 1, true);
    y_scrollBar->SetScrollbar(100, 1, 201, 1, true);
}

void GUIMyFrame1::OpenFile( wxCommandEvent& event )
{

    /*if (...current content has not been saved...)
    {
        if (wxMessageBox(_("Current content has not been saved! Proceed?"), _("Please confirm"),
            wxICON_QUESTION | wxYES_NO, this) == wxNO)
            return;
        //else: proceed asking to the user the new file to open
    }*/

    wxFileDialog openFileDialog(this, _("Open XYZ file"), "", "", "JPEG files (*.jpg)|*.jpg|PNG files (*.png)|*.png", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL) return;

    wxFileInputStream input_stream(openFileDialog.GetPath());
    if (!input_stream.IsOk())
    {
        wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
        return;
    }

    // Load the image
    wxImage newImage;
    newImage.LoadFile(openFileDialog.GetPath());

    // Load/Create a circular mask
    this->mask.LoadFile("mask.png");
    //CreateMask();

    // Resizing the image to square (initial image does not have to be square, but it will be cropped)
    int size = newImage.GetSize().x > newImage.GetSize().y ? newImage.GetSize().y : newImage.GetSize().x;
    newImage.Resize(wxSize(size, size), wxPoint(0, 0));
    newImage.Rescale(this->m_panel1->GetSize().x, this->m_panel1->GetSize().x);
    this->mask.Rescale(this->m_panel1->GetSize().x, this->m_panel1->GetSize().x);

    // Connecting images to the class
     
    //newImage.SetMaskFromImage(newMask, 0, 0, 0);

    this->original = newImage;
    this->shifted = this->original.Copy();
    this->copy = this->shifted.Copy();

    Extend();

    Repaint();
}

void GUIMyFrame1::Revert( wxCommandEvent& event )
{
    // This is a complete reset of labels, scrollbar values , and xy coordinates of a shifted image

    this->countval_staticText->SetLabel("0");
    this->angleval_staticText->SetLabel("0");
    this->xval_staticText->SetLabel("0%");
    this->yval_staticText->SetLabel("0%");

    curr_x = 0;
    curr_y = 0;

    count_scrollBar->SetScrollbar(0, 0, 20, 1, true);
    angle_scrollBar->SetScrollbar(0, 1, 360, 1, true);
    x_scrollBar->SetScrollbar(100, 1, 201, 1, true);
    y_scrollBar->SetScrollbar(100, 1, 201, 1, true);

    this->copy = this->original.Copy();
    Repaint();
}

void GUIMyFrame1::Recount_Axes( wxScrollEvent& event )
{
    // Function for changing axes count

    int new_val = this->count_scrollBar->GetThumbPosition();
    this->countval_staticText->SetLabel(std::to_string(new_val));

    this->axes_angle = new_val == 0 ? 0 : 180 / new_val;
    this->axes_count = new_val;

    for (int i = 0; i < axes_count; i++) {
        Reflect(angle + this->axes_angle * i);
    }

    Repaint();
}

void GUIMyFrame1::Change_Angle( wxScrollEvent& event )
{
    // Function for changing angle

    int new_val = this->angle_scrollBar->GetThumbPosition();
    this->angleval_staticText->SetLabel(std::to_string(new_val));

    this->angle = new_val;
    this->copy = this->shifted.Copy();

    for (int i = 0; i < axes_count; i++) {
        Reflect(angle + this->axes_angle*i);
    }

    Repaint();
}

void GUIMyFrame1::Move_X(wxScrollEvent& event)
{
    // Function for moving/shifting along the x axis

    int new_val = this->x_scrollBar->GetThumbPosition() - 100;
    std::string new_string = std::to_string(new_val) + "%";
    this->xval_staticText->SetLabel(new_string);

    curr_x = (this->shifted.GetHeight() / 100) * new_val;

    wxBitmap tmpbmp = wxBitmap(this->shifted);
    wxBitmap bmpext = wxBitmap(this->extended);
    wxMemoryDC mem2(bmpext);
    wxMemoryDC mem1(tmpbmp);
    mem1.Blit(0, 0, this->shifted.GetWidth(), this->shifted.GetHeight(), &mem2, this->shifted.GetWidth() + curr_x, this->shifted.GetHeight() + curr_y);
    mem1.SelectObject(wxNullBitmap);

    this->shifted = tmpbmp.ConvertToImage();
    this->copy = this->shifted.Copy();

    Repaint();
}

void GUIMyFrame1::Move_Y(wxScrollEvent& event)
{
    // Function for moving/shifting along the y axis

    int new_val = this->y_scrollBar->GetThumbPosition() - 100;
    std::string new_string = std::to_string(new_val) + "%";
    this->yval_staticText->SetLabel(new_string);

    curr_y = (this->shifted.GetHeight() / 100) * new_val;

    wxBitmap tmpbmp = wxBitmap(this->shifted);
    wxBitmap bmpext = wxBitmap(this->extended);
    wxMemoryDC mem2(bmpext);
    wxMemoryDC mem1(tmpbmp);
    mem1.Blit(0, 0, this->shifted.GetWidth(), this->shifted.GetHeight(), &mem2, this->shifted.GetWidth() + curr_x, this->shifted.GetHeight() + curr_y);
    mem1.SelectObject(wxNullBitmap);

    this->shifted = tmpbmp.ConvertToImage();
    this->copy = this->shifted.Copy();

    Repaint();
}

void GUIMyFrame1::Interpolate( wxCommandEvent& event )
{
// TODO: Implement Interpolate
    this->extended.SaveFile("lol.png", wxBITMAP_TYPE_PNG);
}

void GUIMyFrame1::SaveFile( wxCommandEvent& event )
{
    // Function for saving the current image on the screen

    wxFileDialog saveFileDialog(this, _("Save file"), "", "", "PNG files (*.png)|*.png | BITMAP files (*. bmp)|*.bmp", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL) return;
    int tmp = saveFileDialog.GetFilterIndex();
    wxString name = saveFileDialog.GetFilename();
    switch (tmp) {
    case 0:
        this->copy.SaveFile(name, wxBITMAP_TYPE_PNG);
        break;
    case 1:
        this->copy.SaveFile(name, wxBITMAP_TYPE_BMP);
        break;
    }
}

void GUIMyFrame1::Animate( wxCommandEvent& event )
{
    // Function for animation
    this->angle = 0;

    for (int i = 0; i < 721; i++) {
        this->copy = this->shifted.Copy();

        for (int i = 0; i < axes_count; i++) {
            Reflect(angle + this->axes_angle*i);
        }
        Repaint();

        this->angle += 1;

        // Animation speed regulation
        Sleep(20);
    }
}

void GUIMyFrame1::Repaint() {
    // Function for graphic output

    wxClientDC dc1(this->m_panel1);
    wxBufferedDC dc(&dc1);

    int width = this->copy.GetWidth(),
        height = this->copy.GetHeight();
    
    this->copy.SetMaskFromImage(this->mask, 0, 0, 0);
    dc.DrawBitmap(wxBitmap(this->copy), wxPoint(0, 0));

    // FOR TESTING. NO RELATION TO THE FINAL VERSION

    //dc.DrawLine(width / 2, 0, width / 2, height);
    //dc.DrawLine(width, height / 2, 0, height / 2);
    //dc.DrawLine(testing_variable1.GetX(), testing_variable1.GetY(), testing_variable2.GetX(), testing_variable2.GetY());
    //dc.DrawLine(testing_variable2.GetX(), testing_variable2.GetY(), testing_variable3.GetX(), testing_variable3.GetY());
    //dc.DrawLine(testing_variable3.GetX(), testing_variable3.GetY(), testing_variable4.GetX(), testing_variable4.GetY());
    //dc.DrawLine(testing_variable4.GetX(), testing_variable4.GetY(), testing_variable1.GetX(), testing_variable1.GetY());

    //dc.SetBrush(*wxWHITE_BRUSH);
    //dc.DrawText(std::to_string(test_var), 50, 50);
}

void GUIMyFrame1::Reflect(int angle) {
    // Function for finding the reflection of an image along the axis that goes through the center of an image under certain angle 
    
    angle %= 360;
    wxImage tmp_cpy = this->copy.Copy();

    unsigned char* to = this->copy.GetData();
    unsigned char* from = tmp_cpy.GetData();

    int size_x = this->copy.GetWidth(),
        size_y = this->copy.GetHeight();

    int bytes_per_pixel = this->copy.HasAlpha() ? 4 : 3;

    //if (sizeof(to) / sizeof(to[0]) < size_x * size_y * bytes_per_pixel) return;

    double a = tan((-angle + 90) * PI / 180);
    double counter_a = tan((-angle) * PI / 180);

    Matrix reflect;

    reflect.data[0][0] = (1 - a*a)/(1 + a*a);
    reflect.data[0][1] = 2*a / (1 + a * a);
    reflect.data[1][0] = 2*a / (1 + a * a);
    reflect.data[1][1] = (a*a - 1) / (1 + a * a);

    Matrix matrix = get_translation_matrix(+size_x / 2, +size_y / 2) * reflect * get_translation_matrix(-size_x / 2, -size_y / 2);
    Vector vector;

    // I have no idea why or how this works. PLEASE DO NOT TOUCH
    for (int y = 0; y < size_y; y+=1) {
        for (int x = 0; x < size_x; x++) {

            vector.Set(x, y);
            vector = matrix * vector;

            int new_x = vector.GetX();
            int new_y = vector.GetY();

            if (angle % 180 == 0 ? angle  == 0 ? x < size_x / 2 : x > size_x / 2 : angle < 180 ? (a * (x - size_x / 2) + size_y / 2 - y) < 0 : (a * (x - size_x / 2) + size_y / 2 - y) > 0) {
                if ((new_y * size_x * 3 + bytes_per_pixel * new_x > 0) && (new_y * size_x * 3 + bytes_per_pixel * new_x + 2 < size_x * size_y * 3)) {
                    //tmp_cpy.Paste(copy, x, y);
                    to[y * size_x * 3 + bytes_per_pixel * x + 0] = from[new_y * size_x * 3 + bytes_per_pixel * new_x + 0];
                    to[y * size_x * 3 + bytes_per_pixel * x + 1] = from[new_y * size_x * 3 + bytes_per_pixel * new_x + 1];
                    to[y * size_x * 3 + bytes_per_pixel * x + 2] = from[new_y * size_x * 3 + bytes_per_pixel * new_x + 2];
                }
                //else {
                //    to[y * size_x * 3 + bytes_per_pixel * x + 0] = 0;
                //    to[y * size_x * 3 + bytes_per_pixel * x + 1] = 0;
                //    to[y * size_x * 3 + bytes_per_pixel * x + 2] = 0;
                //}
            }
        }
    }
}

void GUIMyFrame1::Extend() {
    // Function for finding the extended version of the image. Needed for moving/shifting the original image along the xy axes

    int size_x = this->copy.GetWidth(),
        size_y = this->copy.GetHeight();

    wxBitmap* TempBMP = new wxBitmap(size_x*3, size_y*3);

    {
        wxMemoryDC extender(*TempBMP);
        extender.SetBackground(*wxWHITE_BRUSH);
        extender.Clear();

        extender.DrawBitmap(copy, size_x, size_y);
        extender.DrawBitmap(copy.Mirror(false), size_x, 0);
        extender.DrawBitmap(copy.Mirror(false), size_x, size_x*2);
        extender.DrawBitmap(copy.Mirror(), 0, size_y);
        extender.DrawBitmap(copy.Mirror(), size_x*2, size_y);

        extender.DrawBitmap(copy.Rotate180(), 0, 0);
        extender.DrawBitmap(copy.Rotate180(), size_x*2, 0);
        extender.DrawBitmap(copy.Rotate180(), 0, size_y*2);
        extender.DrawBitmap(copy.Rotate180(), size_x*2, size_y*2);
    }

    extended = (*TempBMP).ConvertToImage();
    delete TempBMP;
}

void GUIMyFrame1::CreateMask() {
    // Image for creating a circular mask
    // DOES NOT WORK

    wxBitmap maskbmp = wxBitmap(copy.GetWidth(), copy.GetHeight());
    wxMemoryDC memdc(maskbmp);

    memdc.SetBackground(*wxWHITE_BRUSH);
    memdc.SetBrush(*wxBLACK_BRUSH);
    memdc.DrawCircle(this->copy.GetWidth() / 2, this->copy.GetHeight() / 2, this->copy.GetWidth() / 2);

    memdc.SelectObject(wxNullBitmap);


    mask = maskbmp.ConvertToImage();

    mask.Rescale(this->copy.GetWidth(), this->copy.GetHeight());  // This line is ignored for some reason
}