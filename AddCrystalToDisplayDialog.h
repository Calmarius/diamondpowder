#ifndef ADDCRYSTALTODISPLAYDIALOG_H
#define ADDCRYSTALTODISPLAYDIALOG_H

//(*Headers(AddCrystalToDisplayDialog)
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class AddCrystalToDisplayDialog: public wxDialog
{
	public:

		AddCrystalToDisplayDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~AddCrystalToDisplayDialog();

		//(*Declarations(AddCrystalToDisplayDialog)
		wxTextCtrl* crystalNameTextBox;
		wxStaticText* StaticText1;
		//*)

	protected:

		//(*Identifiers(AddCrystalToDisplayDialog)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		//*)

	private:

		//(*Handlers(AddCrystalToDisplayDialog)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
