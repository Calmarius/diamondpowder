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
 * @file matrix.h
 *
 * 4×4 matrix struct and its operations.
 */

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
/**
 * Does a homogenous transformation of the given vector, the resulting 4D vector is stored in r.
 */
void transformVector4d(const Matrix &matrix, const Vector3 &vect, double *r);
/**
 * Transforms the given vector with the given matrix. Returns the transformed vector.
 */
Vector3 transformVector(const Matrix &matrix, const Vector3 &v);

Matrix create3DTransformationMatrix
(
    Vector3 eye, ///< The point to look from
    Vector3 target, ///< The target to look at.
    Vector3 up, ///< The upward direction
    double left, ///< Left of the viewport.
    double top, ///< top of the viewport.
    double width, ///< width of the viewport.
    double height ///< height of the viewport.
);

#endif // MATRIX_H
