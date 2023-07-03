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

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
    wxImage original = wxImage(m_panel1->GetSize());
    wxImage copy = wxImage(m_panel1->GetSize());

    int axes_count = 0;
    std::vector<int> axes;


    count_scrollBar->SetScrollbar(0, 1, 20, 1, true);
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

    wxFileDialog openFileDialog(this, _("Open XYZ file"), "", "", "JPEG files (*.jpg)|*.jpg", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL) return;

    // proceed loading the file chosen by the user;
    // this can be done with e.g. wxWidgets input streams:
    wxFileInputStream input_stream(openFileDialog.GetPath());
    if (!input_stream.IsOk())
    {
        wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
        return;
    }

    wxImage newImage;
    newImage.LoadFile(openFileDialog.GetPath());

    int size = newImage.GetSize().x > newImage.GetSize().y ? newImage.GetSize().y : newImage.GetSize().x;
    newImage.Resize(wxSize(size, size), wxPoint(0, 0));
    newImage.Rescale(this->m_panel1->GetSize().x, this->m_panel1->GetSize().y);
    wxImage outputImage = newImage;


    //przyk³ad ze interpolacja dzia³a ale jak j¹ wykorzystaæ to nie wiem xd
    //interpolatory nie s¹ jeszcze podpiête pod nic, tylko s¹ zrobione na 'sztywno'
     
 
   // wxImage outputImage = BilinearInterpolation(newImage, 1000, 1000);
   // wxImage outputImage = NearestNeighborInterpolation(newImage, 1000, 1000);

    this->original = outputImage;
    this->copy = this->original.Copy();




    Repaint();
}

void GUIMyFrame1::Revert( wxCommandEvent& event )
{
    this->copy = this->original.Copy();
    Repaint();
}

void GUIMyFrame1::Recount_Axes( wxScrollEvent& event )
{
    int new_val = this->count_scrollBar->GetThumbPosition() + 1;
    this->countval_staticText->SetLabel(std::to_string(new_val));
// TODO: Implement Recount_Axes
}

void GUIMyFrame1::Change_Angle( wxScrollEvent& event )
{
    int new_val = this->angle_scrollBar->GetThumbPosition();
    this->angleval_staticText->SetLabel(std::to_string(new_val));
// TODO: Implement Change_Angle
}

void GUIMyFrame1::Move_X( wxScrollEvent& event )
{
    int new_val = this->x_scrollBar->GetThumbPosition() - 100;
    std::string new_string = std::to_string(new_val) + "%";
    this->xval_staticText->SetLabel(new_string);
// TODO: Implement Move_X
}

void GUIMyFrame1::Move_Y( wxScrollEvent& event )
{
    int new_val = this->y_scrollBar->GetThumbPosition() - 100;
    std::string new_string = std::to_string(new_val) + "%";
    this->yval_staticText->SetLabel(new_string);
// TODO: Implement Move_Y
}

void GUIMyFrame1::Interpolate( wxCommandEvent& event )
{
// TODO: Implement Interpolate

}


wxImage GUIMyFrame1::NearestNeighborInterpolation(const wxImage& inputImage, int newWidth, int newHeight)
{
    int oldWidth = inputImage.GetWidth();
    int oldHeight = inputImage.GetHeight();

    wxImage outputImage(newWidth, newHeight);

    double widthRatio = static_cast<double>(oldWidth) / newWidth;
    double heightRatio = static_cast<double>(oldHeight) / newHeight;

    for (int y = 0; y < newHeight; ++y)
    {
        for (int x = 0; x < newWidth; ++x)
        {
            int oldX = static_cast<int>(x * widthRatio);
            int oldY = static_cast<int>(y * heightRatio);

            wxColor pixelColor(inputImage.GetRed(oldX, oldY),
                inputImage.GetGreen(oldX, oldY),
                inputImage.GetBlue(oldX, oldY));

            outputImage.SetRGB(x, y, pixelColor.Red(), pixelColor.Green(), pixelColor.Blue());
        }
    }

    return outputImage;
}


wxImage GUIMyFrame1::BilinearInterpolation(const wxImage& image, float newWidth, float newHeight) {
    wxImage newImage(newWidth, newHeight);

    for (int y = 0; y < newHeight; y++)
    {
        for (int x = 0; x < newWidth; x++)
        {
            // Wspó³rzêdne piksela w oryginalnym obrazie
            double srcX = (double)x / newWidth * (image.GetWidth() - 1);
            double srcY = (double)y / newHeight * (image.GetHeight() - 1);

            // Indeksy czterech s¹siaduj¹cych pikseli
            int x1 = (int)srcX;
            int y1 = (int)srcY;
            int x2 = x1 + 1;
            int y2 = y1 + 1;

            // Wspó³czynniki interpolacji
            double dx = srcX - x1;
            double dy = srcY - y1;

            // Wartoœci pikseli s¹siaduj¹cych
           /* wxColour c11[3] = {image.GetRed(x1,y1),image.GetGreen(x1,y1),image.GetBlue(x1,y1)};
            wxColour c12[3] = { image.GetRed(x1,y2),image.GetGreen(x1,y2),image.GetBlue(x1,y2) };
            wxColour c21[3] = { image.GetRed(x2,y1),image.GetGreen(x2,y1),image.GetBlue(x2,y1) };
            wxColour c22[3] = { image.GetRed(x2,y2),image.GetGreen(x2,y2),image.GetBlue(x2,y2) };

            // Interpolacja dla ka¿dego kana³u koloru
            unsigned char red = (1 - dx) * (1 - dy) * c11[0].Red() + dx * (1 - dy) * c21[0].Red() +
                (1 - dx) * dy * c12[0].Red() + dx * dy * c22[0].Red();
            unsigned char green = (1 - dx) * (1 - dy) * c11[1].Green() + dx * (1 - dy) * c21[1].Green() +
                (1 - dx) * dy * c12[1].Green() + dx * dy * c22[1].Green();
            unsigned char blue = (1 - dx) * (1 - dy) * c11[2].Blue() + dx * (1 - dy) * c21[2].Blue() +
                (1 - dx) * dy * c12[2].Blue() + dx * dy * c22[2].Blue();
                */


            const unsigned char* data = image.GetData();
            int bytesPerPixel = image.HasAlpha() ? 4 : 3;

            int offset11 = (y1 * image.GetWidth() + x1) * bytesPerPixel;
            int offset12 = (y2 * image.GetWidth() + x1) * bytesPerPixel;
            int offset21 = (y1 * image.GetWidth() + x2) * bytesPerPixel;
            int offset22 = (y2 * image.GetWidth() + x2) * bytesPerPixel;

            unsigned char red11 = data[offset11];
            unsigned char green11 = data[offset11 + 1];
            unsigned char blue11 = data[offset11 + 2];

            unsigned char red12 = data[offset12];
            unsigned char green12 = data[offset12 + 1];
            unsigned char blue12 = data[offset12 + 2];

            unsigned char red21 = data[offset21];
            unsigned char green21 = data[offset21 + 1];
            unsigned char blue21 = data[offset21 + 2];

            unsigned char red22 = data[offset22];
            unsigned char green22 = data[offset22 + 1];
            unsigned char blue22 = data[offset22 + 2];

            // Interpolacja dla ka¿dego kana³u koloru
            unsigned char red = (1 - dx) * (1 - dy) * red11 + dx * (1 - dy) * red21 +
                (1 - dx) * dy * red12 + dx * dy * red22;
            unsigned char green = (1 - dx) * (1 - dy) * green11 + dx * (1 - dy) * green21 +
                (1 - dx) * dy * green12 + dx * dy * green22;
            unsigned char blue = (1 - dx) * (1 - dy) * blue11 + dx * (1 - dy) * blue21 +
                (1 - dx) * dy * blue12 + dx * dy * blue22;

            // Ustawienie koloru piksela w nowym obrazie
            newImage.SetRGB(x, y, red, green, blue);
        }
    }

    return newImage;
}




void GUIMyFrame1::SaveFile( wxCommandEvent& event )
{
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
// TODO: Implement Animate
}

void GUIMyFrame1::Repaint() {
    wxClientDC dc1(this->m_panel1);
    wxBufferedDC dc(&dc1);

    dc.DrawBitmap(wxBitmap(this->copy), wxPoint(0, 0));
}

/*void GUIMyFrame1::Reflect(double angle) {
    wxImage tmp_cpy = this->copy.Copy();

    unsigned char* to = this->copy.GetData();
    unsigned char* from = tmp_cpy.GetData();

    double a = tan(angle);
    int size_x = tmp_cpy.GetWidth(),
        size_y = tmp_cpy.GetHeight();

    size_t size = tmp_cpy.GetWidth() * tmp_cpy.GetHeight();

    Matrix matrix = get_mreflection_matrix(angle);
   // this->check = size;

    for (int i = 0; i < size; i += 3) {
        int new_index = mirror(i, size_x * 3, size_y * 3, matrix, angle);
        //new_index = new_index / 3;
        //new_index = new_index * 3;
        new_index -= new_index % 3;

        if (new_index > 0) {

            to[i + 0] = from[i + 0];
            to[i + 1] = from[i + 1];
            to[i + 2] = from[i + 2];

            to[new_index + 0] = from[i + 0];
            to[new_index + 1] = from[i + 1];
            to[new_index + 2] = from[i + 2];
        }
    }
}
*/

void GUIMyFrame1::Reflect(double angle) {
    int size_x = this->copy.GetWidth(),
        size_y = this->copy.GetHeight();

    float alpha_rad = angle * (3.1415926 / 180);
    //wxImage tmp_cpy = this->copy.Copy().Rotate(-alpha_rad, wxPoint(size_x/2, size_y/2));
    wxImage tmp_cpy = this->copy.Copy();

    unsigned char* data = tmp_cpy.GetData();

    size_t size = tmp_cpy.GetWidth() * tmp_cpy.GetHeight();

    size_t size2 = sizeof(data) / sizeof(data[0]);
    //this->check = size;

    for (int y = 0; y < size_y / 2; y++) {
        for (int x = 0; x < size_x; x++) {

            data[y * size_y + 3 * x + 0] = data[(size_y - y) * size_y + 3 * x + 0];
            data[y * size_y + 3 * x + 1] = data[(size_y - y) * size_y + 3 * x + 1];
            data[y * size_y + 3 * x + 2] = data[(size_y - y) * size_y + 3 * x + 2];

        }
    }

    //this->copy = tmp_cpy.Rotate(alpha_rad, wxPoint(size_x / 2, size_y / 2));
    this->copy = tmp_cpy;
}