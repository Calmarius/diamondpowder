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


/***************************************************************
 * @file      hsMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Calmarius (calmarius@calmarius.net)
 * Created:   2012-10-21
 * Copyright: Calmarius (calmarius.net)
 * License:
 **************************************************************/

//(*InternalHeaders(hsFrame)
#include <wx/string.h>
#include <wx/intl.h>
//*)

const char *CrystalDescriptor::orientationTypes[OT_MAX_ORIENTATIONTYPE] =
{
    "Random",
    "Parry",
    "Column",
    "Plate",
    "Lowitz"
};

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(hsFrame)
const long hsFrame::idMenuQuit = wxNewId();
const long hsFrame::ID_MENU_OPENCRYSTALEDITOR = wxNewId();
const long hsFrame::ID_MENUITEM1 = wxNewId();
const long hsFrame::ID_MENUITEM2 = wxNewId();
const long hsFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(hsFrame,wxFrame)
    //(*EventTable(hsFrame)
    //*)
END_EVENT_TABLE()

hsFrame::hsFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(hsFrame)
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuItem* renderMenuItem;
    wxMenuBar* MenuBar1;

    Create(parent, id, _("Halo simulator"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(600,315));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    openCrystalEditorMenuItem = new wxMenuItem(Menu3, ID_MENU_OPENCRYSTALEDITOR, _("Crystal editor..."), _("Opens the cristal editor where you can set the vertices of the crystal."), wxITEM_NORMAL);
    Menu3->Append(openCrystalEditorMenuItem);
    crystalCompositionEditorMenuItem = new wxMenuItem(Menu3, ID_MENUITEM1, _("Crystal composition editor..."), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(crystalCompositionEditorMenuItem);
    MenuBar1->Append(Menu3, _("Crystals"));
    Menu2 = new wxMenu();
    renderMenuItem = new wxMenuItem(Menu2, ID_MENUITEM2, _("Render..."), _("Renders the halo display with the given parameters"), wxITEM_NORMAL);
    Menu2->Append(renderMenuItem);
    MenuBar1->Append(Menu2, _("Rendering"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&hsFrame::OnQuit);
    Connect(ID_MENU_OPENCRYSTALEDITOR,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&hsFrame::OnopenCrystalEditorMenuItemSelected);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&hsFrame::OnCrystalCompositionEditorMenuItemSelected);
    Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&hsFrame::OnRenderMenuItemSelected);
    Connect(wxEVT_KEY_DOWN,(wxObjectEventFunction)&hsFrame::OnKeyDown);
    //*)

}

hsFrame::~hsFrame()
{
    //(*Destroy(hsFrame)
    //*)

}

void hsFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void hsFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void hsFrame::OnopenCrystalEditorMenuItemSelected(wxCommandEvent& event)
{
    credFrame = new CrystalEditorFrame(crystalClasses, this);
    credFrame->Show();
}

void hsFrame::OnKeyDown(wxKeyEvent& event)
{
}

void hsFrame::OnCrystalCompositionEditorMenuItemSelected(wxCommandEvent& event)
{
    compositionEditorDialog = new CrystalCompositionEditorDialog(crystalClasses, this);
    compositionEditorDialog->Show();
}

void hsFrame::OnRenderMenuItemSelected(wxCommandEvent& event)
{
    RenderSetupDialog rsd(this);
    if (rsd.ShowModal() == wxID_OK)
    {
        long tmp;
        double tmpf;
        renderingSetupStruct.crystals = crystalClasses;
        if (!rsd.crystalCountTextBox->GetValue().ToLong(&tmp))
        {
            wxMessageBox(wxT("Crystal count is invalid number."));
            return;
        }
        renderingSetupStruct.crystalCount = tmp;
        if (!rsd.imageSizeTextBox->GetValue().ToLong(&tmp))
        {
            wxMessageBox(wxT("Image size is invalid number."));
            return;
        }
        renderingSetupStruct.imageSize = tmp;
        if (!rsd.solarDiskRadiusTextBox->GetValue().ToDouble(&tmpf))
        {
            wxMessageBox(wxT("Solar disk radius is invalid number."));
            return;
        }
        renderingSetupStruct.solarDiskRadius = tmpf;
        if (!rsd.solarAltitudeTextBox->GetValue().ToDouble(&tmpf))
        {
            wxMessageBox(wxT("Solar altitude is invalid number."));
            return;
        }
        renderingSetupStruct.solarAltitude = tmpf;
        if (!rsd.pixelIntensityTextBox->GetValue().ToDouble(&tmpf))
        {
            wxMessageBox(wxT("Pixel intensity is invalid number."));
            return;
        }
        renderingSetupStruct.pixelIntensity = tmpf;
        if (!rsd.maxRayCastInfoTextBox->GetValue().ToLong(&tmp))
        {
            wxMessageBox(wxT("Max raycasting info is invalid number."));
            return;
        }
        renderingSetupStruct.maxRayCastInfoSize = tmp;

        renderingProcessFrame = new RenderingProcessFrame(renderingSetupStruct, this);
        renderingProcessFrame->Show();
        renderingProcessFrame->Center();

    }
}
