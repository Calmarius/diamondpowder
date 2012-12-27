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
 *
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
