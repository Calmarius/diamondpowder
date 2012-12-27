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
