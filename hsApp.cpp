/***************************************************************
 * Name:      hsApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Calmarius (calmarius@calmarius.net)
 * Created:   2012-10-21
 * Copyright: Calmarius (calmarius.net)
 * License:
 **************************************************************/

//(*AppHeaders
#include "hsMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(hsApp)

bool hsApp::OnInit()
{
    /* RUN SOME TESTS */

    // Test cross product

    {
        Vector3 tmp = Vector3(1, 0, 0) % Vector3(0, 1, 0);
        assert(tmp.x == 0);
        assert(tmp.y == 0);
        assert(tmp.z == 1);
    }

    // Test rotation

    {
        Vector3 axis(0, 0, 1);
        Vector3 v(1, 0, 0);
        Matrix rotate = createRotationMatrix(axis, 3.1415926536 / 2);
        Vector3 r = transformVector(rotate, v);
        assert(fabs(r.x - 0) < 1e-6);
        assert(fabs(r.y - 1) < 1e-6);
        assert(fabs(r.z - 0) < 1e-6);
    }

    // Test castRay

    // Trivial test, hit a triangle at its center
    double u, v, w;
    bool result = castRay(Vector3(0, 0, 0), Vector3(0, 0, -1), Vector3(0, 1, -2), Vector3(-1, -1, -2), Vector3(1, -1, -2), u, v, w);
    assert(result);
    assert(fabs(u - 0.25) < 1e-6);
    assert(fabs(v - 0.25) < 1e-6);
    assert(fabs(w - 2) < 1e-6);
    // Test when outside of the AB edge
    assert(!castRay(Vector3(-1, 0, 0), Vector3(0, 0, -1), Vector3(0, 1, -2), Vector3(-1, -1, -2), Vector3(1, -1, -2), u, v, w));
    // Test when outside of the AC edge
    assert(!castRay(Vector3(1, 0, 0), Vector3(0, 0, -1), Vector3(0, 1, -2), Vector3(-1, -1, -2), Vector3(1, -1, -2), u, v, w));
    // Test when outside of the BC edge
    assert(!castRay(Vector3(0, -1.1, 0), Vector3(0, 0, -1), Vector3(0, 1, -2), Vector3(-1, -1, -2), Vector3(1, -1, -2), u, v, w));
    // Test when ray points to the wrong direction
    assert(!castRay(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, -2), Vector3(-1, -1, -2), Vector3(1, -1, -2), u, v, w));
    // Test when ray is parallel with the triangle.
    assert(!castRay(Vector3(0, 0, 0), Vector3(1, 0, 0), Vector3(0, 1, -2), Vector3(-1, -1, -2), Vector3(1, -1, -2), u, v, w));

    // Test castRayOnMesh

    Mesh mesh;

    initMesh(mesh);

    // back face
    mesh.vertices.push_back(Vector3(-1, -1, -1));
    mesh.vertices.push_back(Vector3(-1, 1, -1));
    mesh.vertices.push_back(Vector3(1, 1, -1));
    mesh.vertices.push_back(Vector3(1, -1, -1));
    // front face
    mesh.vertices.push_back(Vector3(-1, -1, 1));
    mesh.vertices.push_back(Vector3(-1, 1, 1));
    mesh.vertices.push_back(Vector3(1, 1, 1));
    mesh.vertices.push_back(Vector3(1, -1, 1));

    vector<int> face;
    face.push_back(0);
    face.push_back(1);
    face.push_back(2);
    face.push_back(3);
    mesh.faces.push_back(face);

    face.clear();
    face.push_back(4);
    face.push_back(5);
    face.push_back(6);
    face.push_back(7);
    mesh.faces.push_back(face);

    face.clear();
    face.push_back(0);
    face.push_back(1);
    face.push_back(5);
    face.push_back(4);
    mesh.faces.push_back(face);

    face.clear();
    face.push_back(2);
    face.push_back(3);
    face.push_back(7);
    face.push_back(6);
    mesh.faces.push_back(face);

    face.clear();
    face.push_back(1);
    face.push_back(5);
    face.push_back(6);
    face.push_back(2);
    mesh.faces.push_back(face);

    face.clear();
    face.push_back(0);
    face.push_back(4);
    face.push_back(7);
    face.push_back(3);
    mesh.faces.push_back(face);

    int hitFace;

    // Test front face hitting
    result = castRayOnMesh(mesh, -1, Vector3(0.1, 0.1, 3), Vector3(0, 0, -1), u, v, w, hitFace);
    assert(result);
    assert(hitFace == 1);
    // Test back face hitting
    result = castRayOnMesh(mesh, -1, Vector3(0.1, 0.1, -3), Vector3(0, 0, 1), u, v, w, hitFace);
    assert(result);
    assert(hitFace == 0);
    // Test skip face (so it should skip the front face and hit the back face)
    result = castRayOnMesh(mesh, 1, Vector3(0.1, 0.1, -3), Vector3(0, 0, 1), u, v, w, hitFace);
    assert(result);
    assert(hitFace == 0);

    /*END TESTS*/

    srand(time(0));
    setlocale(LC_NUMERIC, "C");
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	hsFrame* Frame = new hsFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
