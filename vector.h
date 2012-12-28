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
 * @file vector.h
 *
 * 3D vector and its functions and operators.
 */

#ifndef VECTOR_H
#define VECTOR_H

struct Vector3
{
    double x, y, z;

    Vector3()
    {

    }

    Vector3(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

/**Vector addition*/
Vector3 &operator+=(Vector3 &a, const Vector3 &b);
Vector3 operator+(const Vector3 &a, const Vector3 &b);
/**Vector subtraction*/
Vector3 &operator-=(Vector3 &a, const Vector3 &b);
Vector3 operator-(const Vector3 &a, const Vector3 &b);
/**Division with scalar*/
Vector3 &operator/=(Vector3 &a, double x);
Vector3 operator/(const Vector3 &a, double x);
/**Multiplication with scalar*/
Vector3 &operator*=(Vector3 &a, double x);
Vector3 operator*(const Vector3 &a, double x);
Vector3 operator*(double x, const Vector3 &a);
/**Dot product*/
double operator*(const Vector3 &a, const Vector3 &b);
/**Cross product*/
Vector3 &operator%=(Vector3 &a, const Vector3 &b);
Vector3 operator%(const Vector3 &a, const Vector3 &b);
/**Length*/
double operator~(const Vector3 &a);
/**Minus*/
Vector3 operator-(const Vector3 &a);
/**
 * Fixes a rotated coordinate system given by 3 vectors.
 *
 * It will reorthoganlize the system, and adjust the length of the vectors to unit length.
 */
void fix3VectorSystem(Vector3 &right, Vector3 &upward, Vector3 &backward);

/**
 * Gets a random unit vector.
 */
Vector3 getRandomVector();

Vector3 clampVector(const Vector3 &v, double maxLen);
void rotate2d(double &x, double &y, double angle);

#endif // VECTOR_H
