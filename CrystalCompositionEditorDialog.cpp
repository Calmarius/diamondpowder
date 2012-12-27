#include "CrystalCompositionEditorDialog.h"

//(*InternalHeaders(CrystalCompositionEditorDialog)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(CrystalCompositionEditorDialog)
const long CrystalCompositionEditorDialog::ID_STATICTEXT1 = wxNewId();
const long CrystalCompositionEditorDialog::ID_BUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(CrystalCompositionEditorDialog,wxDialog)
	//(*EventTable(CrystalCompositionEditorDialog)
	//*)
END_EVENT_TABLE()

CrystalCompositionEditorDialog::CrystalCompositionEditorDialog(
    std::vector<CrystalDescriptor> &_crystalClasses,
    wxWindow* parent,
    wxWindowID id,
    const wxPoint& pos,
    const wxSize& size
):
    crystalClasses(_crystalClasses)
{
	//(*Initialize(CrystalCompositionEditorDialog)
	wxFlexGridSizer* crystalSizer;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	mainSizer = new wxBoxSizer(wxVERTICAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Crystal composition:"), wxDefaultPosition, wxSize(149,27), 0, _T("ID_STATICTEXT1"));
	mainSizer->Add(StaticText1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	crystalSizer = new wxFlexGridSizer(0, 5, 0, 0);
	mainSizer->Add(crystalSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	okButton = new wxButton(this, ID_BUTTON1, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	mainSizer->Add(okButton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(mainSizer);
	mainSizer->Fit(this);
	mainSizer->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CrystalCompositionEditorDialog::OnOkButtonClick);
	//*)

    crystalSizer->Add(new wxStaticText(this, -1, wxT("Name")));
    crystalSizer->Add(new wxStaticText(this, -1, wxT("Orientation")));
    crystalSizer->Add(new wxStaticText(this, -1, wxT("Population weight")));
    crystalSizer->Add(new wxStaticText(this, -1, wxT("wobbliness (in °)")));
    crystalSizer->Add(new wxStaticText(this, -1, wxT("")));

    for(size_t i = 0; i < crystalClasses.size(); i++)
    {
        CrystalDescriptor &current = crystalClasses[i];
        CrystalDescriptorControl *control = new CrystalDescriptorControl();

        control->nameTextBox = new wxTextCtrl(this, -1, wxString::FromUTF8(current.name.c_str()));

        wxChoice *choice = new wxChoice(this, -1);
        for (size_t j = 0; j < CrystalDescriptor::OT_MAX_ORIENTATIONTYPE; j++)
        {
            choice->Append(wxString::FromUTF8(CrystalDescriptor::orientationTypes[j]));
            if (j == (size_t)current.orientation)
            {
                choice->SetSelection(j);
            }
        }
        control->orientationTypeChoice = choice;
        control->weightTextBox = new wxTextCtrl(this, -1, wxString::Format(wxT("%g"), current.populationWeight));
        control->wobblinessTextBox = new wxTextCtrl(this, -1, wxString::Format(wxT("%g"), current.wobbliness));
        control->deleteButton = new wxButton(this, wxNewId(), wxT("Delete"));

        crystalSizer->Add(control->nameTextBox);
        crystalSizer->Add(control->orientationTypeChoice);
        crystalSizer->Add(control->weightTextBox);
        crystalSizer->Add(control->wobblinessTextBox);
        crystalSizer->Add(control->deleteButton);

        Connect(control->deleteButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&CrystalCompositionEditorDialog::OnDeleteButtonClick);

        crystalDescriptorControls.push_back(control);
        control->deleteButton->SetClientObject(new DeleteCrystalButtonData(control));
    }

	mainSizer->Fit(this);
	mainSizer->SetSizeHints(this);

}

CrystalCompositionEditorDialog::~CrystalCompositionEditorDialog()
{
	//(*Destroy(CrystalCompositionEditorDialog)
	//*)
}

void CrystalCompositionEditorDialog::OnDeleteButtonClick(wxCommandEvent& event)
{
    wxButton *button = dynamic_cast<wxButton*>(event.GetEventObject());
    if (!button) return;

    DeleteCrystalButtonData *dcbd = dynamic_cast<DeleteCrystalButtonData*>(button->GetClientObject());
    if (!dcbd) return;

    CrystalDescriptorControl &controlSet = *dcbd->controlSet;

    size_t controlSetIndex;

    for (controlSetIndex = 0; controlSetIndex < crystalDescriptorControls.size(); controlSetIndex++)
    {
        if (crystalDescriptorControls[controlSetIndex] == &controlSet)
        {
            break;
        }
    }

    if (controlSetIndex == crystalDescriptorControls.size()) return;

    controlSet.deleteButton->Destroy();
    controlSet.nameTextBox->Destroy();
    controlSet.orientationTypeChoice->Destroy();
    controlSet.weightTextBox->Destroy();
    controlSet.wobblinessTextBox->Destroy();

    delete crystalDescriptorControls[controlSetIndex];
    crystalDescriptorControls.erase(crystalDescriptorControls.begin() + controlSetIndex);
    crystalClasses.erase(crystalClasses.begin() + controlSetIndex);

	mainSizer->Fit(this);
	mainSizer->SetSizeHints(this);

}

void CrystalCompositionEditorDialog::OnOkButtonClick(wxCommandEvent& event)
{
    for (size_t i = 0; i < crystalDescriptorControls.size(); i++)
    {
        CrystalDescriptorControl &currentControl = *crystalDescriptorControls[i];
        CrystalDescriptor &currentDescriptor = crystalClasses[i];
        long tmp = 0;
        double tmpf;

        currentDescriptor.name.assign(currentControl.nameTextBox->GetValue().ToUTF8());
        currentDescriptor.orientation = (CrystalDescriptor::OrientationType)currentControl.orientationTypeChoice->GetSelection();
        currentControl.weightTextBox->GetValue().ToLong(&tmp);
        currentDescriptor.populationWeight = tmp;
        currentControl.wobblinessTextBox->GetValue().ToDouble(&tmpf);
        currentDescriptor.wobbliness = tmpf;
    }
    Close();
}
