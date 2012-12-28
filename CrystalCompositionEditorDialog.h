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
 * @file CrystalCompositionEditorDialog.h
 *
 * The crystal compositon editor dialog box.
 */

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
