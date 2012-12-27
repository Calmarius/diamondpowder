Matrix operator%(const Matrix &a, const Matrix &b)
{
    Matrix result;
    int i, j, k;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            result.elem[i][j] = 0;
            for (k = 0; k < 4; k++)
            {
                result.elem[i][j] += a.elem[i][k] * b.elem[k][j];
            }
        }
    }
    return result;
}


Matrix getIdentityMatrix()
{
    return Matrix
    (
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    );
}

Matrix createTranslateMatrix(double x, double y, double z)
{
    return Matrix
    (
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        x, y, z, 1
    );
}

Matrix createScaleMatrix(double scaleRate)
{
    return Matrix
    (
        scaleRate, 0, 0, 0,
        0, scaleRate, 0, 0,
        0, 0, scaleRate, 0,
        0, 0, 0, 1
    );
}

Matrix createScaleMatrix(double scaleX, double scaleY, double scaleZ)
{
    return Matrix
    (
        scaleX, 0, 0, 0,
        0, scaleY, 0, 0,
        0, 0, scaleZ, 0,
        0, 0, 0, 1
    );
}

/**
 * Creates raw perspective matrix, which just divides the z coordinate from x and y.
 */
Matrix createRawPerspectiveMatrix()
{
    return Matrix
    (
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 0, -1,
        0, 0, 1, 0
    );
}

/**
 * Creates a perspective matrix, which just divides the z coordinate/zoom from x and y.
 */
Matrix createPerspectiveMatrix(double zoom)
{
    return Matrix
    (
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 0, -1 / zoom,
        0, 0, 1 / zoom, 0
    );
}

Matrix createLookAtMatrix(const Vector3 &eye, const Vector3 &target, const Vector3 &up)
{
    Vector3 backward = eye - target;
    Vector3 sideways = up % backward;
    Vector3 up_ortho = backward % sideways;

    sideways /= ~sideways;
    up_ortho /= ~up_ortho;
    backward /= ~backward;

    Matrix rotation
    (
        sideways.x, up_ortho.x, backward.x, 0,
        sideways.y, up_ortho.y, backward.y, 0,
        sideways.z, up_ortho.z, backward.z, 0,
        0, 0, 0, 1
    );

    Matrix translation = createTranslateMatrix(-eye.x, -eye.y, -eye.z);

    return translation%rotation;
}

void transformVector4d(const Matrix &matrix, const Vector3 &vect, double *r)
{
    double v[4] = {vect.x, vect.y, vect.z, 1};

    // Matrix multiplication
    for (int j = 0; j < 4; j++)
    {
        r[j] = 0;
        for (int i = 0; i < 4; i++)
        {
            r[j] += v[i] * matrix.elem[i][j];
        }
    }
}

Vector3 transformVector(const Matrix &matrix, const Vector3 &vect)
{
    double r[4];
    transformVector4d(matrix, vect, r);
    // Homogenous -> regular vector.
    for (int i = 0; i < 3; i++)
    {
        r[i] /= r[3];
    }

    return Vector3(r[0], r[1], r[2]);

}

Matrix create3DTransformationMatrix
(
    Vector3 eye,
    Vector3 target,
    Vector3 up,
    double left,
    double top,
    double width,
    double height
)
{
    Matrix lookAt = createLookAtMatrix(eye, target, up);
    Matrix perspective = createRawPerspectiveMatrix();
    double minDim = std::min(width, height);
    Matrix scale = createScaleMatrix(minDim, -minDim, 1);
    Matrix viewport = createTranslateMatrix(left + width / 2.0, top + height / 2.0, 0);

    return lookAt % perspective % scale % viewport;
}

Matrix createRotationMatrix(const Vector3 &a, double angle)
{
    double c = cos(angle);
    double s = sin(angle);

    return Matrix
    (
        (1-c)*a.x*a.x + c, (1-c)*a.x*a.y + s*a.z, (1-c)*a.x*a.z - s*a.y, 0,
        (1-c)*a.y*a.x - s*a.z, (1-c)*a.y*a.y + c, (1-c)*a.y*a.z + s*a.x, 0,
        (1-c)*a.z*a.x + s*a.y, (1-c)*a.z*a.y - s*a.x, (1-c)*a.z*a.z +c, 0,
        0, 0, 0, 1
    );
}

