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

void transformMesh(Mesh &mesh, const Matrix &transformation);

double clampIn(double x, double a, double b);

void drawLine3d(
    wxDC &hdc,
    const Matrix &combined,
    const Vector3 &a,
    const Vector3 &b
);

inline double randFloat() {return rand() / (double)RAND_MAX;}

inline double randFloat(double min, double max) {return min + randFloat() * (max - min);}

double randFloatNormal(double center, double variance);

int clampInInt(int x, int a, int b);
double clampIn(double x, double a, double b);


#endif // UTILS_H
