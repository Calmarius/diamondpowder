#ifndef CRYSTALCOMPOSITIONEDITORDIALOG_H
#define CRYSTALCOMPOSITIONEDITORDIALOG_H

//(*Headers(CrystalCompositionEditorDialog)
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>
//*)

class CrystalDescriptor;

class CrystalCompositionEditorDialog: public wxDialog
{
	public:

		CrystalCompositionEditorDialog(std::vector<CrystalDescriptor> &crystalClasses, wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~CrystalCompositionEditorDialog();

		//(*Declarations(CrystalCompositionEditorDialog)
		wxButton* okButton;
		wxStaticText* StaticText1;
		wxBoxSizer* mainSizer;
		//*)

	protected:

		//(*Identifiers(CrystalCompositionEditorDialog)
		static const long ID_STATICTEXT1;
		static const long ID_BUTTON1;
		//*)

	private:

        struct CrystalDescriptorControl
        {
            wxTextCtrl *nameTextBox;
            wxChoice *orientationTypeChoice;
            wxTextCtrl *weightTextBox;
            wxTextCtrl *wobblinessTextBox;
            wxButton *deleteButton;
        };

        struct DeleteCrystalButtonData : public wxClientData
        {
            CrystalDescriptorControl *controlSet;

            DeleteCrystalButtonData(CrystalDescriptorControl *controlSet_)
            {
                 controlSet = controlSet_;
            }
        };

        std::vector<CrystalDescriptorControl*> crystalDescriptorControls;
        std::vector<CrystalDescriptor> &crystalClasses;

		//(*Handlers(CrystalCompositionEditorDialog)
		void OnOkButtonClick(wxCommandEvent& event);
		//*)

		void OnDeleteButtonClick(wxCommandEvent& event);

		DECLARE_EVENT_TABLE()
};

#endif
