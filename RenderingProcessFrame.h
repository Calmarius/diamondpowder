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
 * @file RenderingProcessFrame.h
 *
 * A Window that shows the rendering process and the result.
 */

#ifndef RENDERINGPROCESSFRAME_H
#define RENDERINGPROCESSFRAME_H

//(*Headers(RenderingProcessFrame)
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/stattext.h>
//*)

class HaloRenderingSetupStruct;

class RenderingProcessFrame: public wxFrame
{
	public:

		RenderingProcessFrame(const HaloRenderingSetupStruct &setupStruct, wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~RenderingProcessFrame();

		//(*Declarations(RenderingProcessFrame)
		wxScrolledWindow* mainpanel;
		wxButton* cancelButton;
		wxStaticText* renderingStatusText;
		wxButton* saveBitmapsButton;
		//*)

	protected:

		//(*Identifiers(RenderingProcessFrame)
		static const long ID_STATICTEXT1;
		static const long ID_PANEL1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

        static const int SCROLL_UNIT_SIZE = 15;

		//(*Handlers(RenderingProcessFrame)
		void OnCancelButtonClick(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		void OnPaint(wxPaintEvent& event);
		void OnMainpanelPaint(wxPaintEvent& event);
		void OnSaveBitmapsButtonClick(wxCommandEvent& event);
		void OnLeftDown(wxMouseEvent& event);
		//*)

		wxBitmap *bitmaps[6]; ///< 6 square bitmaps of the cubic panorama.

		void onCancel();
		void OnThreadNotify(wxCommandEvent &event);

		bool operationFinished;
		HaloRenderingSetupStruct setupStruct; ///< Input and output of the rendering process will be stored here.
		HaloRenderingThread *renderingThread; ///< This will do the work.
		Vector3 bitmapLocations[6]; ///< Stores the location where to put the bitmaps when ready.

		DECLARE_EVENT_TABLE()
};

#endif
