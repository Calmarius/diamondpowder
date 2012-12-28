/*
Copyright (c) 2012, Dávid Csirmaz
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 * @file HexagonalPrismGeneratorDialog.h
 *
 * Dialog that sets up the hexagonal prism generation.
 */

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

        Mesh &mesh; ///< Reference to the mesh the generator will work on.

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
