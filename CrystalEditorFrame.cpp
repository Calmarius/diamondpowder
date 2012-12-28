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
 * @file CrystalEditorFrame.cpp
 *
 * Code for the crystal editor window.
 */

//(*InternalHeaders(CrystalEditorFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(CrystalEditorFrame)
const long CrystalEditorFrame::ID_PANEL1 = wxNewId();
const long CrystalEditorFrame::ID_MENUITEM_GENHEXAGONALPRISM = wxNewId();
const long CrystalEditorFrame::ID_MENUITEM3 = wxNewId();
const long CrystalEditorFrame::ID_MENUITEM1 = wxNewId();
const long CrystalEditorFrame::ID_MENUITEM2 = wxNewId();
const long CrystalEditorFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(CrystalEditorFrame,wxFrame)
    EVT_KEY_DOWN(CrystalEditorFrame::OnKeyDown)
	//(*EventTable(CrystalEditorFrame)
	//*)
END_EVENT_TABLE()

void CrystalEditorFrame::initialize(wxWindow *parent, wxWindowID id)
{
	//(*Initialize(CrystalEditorFrame)
	wxMenuItem* generateHexagonalPrismMenuItem;

	Create(parent, id, _("Crystal editor"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
	SetClientSize(wxSize(605,282));
	mainPanel = new wxPanel(this, ID_PANEL1, wxPoint(256,152), wxDefaultSize, 0, _T("ID_PANEL1"));
	MenuBar1 = new wxMenuBar();
	Menu1 = new wxMenu();
	generateHexagonalPrismMenuItem = new wxMenuItem(Menu1, ID_MENUITEM_GENHEXAGONALPRISM, _("Hexagonal prism..."), _("Generates hexagonal prism"), wxITEM_NORMAL);
	Menu1->Append(generateHexagonalPrismMenuItem);
	generateOctahedronMenuItem = new wxMenuItem(Menu1, ID_MENUITEM3, _("Octahedron"), _("Generates regular octahedron"), wxITEM_NORMAL);
	Menu1->Append(generateOctahedronMenuItem);
	MenuBar1->Append(Menu1, _("Generate"));
	Menu2 = new wxMenu();
	addCrystalToDisplayItem = new wxMenuItem(Menu2, ID_MENUITEM1, _("Add this crystal to the display..."), wxEmptyString, wxITEM_NORMAL);
	Menu2->Append(addCrystalToDisplayItem);
	MenuBar1->Append(Menu2, _("Manage"));
	Menu3 = new wxMenu();
	castRayMenuItem = new wxMenuItem(Menu3, ID_MENUITEM2, _("&Cast Ray\tC"), _("Casts a ray on the mesh"), wxITEM_NORMAL);
	Menu3->Append(castRayMenuItem);
	MenuBar1->Append(Menu3, _("Controls"));
	SetMenuBar(MenuBar1);
	StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
	int __wxStatusBarWidths_1[1] = { -10 };
	int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
	StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
	StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
	SetStatusBar(StatusBar1);

	mainPanel->Connect(wxEVT_PAINT,(wxObjectEventFunction)&CrystalEditorFrame::OnPaint,0,this);
	mainPanel->Connect(wxEVT_KEY_DOWN,(wxObjectEventFunction)&CrystalEditorFrame::OnKeyDown,0,this);
	mainPanel->Connect(wxEVT_KEY_UP,(wxObjectEventFunction)&CrystalEditorFrame::OnKeyUp,0,this);
	mainPanel->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&CrystalEditorFrame::OnLeftDown,0,this);
	mainPanel->Connect(wxEVT_LEFT_UP,(wxObjectEventFunction)&CrystalEditorFrame::OnLeftUp,0,this);
	mainPanel->Connect(wxEVT_MOTION,(wxObjectEventFunction)&CrystalEditorFrame::OnMouseMove,0,this);
	mainPanel->Connect(wxEVT_MOUSEWHEEL,(wxObjectEventFunction)&CrystalEditorFrame::OnMouseWheel,0,this);
	Connect(ID_MENUITEM_GENHEXAGONALPRISM,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CrystalEditorFrame::OnGenerateHexagonalPrismMenuItemSelected);
	Connect(ID_MENUITEM3,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CrystalEditorFrame::OnGenerateOctahedronMenuItemSelected);
	Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CrystalEditorFrame::OnAddCrystalToDisplayItemSelected);
	Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CrystalEditorFrame::OnCastRayMenuItemSelected);
	Connect(wxEVT_ERASE_BACKGROUND,(wxObjectEventFunction)&CrystalEditorFrame::OnEraseBackground);
	Connect(wxEVT_RIGHT_DOWN,(wxObjectEventFunction)&CrystalEditorFrame::OnRightDown);
	//*)

    mainPanel->SetFocus();

    // Initialize red, green, blue rays.

    rayPaths[0].refractionIndex = RED_N;
    rayPaths[0].pen = wxPen(wxColor(255, 0, 0));
    rayPaths[0].rayPaths.clear();

    rayPaths[1].refractionIndex = GREEN_N;
    rayPaths[1].pen = wxPen(wxColor(0, 255, 0));
    rayPaths[1].rayPaths.clear();

    rayPaths[2].refractionIndex = BLUE_N;
    rayPaths[2].pen = wxPen(wxColor(0, 0, 255));
    rayPaths[2].rayPaths.clear();

    rayCastingMode = false;

    // Make pens

    redPen = wxPen(wxColour(255, 0, 0));
    greenPen = wxPen(wxColour(0, 255, 0));
    bluePen = wxPen(wxColour(0, 0, 255));

}

CrystalEditorFrame::CrystalEditorFrame(const RayPathDescriptor &rtd, wxWindow* parent,wxWindowID id):
    rayPathDescriptor(rtd),
    right(1, 0, 0),
    upward(0, 1, 0),
    backward(0, 0, 1),
    target(0, 0, 0),
    distance(10),
    crystalMeshes(0),
    dragging(false),
    prevMousePos(0, 0, 0),
    rayPos(-10, 0, 0),
    rayDir(1, 0, 0)
{
    initialize(parent, id);

    addCrystalToDisplayItem->Enable(false);
    castRayMenuItem->Enable(false);

    crystalMesh = *rtd.mesh;
    transformMesh(crystalMesh, rtd.orientation);
    rayPos = rtd.rayPos;
    rayDir = rtd.rayDir;

    updateRayPaths();

    minimumIntensity = 0.5;
}


CrystalEditorFrame::CrystalEditorFrame(std::vector<CrystalDescriptor> &_crystalMeshes, wxWindow* parent,wxWindowID id):
    right(1, 0, 0),
    upward(0, 1, 0),
    backward(0, 0, 1),
    target(0, 0, 0),
    distance(10),
    crystalMeshes(&_crystalMeshes),
    dragging(false),
    prevMousePos(0, 0, 0),
    rayPos(-10, 0, 0),
    rayDir(1, 0, 0)
{

    initialize(parent, id);
	// Put a cube into the mesh.
    initMesh(crystalMesh);

    // back face
    crystalMesh.vertices.push_back(Vector3(-1, -1, -1));
    crystalMesh.vertices.push_back(Vector3(-1, 1, -1));
    crystalMesh.vertices.push_back(Vector3(1, 1, -1));
    crystalMesh.vertices.push_back(Vector3(1, -1, -1));
    // front face
    crystalMesh.vertices.push_back(Vector3(-1, -1, 1));
    crystalMesh.vertices.push_back(Vector3(-1, 1, 1));
    crystalMesh.vertices.push_back(Vector3(1, 1, 1));
    crystalMesh.vertices.push_back(Vector3(1, -1, 1));

    // back face
    vector<int> face;
    face.push_back(0);
    face.push_back(1);
    face.push_back(2);
    face.push_back(3);
    crystalMesh.faces.push_back(face);

    // front face
    face.clear();
    face.push_back(4);
    face.push_back(5);
    face.push_back(6);
    face.push_back(7);
    crystalMesh.faces.push_back(face);

    // left face
    face.clear();
    face.push_back(0);
    face.push_back(1);
    face.push_back(5);
    face.push_back(4);
    crystalMesh.faces.push_back(face);

    // right face
    face.clear();
    face.push_back(2);
    face.push_back(3);
    face.push_back(7);
    face.push_back(6);
    crystalMesh.faces.push_back(face);

    // top face
    face.clear();
    face.push_back(1);
    face.push_back(5);
    face.push_back(6);
    face.push_back(2);
    crystalMesh.faces.push_back(face);

    // bottom face
    face.clear();
    face.push_back(0);
    face.push_back(4);
    face.push_back(7);
    face.push_back(3);
    crystalMesh.faces.push_back(face);

    minimumIntensity = 0;
}

CrystalEditorFrame::~CrystalEditorFrame()
{
	//(*Destroy(CrystalEditorFrame)
	//*)
}


void CrystalEditorFrame::OnGenerateHexagonalPrismMenuItemSelected(wxCommandEvent& event)
{
    HexagonalPrismGeneratorDialog hexaPrismGen(crystalMesh, this);
    hexaPrismGen.ShowModal();
    mainPanel->Refresh();
}

void CrystalEditorFrame::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(mainPanel);
    dc.SetBackground(*wxBLACK_BRUSH);
    dc.Clear();
    int width, height;
    GetClientSize(&width, &height);
    Matrix combinedMatrix = create3DTransformationMatrix
    (
        target + backward * distance,
        target,
        upward,
        0, 0,
        width, height
    );

    // Render coorinate axes
    Vector3 origin(0,0,0);
    Vector3 right(0.3,0,0);
    Vector3 up(0,0.3,0);
    Vector3 backward(0,0,0.3);

    dc.SetPen(redPen);
    drawLine3d(dc, combinedMatrix, origin, right);
    dc.SetPen(greenPen);
    drawLine3d(dc, combinedMatrix, origin, up);
    dc.SetPen(bluePen);
    drawLine3d(dc, combinedMatrix, origin, backward);

    // Render ray paths
    for (int i = 0; i < COLOR_COUNT; i++)
    {
        Ray &currentPaths = rayPaths[i];
        wxColor pc = currentPaths.pen.GetColour();
        for (size_t j = 0; j < currentPaths.rayPaths.size(); j++)
        {
            vector<pair<Vector3, double> > &currentPath = currentPaths.rayPaths[j];
            for (size_t k = 0; k < currentPath.size() - 1; k++)
            {
                double p = currentPath[k].second;
                if (p < minimumIntensity) p = minimumIntensity;
                wxPen tmpPen(
                    wxColour(
                        clampIn(p * pc.Red(), 0, 255),
                        clampIn(p * pc.Green(), 0, 255),
                        clampIn(p * pc.Blue(), 0, 255)
                    )
                );

                dc.SetPen(tmpPen);
                drawLine3d(dc, combinedMatrix, currentPath[k].first, currentPath[k + 1].first);
            }
        }
    }
    // Render the mesh wireframe
    dc.SetPen(*wxWHITE_PEN);
    renderMeshOnDC(
        dc,
        crystalMesh,
        combinedMatrix,
        RM_WIREFRAME
    );
}

void CrystalEditorFrame::OnLeftDown(wxMouseEvent& event)
{
    if (rayCastingMode)
    {
        // Cast a ray towards the clicked point.
        int width, height;
        GetClientSize(&width, &height);
        double unitLength = min(width, height);
        double offsetX = (event.GetX() - (width * 0.5)) / unitLength;
        double offsetY = -(event.GetY() - (height * 0.5)) / unitLength;


        rayPos = target + backward * distance;
        rayDir = -backward + offsetX * right + offsetY * upward;

        SetCursor(wxNullCursor);
        rayCastingMode = false;

        updateRayPaths();
        mainPanel->Refresh();
        return;
    }
    dragging = true;
    prevMousePos.x = event.GetX();
    prevMousePos.y = event.GetY();
}

void CrystalEditorFrame::OnLeftUp(wxMouseEvent& event)
{
    dragging = false;
}

void CrystalEditorFrame::updateRayPaths()
{
    for (int i = 0; i < COLOR_COUNT; i++)
    {
        computeRayPathInGlassMesh(
            crystalMesh,
            rayPaths[i].refractionIndex,
            rayPos,
            rayDir,
            0.01,
            rayPaths[i].rayPaths
        );
    }
}


void CrystalEditorFrame::OnMouseMove(wxMouseEvent& event)
{
    if (!dragging) return;

    // Turn mouse movement to a movement of a virtual trackball (which is as big as the window).
    Vector3 currentMousePos(event.GetX(), event.GetY(), 0);
    int width, height;
    GetSize(&width, &height);
    log_var(CRYSTAL_EDITOR_MOUSE_MOVE, width);
    log_var(CRYSTAL_EDITOR_MOUSE_MOVE, height);
    double windowSize = std::min(width, height);
    log_var(CRYSTAL_EDITOR_MOUSE_MOVE, windowSize);
    Vector3 center(0.5 * width, 0.5 * height, 0);
    log_var(CRYSTAL_EDITOR_MOUSE_MOVE, center);
    Vector3 normPrevPos = (prevMousePos - center) / windowSize;
    log_var(CRYSTAL_EDITOR_MOUSE_MOVE, normPrevPos);
    Vector3 normPos = (currentMousePos - center) / windowSize;
    log_var(CRYSTAL_EDITOR_MOUSE_MOVE, normPos);
    // Invert vertical axis, because in camera space Y grow upward.
    normPrevPos.y = -normPrevPos.y;
    normPos.y = -normPos.y;
    // Calculate the Z position on the trackball
    normPrevPos.z = normPrevPos * normPrevPos <= 1 ? sqrt(1.0 - normPrevPos * normPrevPos) : 0;
    normPos.z = normPos * normPos <= 1 ? sqrt(1.0 - normPos * normPos) : 0;
    log_var(CRYSTAL_EDITOR_MOUSE_MOVE, normPrevPos);
    log_var(CRYSTAL_EDITOR_MOUSE_MOVE, normPos);
    // Calculate the rotation axis
    Vector3 rotAxis = normPrevPos % normPos;
    double rotAxisLength = ~rotAxis;
    if (rotAxisLength == 0)
    {
        // No rotation.
        return;
    }
    rotAxis /= rotAxisLength;
    log_var(CRYSTAL_EDITOR_MOUSE_MOVE, rotAxis);
    // Calculate the real rotation axis and the angle.
    double rotAngle = acos((normPrevPos * normPos)/(~normPrevPos * ~normPos));
    log_var(CRYSTAL_EDITOR_MOUSE_MOVE, rotAngle);
    Vector3 realRotAxis = rotAxis.x * right + rotAxis.y * upward + rotAxis.z * backward; // Create the true rotation axis (in camera space).
    log_var(CRYSTAL_EDITOR_MOUSE_MOVE, realRotAxis);

    Matrix rotation = createRotationMatrix(realRotAxis, -rotAngle); // Negative as we rotate the view, not the object
    log_var(CRYSTAL_EDITOR_MOUSE_MOVE, rotation);

    backward = transformVector(rotation, backward);
    right = transformVector(rotation, right);
    upward = transformVector(rotation, upward);
    log_var(CRYSTAL_EDITOR_MOUSE_MOVE, backward);
    log_var(CRYSTAL_EDITOR_MOUSE_MOVE, right);
    log_var(CRYSTAL_EDITOR_MOUSE_MOVE, upward);

    fix3VectorSystem(right, upward, backward);

    prevMousePos.x = event.GetX();
    prevMousePos.y = event.GetY();
    prevMousePos.z = 0;

    // Calculate ray path

    updateRayPaths();

    mainPanel->Refresh();
    log_printf(CRYSTAL_EDITOR_MOUSE_MOVE, "========================\n");
}

void CrystalEditorFrame::OnMouseWheel(wxMouseEvent& event)
{
    // Zooming in and out.
    int rotation = event.GetWheelRotation();
    const double ROTATION_FACTOR = 0.01;
    const double SCALE_EXPONENT = 0.95;
    double realRotation = rotation * ROTATION_FACTOR;

    distance *= pow(SCALE_EXPONENT, realRotation);

    mainPanel->Refresh();
}

void CrystalEditorFrame::OnKeyDown(wxKeyEvent& event)
{
    // Controlling the view.
    Matrix T;
    Vector3 tmp;
    int keyCode = event.GetKeyCode();
    const double STEP = 0.01;

    switch (keyCode)
    {
        case WXK_LEFT:
        {
            tmp = -STEP * right;
        }
        break;
        case WXK_RIGHT:
        {
            tmp = STEP * right;
        }
        break;
        case WXK_UP:
        {
            tmp = STEP * upward;
        }
        break;
        case WXK_DOWN:
        {
            tmp = -STEP * upward;
        }
        break;
        case 'W':
        {
            tmp = -STEP * backward;
        }
        break;
        case 'S':
        {
            tmp = STEP * backward;
        }
        break;
        default:
            return;
    }

    target -= tmp;

    updateRayPaths();
    mainPanel->Refresh();
}

void CrystalEditorFrame::OnKeyUp(wxKeyEvent& event)
{
}

void CrystalEditorFrame::OnAddCrystalToDisplayItemSelected(wxCommandEvent& event)
{
    AddCrystalToDisplayDialog dlg(this);
    if (dlg.ShowModal() == wxID_OK)
    {
        CrystalDescriptor cd;
        cd.name = std::string(dlg.crystalNameTextBox->GetValue().ToUTF8());
        cd.mesh = crystalMesh;
        cd.orientation = CrystalDescriptor::OT_RANDOM;
        cd.populationWeight = 1;
        cd.wobbliness = 0;
        crystalMeshes->push_back(cd);
    }

}

void CrystalEditorFrame::OnCastRayMenuItemSelected(wxCommandEvent& event)
{
    SetCursor(*wxCROSS_CURSOR);
    rayCastingMode = true;
}

void CrystalEditorFrame::OnRightDown(wxMouseEvent& event)
{
    if (rayCastingMode)
    {
        SetCursor(wxNullCursor);
        rayCastingMode = false;
    }
}

void CrystalEditorFrame::OnGenerateOctahedronMenuItemSelected(wxCommandEvent& event)
{
    crystalMesh.vertices.clear();
    crystalMesh.faces.clear();

    crystalMesh.vertices.push_back(Vector3(0, 1, 0)); // Top apex

    // side vertices
    crystalMesh.vertices.push_back(Vector3(-1, 0, 0));
    crystalMesh.vertices.push_back(Vector3(0, 0, -1));
    crystalMesh.vertices.push_back(Vector3(1, 0, 0));
    crystalMesh.vertices.push_back(Vector3(0, 0, 1));

    crystalMesh.vertices.push_back(Vector3(0, -1, 0)); // Bottom apex

    vector<int> face;

    face.clear();
    face.push_back(0);
    face.push_back(1);
    face.push_back(2);
    crystalMesh.faces.push_back(face);

    face.clear();
    face.push_back(0);
    face.push_back(2);
    face.push_back(3);
    crystalMesh.faces.push_back(face);

    face.clear();
    face.push_back(0);
    face.push_back(3);
    face.push_back(4);
    crystalMesh.faces.push_back(face);

    face.clear();
    face.push_back(0);
    face.push_back(4);
    face.push_back(1);
    crystalMesh.faces.push_back(face);

    face.clear();
    face.push_back(5);
    face.push_back(1);
    face.push_back(2);
    crystalMesh.faces.push_back(face);

    face.clear();
    face.push_back(5);
    face.push_back(2);
    face.push_back(3);
    crystalMesh.faces.push_back(face);

    face.clear();
    face.push_back(5);
    face.push_back(3);
    face.push_back(4);
    crystalMesh.faces.push_back(face);

    face.clear();
    face.push_back(5);
    face.push_back(4);
    face.push_back(1);
    crystalMesh.faces.push_back(face);

    mainPanel->Refresh();
}

void CrystalEditorFrame::OnEraseBackground(wxEraseEvent& event)
{
    event.Skip();
}
