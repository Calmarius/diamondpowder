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
 * @file vector.cpp
 *
 * Implementation of 3D vector calculations.
 */

using namespace std;

Vector3 operator+(const Vector3 &a, const Vector3 &b)
{
    Vector3 tmp = a;

    tmp += b;
    return tmp;
}

Vector3 &operator+=(Vector3 &a, const Vector3 &b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;

    return a;
}

Vector3 operator-(const Vector3 &a, const Vector3 &b)
{
    Vector3 tmp = a;

    tmp -= b;
    return tmp;
}

Vector3 &operator-=(Vector3 &a, const Vector3 &b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;

    return a;
}

double operator*(const Vector3 &a, const Vector3 &b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

Vector3 &operator%=(Vector3 &a, const Vector3 &b)
{
    a = a % b;
    return a;
}

Vector3 &operator/=(Vector3 &a, double x)
{
    a.x /= x;
    a.y /= x;
    a.z /= x;

    return a;
}

Vector3 operator/(const Vector3 &a, double x)
{
    Vector3 tmp = a;

    tmp /= x;
    return tmp;
}

Vector3 &operator*=(Vector3 &a, double x)
{
    a.x *= x;
    a.y *= x;
    a.z *= x;
    return a;
}

Vector3 operator*(const Vector3 &a, double x)
{
    Vector3 tmp = a;
    tmp *= x;

    return tmp;
}

Vector3 operator*(double x, const Vector3 &a)
{
    Vector3 tmp = a;
    tmp *= x;

    return tmp;
}


Vector3 operator%(const Vector3 &a, const Vector3 &b)
{
    return Vector3
    (
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
    );
}

double operator~(const Vector3 &a)
{
    return sqrt(a*a);
}

Vector3 operator-(const Vector3 &a)
{
    return Vector3(-a.x, -a.y, -a.z);
}

void fix3VectorSystem(Vector3 &right, Vector3 &upward, Vector3 &backward)
{
    backward = right % upward;
    right = upward % backward;

    right /= ~right;
    upward /= ~upward;
    backward /= ~backward;
}

Vector3 clampVector(const Vector3 &v, double maxLen)
{
    double len = ~v;
    if (len > maxLen)
    {
        return v * (len / maxLen);
    }
    return v;
}

Vector3 getRandomVector()
{
    Vector3 tmp;
    do
    {
        tmp = Vector3(
            (rand() % 10000 - 5000.0) / 5000.0,
            (rand() % 10000 - 5000.0) / 5000.0,
            (rand() % 10000 - 5000.0) / 5000.0
        );
    }
    while (tmp*tmp > 1);
    return tmp / ~tmp;
}

void rotate2d(double &x, double &y, double angle)
{
    double tx, ty;
    tx = x * cos(angle) - y * sin(angle);
    ty = x * sin(angle) + y * cos(angle);
    x = tx;
    y = ty;
}
