#include "AddCrystalToDisplayDialog.h"

//(*InternalHeaders(AddCrystalToDisplayDialog)
#include <wx/button.h>
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(AddCrystalToDisplayDialog)
const long AddCrystalToDisplayDialog::ID_STATICTEXT1 = wxNewId();
const long AddCrystalToDisplayDialog::ID_TEXTCTRL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(AddCrystalToDisplayDialog,wxDialog)
	//(*EventTable(AddCrystalToDisplayDialog)
	//*)
END_EVENT_TABLE()

AddCrystalToDisplayDialog::AddCrystalToDisplayDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(AddCrystalToDisplayDialog)
	wxFlexGridSizer* FlexGridSizer1;
	wxBoxSizer* BoxSizer1;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;
	
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Name:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	crystalNameTextBox = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer1->Add(crystalNameTextBox, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(FlexGridSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StdDialogButtonSizer1 = new wxStdDialogButtonSizer();
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_OK, wxEmptyString));
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_CANCEL, wxEmptyString));
	StdDialogButtonSizer1->Realize();
	BoxSizer1->Add(StdDialogButtonSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	//*)
}

AddCrystalToDisplayDialog::~AddCrystalToDisplayDialog()
{
	//(*Destroy(AddCrystalToDisplayDialog)
	//*)
}

