#ifndef RENDERSETUPDIALOG_H
#define RENDERSETUPDIALOG_H

//(*Headers(RenderSetupDialog)
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class RenderSetupDialog: public wxDialog
{
	public:

		RenderSetupDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~RenderSetupDialog();

		//(*Declarations(RenderSetupDialog)
		wxTextCtrl* solarAltitudeTextBox;
		wxButton* cancelButton;
		wxTextCtrl* imageSizeTextBox;
		wxTextCtrl* pixelIntensityTextBox;
		wxStaticText* StaticText1;
		wxButton* renderButton;
		wxStaticText* StaticText3;
		wxTextCtrl* maxRayCastInfoTextBox;
		wxStaticText* StaticText4;
		wxStaticText* StaticText5;
		wxStaticText* StaticText2;
		wxStaticText* StaticText6;
		wxTextCtrl* solarDiskRadiusTextBox;
		wxTextCtrl* crystalCountTextBox;
		//*)

	protected:

		//(*Identifiers(RenderSetupDialog)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_STATICTEXT4;
		static const long ID_TEXTCTRL4;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL3;
		static const long ID_STATICTEXT5;
		static const long ID_TEXTCTRL5;
		static const long ID_STATICTEXT6;
		static const long ID_TEXTCTRL6;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(RenderSetupDialog)
		void OnRenderButtonClick(wxCommandEvent& event);
		void OnCancelButtonClick(wxCommandEvent& event);
		void OnTextCtrl1Text(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
