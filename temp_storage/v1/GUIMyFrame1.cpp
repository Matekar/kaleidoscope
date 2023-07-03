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
    //newImage = newImage.Rotate(90* 3.1415926 / 180, wxPoint(m_panel1->GetSize().x/2, m_panel1->GetSize().y/2));

    this->original = newImage;
    this->copy = this->original.Copy();

    //Mat newMap = imread(static_cast<std::string>(openFileDialog.GetPath()), IMREAD_COLOR);
    //this->orig = newMap;


    Repaint();
}

void GUIMyFrame1::Revert( wxCommandEvent& event )
{
    this->copy = this->original.Copy();
    Repaint();
}

void GUIMyFrame1::Recount_Axes( wxScrollEvent& event )
{
// TODO: Implement Recount_Axes
    // Tutaj wszystkie obliczenia ig
}

void GUIMyFrame1::Change_Angle( wxScrollEvent& event )
{
// TODO: Implement Change_Angle
}

void GUIMyFrame1::Move_X( wxScrollEvent& event )
{
// TODO: Implement Move_X
}

void GUIMyFrame1::Move_Y( wxScrollEvent& event )
{
// TODO: Implement Move_Y
}

void GUIMyFrame1::Interpolate( wxCommandEvent& event )
{
// TODO: Implement Interpolate
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

void GUIMyFrame1::whateverthisis( wxCommandEvent& event )
{
// TODO: Implement whateverthisis
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
    this->check = size;

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
}*/

/*void GUIMyFrame1::Reflect(double angle) {
    int size_x = this->copy.GetWidth(),
        size_y = this->copy.GetHeight();

    float alpha_rad = angle * (3.1415926 / 180);
    //wxImage tmp_cpy = this->copy.Copy().Rotate(-alpha_rad, wxPoint(size_x/2, size_y/2));
    wxImage tmp_cpy = this->copy.Copy();

    unsigned char* data = tmp_cpy.GetData();

    size_t size = tmp_cpy.GetWidth() * tmp_cpy.GetHeight();

    size_t size2 = sizeof(data) / sizeof(data[0]);
    this->check = size;

    for (int y = 0; y < size_y / 2; y++) {
        for (int x = 0; x < size_x; x++) {

            data[y * size_y + 3 * x + 0] = data[(size_y - y) * size_y + 3 * x + 0];
            data[y * size_y + 3 * x + 1] = data[(size_y - y) * size_y + 3 * x + 1];
            data[y * size_y + 3 * x + 2] = data[(size_y - y) * size_y + 3 * x + 2];

        }
    }

    //this->copy = tmp_cpy.Rotate(alpha_rad, wxPoint(size_x / 2, size_y / 2));
    this->copy = tmp_cpy;
}*/