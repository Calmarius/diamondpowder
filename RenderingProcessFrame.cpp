#include "RenderingProcessFrame.h"

//(*InternalHeaders(RenderingProcessFrame)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(RenderingProcessFrame)
const long RenderingProcessFrame::ID_STATICTEXT1 = wxNewId();
const long RenderingProcessFrame::ID_PANEL1 = wxNewId();
const long RenderingProcessFrame::ID_BUTTON1 = wxNewId();
const long RenderingProcessFrame::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(RenderingProcessFrame,wxFrame)
    EVT_COMMAND(wxID_ANY, wxEVT_HALO_RENDERING_THREAD_NOTIFY, RenderingProcessFrame::OnThreadNotify)
	//(*EventTable(RenderingProcessFrame)
	//*)
END_EVENT_TABLE()

RenderingProcessFrame::RenderingProcessFrame(const HaloRenderingSetupStruct &setupStruct_, wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size) :
    setupStruct(setupStruct_)
{
	//(*Initialize(RenderingProcessFrame)
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;

	Create(parent, id, _("Rendering"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxVSCROLL|wxHSCROLL, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	renderingStatusText = new wxStaticText(this, ID_STATICTEXT1, _("Rendering status..."), wxDefaultPosition, wxSize(360,22), 0, _T("ID_STATICTEXT1"));
	BoxSizer1->Add(renderingStatusText, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	mainpanel = new wxScrolledWindow(this, ID_PANEL1, wxDefaultPosition, wxSize(360,123), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	BoxSizer1->Add(mainpanel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	cancelButton = new wxButton(this, ID_BUTTON1, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer2->Add(cancelButton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	saveBitmapsButton = new wxButton(this, ID_BUTTON2, _("Save bitmaps"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	saveBitmapsButton->Disable();
	BoxSizer2->Add(saveBitmapsButton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	mainpanel->Connect(wxEVT_PAINT,(wxObjectEventFunction)&RenderingProcessFrame::OnMainpanelPaint,0,this);
	mainpanel->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&RenderingProcessFrame::OnLeftDown,0,this);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&RenderingProcessFrame::OnCancelButtonClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&RenderingProcessFrame::OnSaveBitmapsButtonClick);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&RenderingProcessFrame::OnClose);
	Connect(wxEVT_PAINT,(wxObjectEventFunction)&RenderingProcessFrame::OnPaint);
	//*)

    const int m = setupStruct.imageSize;

    bitmapLocations[0].x = 0 * m + 5;
    bitmapLocations[0].y = 1 * m + 5;
    bitmapLocations[0].z = 0;

    bitmapLocations[1].x = 2 * m + 5;
    bitmapLocations[1].y = 1 * m + 5;
    bitmapLocations[1].z = 0;

    bitmapLocations[2].x = 1 * m + 5;
    bitmapLocations[2].y = 0 * m + 5;
    bitmapLocations[2].z = 0;

    bitmapLocations[3].x = 1 * m + 5;
    bitmapLocations[3].y = 2 * m + 5;
    bitmapLocations[3].z = 0;

    bitmapLocations[4].x = 0 * m;
    bitmapLocations[4].y = 0 * m;
    bitmapLocations[4].z = 0;

    bitmapLocations[5].x = 1 * m + 5;
    bitmapLocations[5].y = 1 * m + 5;
    bitmapLocations[5].z = 0;


    operationFinished = false;
    setupStruct.notifee = this;
    setupStruct.cancelled = false;
    renderingThread = new HaloRenderingThread(this->setupStruct);
    renderingThread->Create();
    renderingThread->Run();

    for (int i = 0; i < 6; i++)
    {
        bitmaps[i]= new wxBitmap(setupStruct.imageSize, setupStruct.imageSize);
    }

    mainpanel->SetScrollbars(
        SCROLL_UNIT_SIZE,
        SCROLL_UNIT_SIZE,
        3 * setupStruct.imageSize / SCROLL_UNIT_SIZE + 1,
        3 * setupStruct.imageSize / SCROLL_UNIT_SIZE + 1
    );
}

RenderingProcessFrame::~RenderingProcessFrame()
{
	//(*Destroy(RenderingProcessFrame)
	//*)
	for (int i = 0; i < 6; i++)
	{
        delete bitmaps[i];
	}
	setupStruct.deleteBuffer(setupStruct.imageBuffer);
	setupStruct.deleteMap(setupStruct.rayPaths);
}

void RenderingProcessFrame::OnThreadNotify(wxCommandEvent &event)
{
    renderingStatusText->SetLabel(event.GetString());
    if (event.GetInt())
    {
        operationFinished = true;
        cancelButton->SetLabel(wxT("Finish"));
        saveBitmapsButton->Enable();
        if (!setupStruct.resultValid) return;
        for (size_t k = 0; k < 6; k++)
        {
            wxMemoryDC bdc(*bitmaps[k]);
            size_t offset = k * setupStruct.imageSize * setupStruct.imageSize;

            for (size_t i = 0; i < setupStruct.imageSize; i++)
            {
                for (size_t j = 0; j < setupStruct.imageSize; j++)
                {
                    uint32_t raw = setupStruct.imageBuffer[j * setupStruct.imageSize + i + offset];
                    int red = raw & 0xFF;
                    int green = (raw >> 8) & 0xFF;
                    int blue = (raw >> 16) & 0xFF;
                    wxPen pen(wxColour(red, green, blue)); // YUK!
                    bdc.SetPen(pen);
                    bdc.DrawPoint(i, j);
                }
            }

        }
    }
}

void RenderingProcessFrame::onCancel()
{
    setupStruct.cancelled = true;
    renderingThread->Wait();
    Destroy();
}

void RenderingProcessFrame::OnCancelButtonClick(wxCommandEvent& event)
{
    Close();
}

void RenderingProcessFrame::OnClose(wxCloseEvent& event)
{
    onCancel();
}

void RenderingProcessFrame::OnPaint(wxPaintEvent& event)
{
    wxPaintDC hdc(this);

    /*
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            hdc.DrawBitmap(*bitmaps[j * 3 + i], i * setupStruct.imageSize + 10, j * setupStruct.imageSize + 10);
        }
    }
    */
}

void RenderingProcessFrame::OnMainpanelPaint(wxPaintEvent& event)
{
    wxPaintDC hdc(mainpanel);
    mainpanel->DoPrepareDC(hdc);
    if (!operationFinished) return;

    for (int i = 0; i < 6; i++)
    {
        hdc.DrawBitmap(*bitmaps[i], bitmapLocations[i].x, bitmapLocations[i].y);
    }
}

void RenderingProcessFrame::OnSaveBitmapsButtonClick(wxCommandEvent& event)
{
    int m = setupStruct.imageSize;
    wxBitmap composite(4 * m , 3 * m);
    wxMemoryDC dc(composite);

    dc.DrawBitmap(*bitmaps[0], 0 * m, 1 * m); // LEFT
    dc.DrawBitmap(*bitmaps[1], 2 * m, 1 * m); // RIGHT
    dc.DrawBitmap(*bitmaps[2], 1 * m, 0 * m); // TOP
    dc.DrawBitmap(*bitmaps[3], 1 * m, 2 * m); // BOTTOM
    dc.DrawBitmap(*bitmaps[4], 3 * m, 1 * m); // BACK
    dc.DrawBitmap(*bitmaps[5], 1 * m, 1 * m); // FRONT

    composite.ConvertToImage().SaveFile(wxT("rendering.png"));

}

void RenderingProcessFrame::OnLeftDown(wxMouseEvent& event)
{
    int m = setupStruct.imageSize; //< Size of a single image plane;
    // Get scroll positions
    int sx, sy;
    mainpanel->GetViewStart(&sx, &sy);
    // Clicked positions
    int x = event.GetX() + sx * SCROLL_UNIT_SIZE;
    int y = event.GetY() + sy * SCROLL_UNIT_SIZE;

    int planeId;

    for (planeId = 0; planeId < 6; planeId++)
    {
        if (
            (bitmapLocations[planeId].x <= x) && (x < bitmapLocations[planeId].x + m) &&
            (bitmapLocations[planeId].y <= y) && (y < bitmapLocations[planeId].y + m)
        )
        {
            break;
        }
    }
    if (planeId == 6) return; //< No image plane clicked

    // Location inside the selected plane.
    int px = x - bitmapLocations[planeId].x;
    int py = y - bitmapLocations[planeId].y;

    printf("Selected ray: Plate: %d, x: %d, y: %d\n", planeId, px, py);

    map<RayPathId, RayPathDescriptor>::iterator it = setupStruct.rayPaths->find(RayPathId(planeId, px, py));

    if (it != setupStruct.rayPaths->end())
    {
        printf("Ray found!\n");
        // Pixel found open crystal editor frame
        CrystalEditorFrame *editorframe = new CrystalEditorFrame(it->second, this);
        editorframe->Show();
    }

}
