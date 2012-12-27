/***************************************************************
 * Name:      hsMain.h
 * Purpose:   Defines Application Frame
 * Author:    Calmarius (calmarius@calmarius.net)
 * Created:   2012-10-21
 * Copyright: Calmarius (calmarius.net)
 * License:
 **************************************************************/

#ifndef HSMAIN_H
#define HSMAIN_H

//(*Headers(hsFrame)
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
//*)

struct RayPathId
{
    int planeId; ///< Which plane it's on.
    int x, y; ///< position of pixel

    bool operator<(const RayPathId &path) const
    {
        if (planeId < path.planeId) return true;
        if (planeId > path.planeId) return false;
        if (x < path.x) return true;
        if (x > path.x) return false;
        if (y < path.y) return true;
        return false;
    }

    RayPathId(int _planeId, int _x, int _y)
    {
        x = _x;
        y = _y;
        planeId = _planeId;
    }
};

struct RayPathDescriptor
{
    Mesh *mesh; ///< Unmodified mesh of the crystal
    Matrix orientation; ///< orientation of the crystal
    Vector3 rayPos; ///< Ray position
    Vector3 rayDir; ///< Ray direction
    double intensity; ///< Intensity of the exiting ray.

    RayPathDescriptor(
        Mesh *_mesh,
        const Matrix &_orientation,
        const Vector3 _rayPos,
        const Vector3 _rayDir,
        double _intensity)
    {
        mesh = _mesh;
        orientation = _orientation;
        rayPos = _rayPos;
        rayDir = _rayDir;
        intensity = _intensity;
    }

    RayPathDescriptor() {};
};

struct HaloRenderingSetupStruct
{
    // INPUT ARGUMENTS
    std::vector<CrystalDescriptor> crystals;
    size_t crystalCount;
    size_t imageSize; // a×a in pixels
    double solarDiskRadius; // In degrees.
    wxEvtHandler *notifee; // Sends event to this
    bool cancelled; // Set true during the operation to cancel the rendering. (If rendering is done in a working thread.)
    double solarAltitude; // in degrees
    double pixelIntensity; // how intense a single pixel should be (default 1)
    size_t maxRayCastInfoSize; // Maximum amount of raycasting info.
    // OUTPUT ARGUMENTS
    bool resultValid; // True if calculation finished successfully.
    size_t imageWidth; // in pixels.
    size_t imageHeight; // in pixels.
    // A buffer of integer values as a result of the rendering.
    // It's stored in row mayor order.
    // 6 images are stored, to get a full 360° panorama.
    // The buffer is released if the operation is cancelled
    uint32_t *imageBuffer;
    std::map<RayPathId, RayPathDescriptor> *rayPaths;
    // A function that should be called to release the image buffer.
    void (*deleteBuffer)(uint32_t *buffer);
    void (*deleteMap)(std::map<RayPathId, RayPathDescriptor> *rayPaths);
};

struct CrystalDescriptor
{
    enum OrientationType
    {
        OT_RANDOM,
        OT_PARRY,
        OT_COLUMN,
        OT_PLATE,
        OT_LOWITZ,

        OT_MAX_ORIENTATIONTYPE
    };
    static const char *orientationTypes[OT_MAX_ORIENTATIONTYPE];

    std::string name;
    Mesh mesh;
    OrientationType orientation;
    double populationWeight;
    double wobbliness;
};

class CrystalEditorFrame;
class RenderingProcessFrame;

class hsFrame: public wxFrame
{
    public:

        hsFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~hsFrame();

    private:

        //(*Handlers(hsFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnopenCrystalEditorMenuItemSelected(wxCommandEvent& event);
        void OnKeyDown(wxKeyEvent& event);
        void OnCrystalCompositionEditorMenuItemSelected(wxCommandEvent& event);
        void OnRenderMenuItemSelected(wxCommandEvent& event);
        //*)

        CrystalEditorFrame *credFrame;
        CrystalCompositionEditorDialog *compositionEditorDialog;
        RenderingProcessFrame *renderingProcessFrame;

        //(*Identifiers(hsFrame)
        static const long idMenuQuit;
        static const long ID_MENU_OPENCRYSTALEDITOR;
        static const long ID_MENUITEM1;
        static const long ID_MENUITEM2;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(hsFrame)
        wxStatusBar* StatusBar1;
        wxMenu* Menu3;
        wxMenuItem* crystalCompositionEditorMenuItem;
        wxMenu* Menu2;
        wxMenuItem* openCrystalEditorMenuItem;
        //*)

        HaloRenderingSetupStruct renderingSetupStruct;

        std::vector<CrystalDescriptor> crystalClasses;

        DECLARE_EVENT_TABLE()
};

#endif // HSMAIN_H
