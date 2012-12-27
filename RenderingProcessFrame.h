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

		wxBitmap *bitmaps[6];

		void onCancel();

		void OnThreadNotify(wxCommandEvent &event);
		bool operationFinished;
		HaloRenderingSetupStruct setupStruct;
		HaloRenderingThread *renderingThread;
		Vector3 bitmapLocations[6];

		DECLARE_EVENT_TABLE()
};

#endif
