#ifndef MATRIX_H
#define MATRIX_H

struct Matrix
{
    /**
     * Elements of the matrix, the first is the line index, second is the column index.
     */
    double elem[4][4];

    Matrix() {}

    Matrix
    (
        double m11, double m12, double m13, double m14,
        double m21, double m22, double m23, double m24,
        double m31, double m32, double m33, double m34,
        double m41, double m42, double m43, double m44
    )
    {
        elem[0][0] = m11;
        elem[0][1] = m12;
        elem[0][2] = m13;
        elem[0][3] = m14;

        elem[1][0] = m21;
        elem[1][1] = m22;
        elem[1][2] = m23;
        elem[1][3] = m24;

        elem[2][0] = m31;
        elem[2][1] = m32;
        elem[2][2] = m33;
        elem[2][3] = m34;

        elem[3][0] = m41;
        elem[3][1] = m42;
        elem[3][2] = m43;
        elem[3][3] = m44;
    }
};

Matrix operator%(const Matrix &a, const Matrix &b);

Matrix getIdentityMatrix();
Matrix createTranslateMatrix(double x, double y, double z);
Matrix createScaleMatrix(double scaleRate);
Matrix createScaleMatrix(double scaleX, double scaleY, double scaleZ);
/**
 * Creates raw perspective matrix, which just divides the z coordinate from x and y.
 */
Matrix createRawPerspectiveMatrix();
/**
 * Creates a perspective matrix, which just divides the z coordinate/zoom from x and y.
 */
Matrix createPerspectiveMatrix(double zoom);

Matrix createLookAtMatrix(const Vector3 &position, const Vector3 &target, const Vector3 &up);
/**
 * Creates a rotation matrix for a given axis and angle. Angle is in radians. Axis must be unit length
 */
Matrix createRotationMatrix(const Vector3 &axis, double angle);

void transformVector4d(const Matrix &matrix, const Vector3 &vect, double *r);
Vector3 transformVector(const Matrix &matrix, const Vector3 &v);

Matrix create3DTransformationMatrix
(
    Vector3 eye,
    Vector3 target,
    Vector3 up,
    double left,
    double top,
    double width,
    double height
);

#endif // MATRIX_H
