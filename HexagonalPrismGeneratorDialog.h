#ifndef HEXAGONALPRISMGENERATORDIALOG_H
#define HEXAGONALPRISMGENERATORDIALOG_H

//(*Headers(HexagonalPrismGeneratorDialog)
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/radiobut.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class HexagonalPrismGeneratorDialog: public wxDialog
{
	public:

		HexagonalPrismGeneratorDialog(Mesh &mesh, wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~HexagonalPrismGeneratorDialog();

		//(*Declarations(HexagonalPrismGeneratorDialog)
		wxTextCtrl* sideFaceRatioTextBox;
		wxTextCtrl* prismHeightTextCtrl;
		wxButton* generatePrismButton;
		wxRadioButton* regularRadioButton;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxButton* cancelPrismGenerationButton;
		wxRadioButton* kernPrismRadioButton;
		wxStaticText* StaticText2;
		wxTextCtrl* parryPlateHeightTextBox;
		wxRadioButton* parryPlateRadioButton;
		//*)

	protected:

		//(*Identifiers(HexagonalPrismGeneratorDialog)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_RADIOBUTTON1;
		static const long ID_RADIOBUTTON2;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_RADIOBUTTON3;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL3;
		static const long ID_BUTTON_GENERATEPRISM;
		static const long ID_CANCEL;
		//*)

	private:

        Mesh &mesh;

		//(*Handlers(HexagonalPrismGeneratorDialog)
		void OngeneratePrismClick(wxCommandEvent& event);
		void OncancelPrismGenerationClick(wxCommandEvent& event);
		void OnRegularRadioButtonSelect(wxCommandEvent& event);
		void OnKernPrismRadioButtonSelect(wxCommandEvent& event);
		void OnParryPlateRadioButtonSelect(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
