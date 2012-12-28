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
 * @file CrystalEditorFrame.h
 *
 * The crystal editor's windows.
 */

#ifndef CRYSTALEDITORFRAME_H
#define CRYSTALEDITORFRAME_H

//(*Headers(CrystalEditorFrame)
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

class CrystalEditorFrame: public wxFrame
{
	public:

        // Normal constructor
		CrystalEditorFrame(std::vector<CrystalDescriptor> &crystalMeshes, wxWindow* parent,wxWindowID id=wxID_ANY);
        // Raytracing constructor, many options disabled
		CrystalEditorFrame(const RayPathDescriptor &rtd, wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~CrystalEditorFrame();

		//(*Declarations(CrystalEditorFrame)
		wxPanel* mainPanel;
		wxMenuItem* castRayMenuItem;
		wxMenu* Menu3;
		wxMenuItem* addCrystalToDisplayItem;
		wxMenu* Menu1;
		wxStatusBar* StatusBar1;
		wxMenuItem* generateOctahedronMenuItem;
		wxMenuBar* MenuBar1;
		wxMenu* Menu2;
		//*)

	protected:

		//(*Identifiers(CrystalEditorFrame)
		static const long ID_PANEL1;
		static const long ID_MENUITEM_GENHEXAGONALPRISM;
		static const long ID_MENUITEM3;
		static const long ID_MENUITEM1;
		static const long ID_MENUITEM2;
		static const long ID_STATUSBAR1;
		//*)

	private:

		//(*Handlers(CrystalEditorFrame)
		void OnGenerateHexagonalPrismMenuItemSelected(wxCommandEvent& event);
		void OnPaint(wxPaintEvent& event);
		void OnLeftDown(wxMouseEvent& event);
		void OnLeftUp(wxMouseEvent& event);
		void OnMouseMove(wxMouseEvent& event);
		void OnMouseWheel(wxMouseEvent& event);
		void OnKeyDown(wxKeyEvent& event);
		void OnKeyUp(wxKeyEvent& event);
		void OnTextCtrl1Text(wxCommandEvent& event);
		void OnmainPanelPaint(wxPaintEvent& event);
		void OnAddCrystalToDisplayItemSelected(wxCommandEvent& event);
		void OnCastRayMenuItemSelected(wxCommandEvent& event);
		void OnRightDown(wxMouseEvent& event);
		void OnGenerateOctahedronMenuItemSelected(wxCommandEvent& event);
		void OnEraseBackground(wxEraseEvent& event);
		//*)

        // Comon initializer function
		void initialize(wxWindow *parent, wxWindowID id);

		void updateRayPaths();

		double minimumIntensity; ///< Intensity of the casted rays will be clamped up to this value.

		struct Ray
		{
            std::vector<std::vector<std::pair<Vector3, double> > > rayPaths;
            double refractionIndex;
            wxPen pen;
		};

        /// Used when the editor window created with a predefined crystal orientation and ray path.
		RayPathDescriptor rayPathDescriptor;

        /// Location and orientation and target vectors of the camera.
        /// @{
		Vector3 right;
		Vector3 upward;
		Vector3 backward;
		Vector3 target;
		/// @}
		double distance; ///< Distance from the target.

		std::vector<CrystalDescriptor> *crystalMeshes; ///< Reference to the global crystal mesh collection.

		bool dragging; ///< true when we rotate the crystal.
		Vector3 prevMousePos; ///< previous mouse pos to get relative movement.

        /// Position and direction of the current ray.
        /// @{
		Vector3 rayPos;
		Vector3 rayDir;
		/// @}

		Mesh crystalMesh; ///< The current crystal mesh.
		wxPen redPen, greenPen, bluePen; ///< Pens drawing the rays.

		static const int COLOR_COUNT = 3; ///< Count of ray colors.
		Ray rayPaths[COLOR_COUNT]; ///< Ray paths of different color rays.

		bool rayCastingMode; ///< True when the next clicks sets up a new ray.

		DECLARE_EVENT_TABLE()
};

#endif
