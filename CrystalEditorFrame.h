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

		RayPathDescriptor rayPathDescriptor;

		Vector3 right;
		Vector3 upward;
		Vector3 backward;
		Vector3 target;
		double distance;

		std::vector<CrystalDescriptor> *crystalMeshes;

		bool dragging;
		Vector3 prevMousePos;

		Vector3 rayPos;
		Vector3 rayDir;

		Mesh crystalMesh;
		wxPen redPen, greenPen, bluePen;

		static const int COLOR_COUNT = 3;
		Ray rayPaths[COLOR_COUNT];

		bool rayCastingMode;

		DECLARE_EVENT_TABLE()
};

#endif
