#include "RenderSetupDialog.h"

//(*InternalHeaders(RenderSetupDialog)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(RenderSetupDialog)
const long RenderSetupDialog::ID_STATICTEXT1 = wxNewId();
const long RenderSetupDialog::ID_TEXTCTRL1 = wxNewId();
const long RenderSetupDialog::ID_STATICTEXT2 = wxNewId();
const long RenderSetupDialog::ID_TEXTCTRL2 = wxNewId();
const long RenderSetupDialog::ID_STATICTEXT4 = wxNewId();
const long RenderSetupDialog::ID_TEXTCTRL4 = wxNewId();
const long RenderSetupDialog::ID_STATICTEXT3 = wxNewId();
const long RenderSetupDialog::ID_TEXTCTRL3 = wxNewId();
const long RenderSetupDialog::ID_STATICTEXT5 = wxNewId();
const long RenderSetupDialog::ID_TEXTCTRL5 = wxNewId();
const long RenderSetupDialog::ID_STATICTEXT6 = wxNewId();
const long RenderSetupDialog::ID_TEXTCTRL6 = wxNewId();
const long RenderSetupDialog::ID_BUTTON1 = wxNewId();
const long RenderSetupDialog::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(RenderSetupDialog,wxDialog)
	//(*EventTable(RenderSetupDialog)
	//*)
END_EVENT_TABLE()

RenderSetupDialog::RenderSetupDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(RenderSetupDialog)
	wxFlexGridSizer* FlexGridSizer1;
	wxBoxSizer* BoxSizer1;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Count of crystals:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	crystalCountTextBox = new wxTextCtrl(this, ID_TEXTCTRL1, _("100000"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer1->Add(crystalCountTextBox, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Image size (a×a in pixels):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	imageSizeTextBox = new wxTextCtrl(this, ID_TEXTCTRL2, _("300"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	FlexGridSizer1->Add(imageSizeTextBox, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Solar altitude (in degrees)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer1->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	solarAltitudeTextBox = new wxTextCtrl(this, ID_TEXTCTRL4, _("22"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	FlexGridSizer1->Add(solarAltitudeTextBox, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Solar disk radius (in degrees):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer1->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	solarDiskRadiusTextBox = new wxTextCtrl(this, ID_TEXTCTRL3, _("0.5"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	FlexGridSizer1->Add(solarDiskRadiusTextBox, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Pixel intensity"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer1->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	pixelIntensityTextBox = new wxTextCtrl(this, ID_TEXTCTRL5, _("1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
	FlexGridSizer1->Add(pixelIntensityTextBox, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Maximum raycast info (in megs):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer1->Add(StaticText6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	maxRayCastInfoTextBox = new wxTextCtrl(this, ID_TEXTCTRL6, _("100"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL6"));
	FlexGridSizer1->Add(maxRayCastInfoTextBox, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cancelButton = new wxButton(this, ID_BUTTON1, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer1->Add(cancelButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	renderButton = new wxButton(this, ID_BUTTON2, _("Render!"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer1->Add(renderButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(FlexGridSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&RenderSetupDialog::OnCancelButtonClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&RenderSetupDialog::OnRenderButtonClick);
	//*)
}

RenderSetupDialog::~RenderSetupDialog()
{
	//(*Destroy(RenderSetupDialog)
	//*)
}


void RenderSetupDialog::OnRenderButtonClick(wxCommandEvent& event)
{
    EndModal(wxID_OK);
}

void RenderSetupDialog::OnCancelButtonClick(wxCommandEvent& event)
{
    EndModal(wxID_CANCEL);
}

void RenderSetupDialog::OnTextCtrl1Text(wxCommandEvent& event)
{
}
