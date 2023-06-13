///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 600,600 ), wxTAB_TRAVERSAL );
	m_panel1->SetMinSize( wxSize( 600,600 ) );
	m_panel1->SetMaxSize( wxSize( 900,900 ) );

	bSizer2->Add( m_panel1, 1, wxEXPAND | wxALL, 5 );


	bSizer1->Add( bSizer2, 3, wxEXPAND, 5 );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	m_button1 = new wxButton( this, wxID_ANY, wxT("Open File"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_button1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_button2 = new wxButton( this, wxID_ANY, wxT("Back to original"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_button2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Axis Count: 1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer3->Add( m_staticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_slider1 = new wxSlider( this, wxID_ANY, 1, 1, 20, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer3->Add( m_slider1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_slider4 = new wxSlider( this, wxID_ANY, 0, 0, 359, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer3->Add( m_slider4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_slider5 = new wxSlider( this, wxID_ANY, 0, -100, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer3->Add( m_slider5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_slider6 = new wxSlider( this, wxID_ANY, 0, -100, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer3->Add( m_slider6, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	wxString m_choice1Choices[] = { wxT("Choose Interpolator"), wxT("Interpolator 1"), wxT("Itnerpolator 2"), wxEmptyString, wxEmptyString };
	int m_choice1NChoices = sizeof( m_choice1Choices ) / sizeof( wxString );
	m_choice1 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice1NChoices, m_choice1Choices, 0 );
	m_choice1->SetSelection( 0 );
	bSizer3->Add( m_choice1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_button3 = new wxButton( this, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_button3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_button4 = new wxButton( this, wxID_ANY, wxT("MyButton"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_button4, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );


	bSizer1->Add( bSizer3, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::OpenFile ), NULL, this );
	m_button2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::Revert ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	m_slider4->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	m_slider4->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	m_slider4->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	m_slider4->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	m_slider4->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	m_slider4->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	m_slider4->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	m_slider4->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	m_slider4->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	m_slider5->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	m_slider5->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	m_slider5->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	m_slider5->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	m_slider5->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	m_slider5->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	m_slider5->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	m_slider5->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	m_slider5->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	m_slider6->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	m_slider6->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	m_slider6->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	m_slider6->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	m_slider6->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	m_slider6->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	m_slider6->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	m_slider6->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	m_slider6->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	m_choice1->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MyFrame1::Interpolate ), NULL, this );
	m_button3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::SaveFile ), NULL, this );
	m_button4->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::whateverthisis ), NULL, this );
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	m_button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::OpenFile ), NULL, this );
	m_button2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::Revert ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::Recount_Axes ), NULL, this );
	m_slider4->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	m_slider4->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	m_slider4->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	m_slider4->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	m_slider4->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	m_slider4->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	m_slider4->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	m_slider4->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	m_slider4->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::Change_Angle ), NULL, this );
	m_slider5->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	m_slider5->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	m_slider5->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	m_slider5->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	m_slider5->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	m_slider5->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	m_slider5->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	m_slider5->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	m_slider5->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::Move_X ), NULL, this );
	m_slider6->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	m_slider6->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	m_slider6->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	m_slider6->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	m_slider6->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	m_slider6->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	m_slider6->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	m_slider6->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	m_slider6->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::Move_Y ), NULL, this );
	m_choice1->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MyFrame1::Interpolate ), NULL, this );
	m_button3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::SaveFile ), NULL, this );
	m_button4->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::whateverthisis ), NULL, this );

}
