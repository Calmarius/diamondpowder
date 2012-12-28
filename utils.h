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
 * @file utils.h
 *
 * Some program wide utility functions.
 */

#ifndef UTILS_H
#define UTILS_H

enum RenderMode
{
    RM_WIREFRAME
};

/**
 * Renders the mesh on the given DC
 */
void renderMeshOnDC
(
    wxDC &hdc, ///< handle of device context.
    const Mesh &mesh, ///< mesh to render.
    Matrix transformationMatrix, ///< the current transformation matrix
    RenderMode mode ///< Rendering mode
);

/**
 * Casts ray on a triangle. Returns true, if the ray hits the triangle.
 */
bool castRay(
    const Vector3 &position,  ///< Position the ray shot from.
    const Vector3 &ray,  ///< The direction of the ray
    const Vector3 &A,  ///< Vertex of the triangle
    const Vector3 &B,  ///< Vertex of the triangle
    const Vector3 &C,  ///< Vertex of the triangle
    double &u, ///< Baricentric coordinate on the triangle, coefficient of the AB axis.
    double &v, ///< Baricentric coordinate on the triangle, coefficient of the AC axis.
    double &w ///< Distance of the hit point in units of the ray vector.
);

/**
 * Computes ray path through a glass object.
 */
void computeRayPathInGlassMesh
(
    Mesh &mesh, ///< mesh of the object.
    double refratctionIndex, ///< Optical refraction index.
    Vector3 rayPos, ///< The position the ray shot from
    Vector3 rayDir, ///< Direction of the ray
    std::vector<Vector3> &path ///< List of the points of the path.
);

typedef std::vector<std::pair<Vector3, double> > RayPath;

void computeRayPathInGlassMesh
(
    Mesh &mesh, ///< mesh of the object.
    double refractiveIndex, ///< Optical refraction index.
    Vector3 rayPos, ///< The position the ray shot from
    Vector3 rayDir, ///< Direction of the ray
    double cutOffIntensity, ///< The weakest ray to consider
    std::vector<RayPath> &paths ///< List of the ray paths.
);

/*
 * Exposed for test only.
  */
bool castRayOnMesh(
    const Mesh &mesh,
    int skipFaceIndex,
    Vector3 rayPos,
    Vector3 rayDir,
    double &u,
    double &v,
    double &w,
    int &faceIndex
);

/**
 * Transforms mesh points with the given matrix.
 */
void transformMesh(Mesh &mesh, const Matrix &transformation);

/**
 * If the given x value fall outside the [a,b] interval, it will be clamped to be inside in the interval.
 */
double clampIn(double x, double a, double b);

/**
 * Draws a 3D line.
 */
void drawLine3d(
    wxDC &hdc, ///< Device context
    const Matrix &combined, ///< Combined rendering matrix.
    const Vector3 &a, ///< Start point of the line.
    const Vector3 &b ///< End point of the line.
);

/**
 * Generates uniform random float in [0,1[ interval.
 */
inline double randFloat() {return rand() / (double)RAND_MAX;}

/**
 * Generates uniform random float in [min,max[ interval.
 */
inline double randFloat(double min, double max) {return min + randFloat() * (max - min);}

/**
 * Generates normal distribution random floating point number with the given expected value and variance.
 */
double randFloatNormal(double center, double variance);

/**
 * If the given x value fall outside the [a,b] interval, it will be clamped to be inside in the interval.
 */
int clampInInt(int x, int a, int b);


#endif // UTILS_H
