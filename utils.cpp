using namespace std;

void drawLine3d(
    wxDC &hdc,
    const Matrix &combined,
    const Vector3 &a,
    const Vector3 &b)
{
    double A[4];
    double B[4];

    const double CLIP_Z = 0.5;

    transformVector4d(combined, a, A);
    transformVector4d(combined, b, B);
    /*
    log_var(RENDERING_LOG, A[0]);
    log_var(RENDERING_LOG, A[1]);
    log_var(RENDERING_LOG, A[2]);
    log_var(RENDERING_LOG, A[3]);

    log_var(RENDERING_LOG, B[0]);
    log_var(RENDERING_LOG, B[1]);
    log_var(RENDERING_LOG, B[2]);
    log_var(RENDERING_LOG, B[3]);
    */
    // After the transformation W coordinate is the Z, Z coordinate is the W.
    // Here, positive Z is forward, negative is backward.
    // as we need to divide all others with it.
    double aZ = A[3] / A[2]; //< Calculate Z/W
    double bZ = B[3] / B[2];

    if ((aZ < CLIP_Z) && (bZ < CLIP_Z))
    {
        // Both Z-s are too near no line drawn.
        log_var(RENDERING_LOG, aZ);
        log_var(RENDERING_LOG, bZ);
        log_printf(RENDERING_LOG, "No lines are drawn.\n");
        return;
    }

    // calculate the interpolation factor 0.01 added to correct errors.
    double k = ((CLIP_Z + 0.01)- aZ) / (bZ - aZ);

    if ((0 < k) && (k < 1))
    {
        // interpolation factor in the range, the line must be clipped.
        log_var(RENDERING_LOG, k);
        log_var(RENDERING_LOG, a);
        log_var(RENDERING_LOG, b);
        Vector3 tmp = a + (1-k)*(b-a);
        log_var(RENDERING_LOG, tmp);
        if (aZ < CLIP_Z)
        {
            log_printf(RENDERING_LOG, "Cut down from A side, recursively called.\n");
            drawLine3d
            (
                hdc,
                combined,
                a + k*(b-a),
                b
            );
            return;
        }
        else if (bZ < CLIP_Z)
        {
            log_printf(RENDERING_LOG, "Cut down from B side, recursively called.\n");
            drawLine3d
            (
                hdc,
                combined,
                a,
                a + k*(b-a)
            );
            return;
        }
    }
    // All is ok normalize and draw the line as usual.
    Vector3 nA(A[0], A[1], A[2]);
    Vector3 nB(B[0], B[1], B[2]);

    nA /= A[3];
    nB /= B[3];

    //log_printf(RENDERING_LOG, "Line drawn normally");
    hdc.DrawLine(nA.x, nA.y, nB.x, nB.y);
}



void renderMeshOnDC(
    wxDC &hdc, ///< handle of device context.
    const Mesh &mesh, ///< mesh to render.
    Matrix transformationMatrix, ///< the current transformation matrix
    RenderMode mode ///< Rendering mode
)
{
    Matrix &combined = transformationMatrix;
    wxPen red(wxColour(255, 0, 0));
    wxPen green(wxColour(0, 255, 0));
    wxPen blue(wxColour(0, 0, 255));

    Vector3 zero(0,0,0);
    Vector3 xDir(1, 0, 0);
    Vector3 yDir(0, 1, 0);
    Vector3 zDir(0, 0, 1);

    for (unsigned int i = 0; i < mesh.faces.size(); i++)
    {
        const vector<int> &face = mesh.faces[i];
        //const volatile int *f = &face[0];
        //volatile int size = face.size();
        for (unsigned int j = 0; j < face.size(); j++)
        {
            int k = j + 1 == face.size() ? 0 : j + 1;
            drawLine3d(hdc, combined, mesh.vertices[face[j]], mesh.vertices[face[k]]);
/*            Vector3 a = transformVector(combined, mesh.vertices[face[j]]);
            Vector3 b = transformVector(combined, mesh.vertices[face[k]]);
            hdc.DrawLine(a.x, a.y, b.x, b.y);*/
        }
    }
}

bool castRay(
    const Vector3 &P,
    const Vector3 &r,
    const Vector3 &A,
    const Vector3 &B,
    const Vector3 &C,
    double &u,
    double &v,
    double &w
)
{
    // Side vectors of the triangle.
    Vector3 a = B - A;
    Vector3 b = C - A;
    Vector3 s = A - P; //< Vector pointing from the position, to the A vertex.

    double d = -a * (-b % r); //< Main determinant, got by a triple product.

    if (d == 0)
    {
        // The ray is exactly parallel with the triangle, no hit.
        return false;
    }

    double rd = 1 / d;

    // Calculate the solution using the Cramer's formula.

    u = s * (-b % r) * rd;
    v = -a * (s % r) * rd;
    w = -a * (-b % s) * rd;


    // Check the solution.
    if (u < 0) return false; //< intesection point outside the triangle.
    if (v < 0) return false; //< intesection point outside the triangle.
    if (u + v > 1) return false; //< intesection point outside the triangle.
    if (w < 0) return false; //< Intersection point behind us.

    return true;
}

static bool castRayOnMeshFace(
    const Mesh &mesh,
    const vector<int> face,
    Vector3 rayPos,
    Vector3 rayDir,
    double &u,
    double &v,
    double &w
)
{
    Vector3 firstVertex = mesh.vertices[face[0]];
    for (size_t i = 1; i < face.size() - 1; i++)
    {
        bool result = castRay(
            rayPos,
            rayDir,
            firstVertex,
            mesh.vertices[face[i]],
            mesh.vertices[face[i + 1]],
            u,
            v,
            w
        );
        if (result) return true;
    }
    return false;
}

bool castRayOnMesh(
    const Mesh &mesh,
    int skipFaceIndex,
    Vector3 rayPos,
    Vector3 rayDir,
    double &u,
    double &v,
    double &w,
    int &faceIndex
)
{
    double nearestIntersection = numeric_limits<double>().max();
    faceIndex = -1;
    double nearestU, nearestV;

    for (size_t i = 0; i < mesh.faces.size(); i++)
    {
        if (i == (size_t)skipFaceIndex) continue;

        const vector<int> &face = mesh.faces[i];

        bool result = castRayOnMeshFace(
            mesh,
            face,
            rayPos,
            rayDir,
            u,
            v,
            w
        );

        if (result)
        {
            // A face is hit with ray.
            if (w < nearestIntersection)
            {
                nearestIntersection = w;
                nearestU = u;
                nearestV = v;
                faceIndex = i;
            }
        }
    }
    w = nearestIntersection;
    u = nearestU;
    v = nearestV;
    return faceIndex != -1;
}

static Vector3 getMeshFaceNormalVector(
    const Mesh &mesh,
    int faceIndex
)
{
    const vector<int> &face = mesh.faces[faceIndex];

    const Vector3 a = mesh.vertices[face[0]];
    const Vector3 b = mesh.vertices[face[1]];
    const Vector3 c = mesh.vertices[face[2]];

    return (b - a)%(c - a);
}

/**
 * Computes ray path through a glass object.
 */
void computeRayPathInGlassMesh
(
    Mesh &mesh, ///< mesh of the object.
    double refractiveIndex, ///< Optical refraction index.
    Vector3 rayPos, ///< The position the ray shot from
    Vector3 rayDir, ///< Direction of the ray
    std::vector<Vector3> &path ///< List of the points of the path.
)
{
    int skipFaceIndex = -1; //< The index of face that's skipped in each iteration (because previously hit by a ray)
    double u, v, w;
    int currentFaceIndex;
    bool inside = false; //< true if currently we are inside the glass
    double recRefIndex = 1.0 / refractiveIndex;
    const int MAX_BOUNCE = 50;
    int bouncesLeft = MAX_BOUNCE;

    path.clear();

    path.push_back(rayPos);
    while (castRayOnMesh(mesh, skipFaceIndex, rayPos, rayDir, u, v, w, currentFaceIndex))
    {
        if (!bouncesLeft)
        {
            // Count of bounces are limited.
            break;
        }
        // The mesh is hit with the ray.
        // Compute the hit point
        Vector3 hitPoint = rayPos + w*rayDir;
        // Compute the new direction
        // We need the face normal for that.
        Vector3 faceNormal = getMeshFaceNormalVector(mesh, currentFaceIndex);
        // Calculate the angle of incidence
        double cosIncidenceAngle = (faceNormal * rayDir)/(~faceNormal * ~rayDir);
        // If it's higher than 90° then normalize it:
        if (cosIncidenceAngle < 0)
        {
            cosIncidenceAngle = - cosIncidenceAngle;
            faceNormal = -faceNormal; //< Reverse the normal as to make it point inside.
        }
        double incidenceAngle = acos(cosIncidenceAngle);
        // Calculate the refraction angle and the new direction.
        double currentRecRefIndex = inside ? refractiveIndex : recRefIndex;
        double sinRefractedAngle = currentRecRefIndex * sin(incidenceAngle);
        double refractedAngle;
        Vector3 refPlaneNormal = faceNormal % rayDir; //< Refraction plane normal vector.
        refPlaneNormal /= ~refPlaneNormal;
        if (sinRefractedAngle > 1)
        {
            // Total internal reflection happens
            refractedAngle = PI - incidenceAngle;
        }
        else
        {
            // The ray enters the surface.
            refractedAngle = asin(sinRefractedAngle);
            // Switch medium.
            inside = !inside;
        }
        // We have the angle now. Use the refraction plane normal to rotate face normal, to get the new direction.
        Matrix rotation = createRotationMatrix(refPlaneNormal, refractedAngle);
        Vector3 newRayDir = transformVector(rotation, faceNormal);
        // Done.
        path.push_back(hitPoint); //< Add the hit point. the path
        // Set up the new ray.
        rayDir = newRayDir;
        rayPos = hitPoint;
        skipFaceIndex = currentFaceIndex;
        // Reduce bounce count
        bouncesLeft--;
    }
    // The ray missed or left the mesh.
    // Add a final point to the path to see the direction of the leaving.
    path.push_back(rayPos + 1 * rayDir);
}

struct CRPIGM_RayTreeNode
{
    Vector3 start;
    Vector3 direction;
    double intensity; ///< between 0 and 1.
    int parentIndex; ///< negative for root, otherwise 0 or positive.
    int skipFaceIndex; ///< negative when no face skipped, nonnegative otherwise.
    int nBounces; ///< The number of bounces, the calculation stops after a predefined number of bounces.
    bool inside; ///< True if the ray is going inside the medium
};

/**
 * Computes ray path through a glass object.
 *
 * A ray path is set of point, intensity pairs. The intensity of each point
 * denotes the intensity of the ray to the next point. The initial intensity is 1.
 */
void computeRayPathInGlassMesh
(
    Mesh &mesh, ///< mesh of the object.
    double refractiveIndex, ///< Optical refraction index.
    Vector3 rayPos, ///< The position the ray shot from
    Vector3 rayDir, ///< Direction of the ray
    double cutOffIntensity, ///< The weakest ray to consider
    std::vector<RayPath> &paths ///< List of the ray paths.
)
{
    vector<CRPIGM_RayTreeNode> rayTree;
    const int MAX_BOUNCE = 50;
    double recRefIndex = 1.0 / refractiveIndex;

    CRPIGM_RayTreeNode root;
    root.start = rayPos;
    root.direction = rayDir;
    root.intensity = 1;
    root.parentIndex = -1;
    root.nBounces = 0;
    root.skipFaceIndex = -1;
    root.inside = false;

    rayTree.push_back(root);

    paths.clear();

    log_printf(REFRACTION_LOG, "===================\n");

    for (size_t i = 0; i < rayTree.size(); i++)
    {
        CRPIGM_RayTreeNode currentNode = rayTree[i];
        double u, v, w;
        int hitFaceIndex;

        if (i > 1000)
        {
            log_printf(REFRACTION_LOG, "Runaway allocation!");
            return;
        }

        log_printf(REFRACTION_LOG, "Casting ray #%d:\n", i);
        log_var(REFRACTION_LOG, currentNode.start);
        log_var(REFRACTION_LOG, currentNode.direction);
        log_var(REFRACTION_LOG, currentNode.intensity);

        if (
            (root.nBounces >= MAX_BOUNCE) ||
            (!castRayOnMesh(
                mesh,
                currentNode.skipFaceIndex,
                currentNode.start,
                currentNode.direction,
                u, v, w,
                hitFaceIndex)
            )
        )
        {
            log_printf(REFRACTION_LOG, "Ray does not hit the mesh.\n");
            // Ray does not hit the mesh, so the path is ready. Setup a ray path and save it.
            vector<pair<Vector3, double> > path;
            path.push_back(pair<Vector3, double>(currentNode.start + 10 * currentNode.direction / ~currentNode.direction, 0));
            CRPIGM_RayTreeNode *n = &currentNode;
            while (n)
            {
                path.push_back(pair<Vector3, double>(n->start, n->intensity));
                n = n->parentIndex < 0 ? 0 : &rayTree[n->parentIndex];
            }
            reverse(path.begin(), path.end());
            paths.push_back(path);
            continue;
        }

        Vector3 P = currentNode.start;
        Vector3 d = currentNode.direction;
        // The mesh is hit with the ray.
        // Compute the hit point
        Vector3 hitPoint = P + w*d;
        // Compute the new direction
        // We need the face normal for that.
        Vector3 faceNormal = getMeshFaceNormalVector(mesh, hitFaceIndex);
        // Calculate the angle of incidence
        double cosIncidenceAngle = (faceNormal * d)/(~faceNormal * ~d);
        // If it's higher than 90° then normalize it:
        if (cosIncidenceAngle < 0)
        {
            cosIncidenceAngle = - cosIncidenceAngle;
            faceNormal = -faceNormal; //< Reverse the normal as to make it point inside.
        }
        double incidenceAngle = acos(cosIncidenceAngle);
        // Calculate the refraction angle and the new direction.
        double currentRecRefIndex = currentNode.inside ? refractiveIndex : recRefIndex;
        double sinRefractedAngle = currentRecRefIndex * sin(incidenceAngle);
        double refractedAngle;
        double reflectedAngle;
        Vector3 refPlaneNormal = faceNormal % d; //< Refraction plane normal vector.
        double refPlaneNormalLength = ~refPlaneNormal;
        if (refPlaneNormalLength > 0)
        {
            // normalize it
            refPlaneNormal /= ~refPlaneNormal;
        }
        else
        {
            // its null vector, any vector on the face does it.
            refPlaneNormal = mesh.vertices[mesh.faces[hitFaceIndex][0]] - mesh.vertices[mesh.faces[hitFaceIndex][1]];
            refPlaneNormal /= ~refPlaneNormal;
        }
        // Always some rays always reflected back, so calculate the reflected angle and the matrix for it:
        reflectedAngle = PI - incidenceAngle;
        Matrix reflectionRotation = createRotationMatrix(refPlaneNormal, reflectedAngle);
        double reflectance = 1; //< Default to total internal reflection
        if (sinRefractedAngle <= 1)
        {
            // The ray enters the surface.
            refractedAngle = asin(sinRefractedAngle);
            double cosRefractedAngle = cos(refractedAngle);
            // Calculate the amount of rays reflected back.
            double refSRoot = //< Square root of reflectance of the S polarized ray. (electric field oscillates prependicular to the reflection plane
                (currentRecRefIndex * cosIncidenceAngle - cosRefractedAngle) / (currentRecRefIndex * cosIncidenceAngle + cosRefractedAngle);
            double refPRoot = //< Square root of reflectance of the P polarized ray.  (electric field oscillates parallel to the reflection plane)
                (currentRecRefIndex * cosRefractedAngle - cosIncidenceAngle) / (currentRecRefIndex * cosRefractedAngle + cosIncidenceAngle);
            reflectance = 0.5 * (refSRoot * refSRoot + refPRoot * refPRoot);
            // Test if the ray is intense enough
            if (currentNode.intensity * (1 - reflectance) > cutOffIntensity)
            {
                // We have the refraction angle now and ray is intense enough.
                // Use the refraction plane normal to rotate face normal, to get the new direction.
                Matrix refractionRotation = createRotationMatrix(refPlaneNormal, refractedAngle);
                Vector3 refractedRayDir = transformVector(refractionRotation, faceNormal);
                // Push the refracted ray
                CRPIGM_RayTreeNode rtn;
                rtn.direction = refractedRayDir;
                rtn.inside = !currentNode.inside; //< switch medium.
                rtn.intensity = currentNode.intensity * (1 - reflectance);
                rtn.nBounces = currentNode.nBounces + 1;
                rtn.parentIndex = i;
                rtn.skipFaceIndex = hitFaceIndex;
                rtn.start = hitPoint;
                rayTree.push_back(rtn);
            }
        }
        // Push the reflected ray, if intense enough.
        if (currentNode.intensity * reflectance > cutOffIntensity)
        {
            Matrix reflectionRotation = createRotationMatrix(refPlaneNormal, reflectedAngle);
            Vector3 reflectedRayDir = transformVector(reflectionRotation, faceNormal);
            CRPIGM_RayTreeNode rtn;
            rtn.direction = reflectedRayDir;
            rtn.inside = currentNode.inside; //< switch medium.
            rtn.intensity = currentNode.intensity * reflectance;
            rtn.nBounces = currentNode.nBounces + 1;
            rtn.parentIndex = i;
            rtn.skipFaceIndex = hitFaceIndex;
            rtn.start = hitPoint;
            rayTree.push_back(rtn);
        }
    }
}

void transformMesh(Mesh &mesh, const Matrix &transformation)
{
    int N = mesh.vertices.size();
    for (int i = 0; i < N; i++)
    {
        mesh.vertices[i] = transformVector(transformation, mesh.vertices[i]);
    }
}

double clampIn(double x, double a, double b)
{
    if (x < a) return a;
    if (x > b) return b;
    return x;
}

int clampInInt(int x, int a, int b)
{
    if (x < a) return a;
    if (x > b) return b;
    return x;
}

double randFloatNormal(double center, double variance)
{
    double u = rand() / (double)RAND_MAX;
    double v = rand() / (double)RAND_MAX;
    return sqrt(-2 * log(u)) * cos(2 * 3.1415 * v) * variance + center;
}

/*
double randFloatNormal(double min, double max)
{
    const int N = 20;
    double raw = 0;
    for (int i = 0; i < N; i++)
    {
        raw += rand();
    }
    raw /= (double)N * RAND_MAX;
    return min + raw * (max - min);
}
*/

















