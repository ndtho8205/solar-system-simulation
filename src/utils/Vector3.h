#ifndef VECTOR3_H
#define VECTOR3_H

#ifndef QT_CORE_LIB
#include <iostream>
#else
#include <QDataStream>
#endif

#include <cmath>



template <class T> class Vector3;

typedef Vector3<double> Vec3d;
typedef Vector3<float>  Vec3f;
typedef Vector3<int>    Vec3i;



template <class T> class Vector3
{
public:
    T x;
    T y;
    T z;

    //
    //  --- Constructors and Destructors ---
    //

    Vector3();

    Vector3(T _v);

    Vector3(T _x, T _y, T _z);

    Vector3(const Vector3<T> &_other);

    //
    // --- Assignment operator ---
    //

    Vector3 &operator=(const Vector3<T> &_other);

    //
    // --- Relational operator ---
    //

    bool operator==(const Vector3<T> &_other) const;

    bool operator!=(const Vector3<T> &_other) const;

    //
    //  --- (non-modifying) Arithematic Operators ---
    //

    const Vector3 &operator+() const;

    Vector3 operator-() const;

    Vector3 operator+(const Vector3<T> &_other) const;

    Vector3 operator-(const Vector3<T> &_other) const;

    Vector3 operator*(const Vector3<T> &_other) const;

    Vector3 operator*(T _s) const;

    Vector3 operator/(T _s) const;

    //
    //  --- (modifying) Arithematic Operators ---
    //

    Vector3 &operator+=(const Vector3<T> &_other);

    Vector3 &operator-=(const Vector3<T> &_other);

    Vector3 &operator*=(const Vector3<T> &_other);

    Vector3 &operator*=(T _s);

    Vector3 &operator/=(T _s);

    //
    // --- Method ---
    //

    operator QString();

    T dot(const Vector3<T> &_other) const;

    Vector3 operator^(const Vector3<T> &_other);

    T distance(const Vector3<T> &_other);

    T latitude() const;

    T longitude() const;

    T angle(const Vector3<T> &_other) const;

    T angleNormalized(const Vector3<T> &_other) const;

    T length() const;

    T lengthSquared() const;

    Vector3 &normalize();
};

//
// --- Friend method ---
//

template <class T> Vector3<T> operator*(T _s, const Vector3<T> &_other)
{
    return _other * _s;
}

//
// --- Input & Output ---
//

#ifdef QT_CORE_LIB

template <class T> QDataStream &operator<<(QDataStream &out, const Vector3<T> &_v)
{
    out << "(" << _v.x << ", " << _v.y << ", " << _v.z << ")";
    return out;
}

template <class T> QDataStream &operator>>(QDataStream &in, Vector3<T> &_v)
{
    in >> _v.x >> _v.y >> _v.z;
    return in;
}

template <class T> Vector3<T>::operator QString()
{
    return QString("(%1, %2, %3)").arg(x).arg(y).arg(z);
}

#else

template <class T> std::ostream &operator<<(std::ostream &out, const Vector3<T> &_v)
{
    out << "(" << _v.x << ", " << _v.y << ", " << _v.z << ")";
    return out;
}

template <class T> std::istream &operator>>(std::istream &in, Vector3<T> &_v)
{
    in >> _v.x >> _v.y >> _v.z;
    return in;
}

#endif



// ===========================================================================
// --- Vector3 implementation ---
// ===========================================================================

//
//  --- Constructors and Destructors ---
//

template <class T> Vector3<T>::Vector3() : x(0), y(0), z(0)
{
}

template <class T> Vector3<T>::Vector3(T _v) : x(_v), y(_v), z(_v)
{
}

template <class T> Vector3<T>::Vector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z)
{
}

template <class T>
Vector3<T>::Vector3(const Vector3<T> &_other) : x(_other.x), y(_other.y), z(_other.z)
{
}

//
// --- Assignment operator ---
//

template <class T> Vector3<T> &Vector3<T>::operator=(const Vector3<T> &_other)
{
    x = _other.x;
    y = _other.y;
    z = _other.z;
    return *this;
}

//
// --- Relational operator ---
//

template <class T> bool Vector3<T>::operator==(const Vector3<T> &_other) const
{
    return (x == _other.x && y == _other.y && z == _other.z);
}

template <class T> bool Vector3<T>::operator!=(const Vector3<T> &_other) const
{
    return (x != _other.x || y != _other.y || z != _other.z);
}

//
//  --- (non-modifying) Arithematic Operators ---
//

template <class T> const Vector3<T> &Vector3<T>::operator+() const
{
    return *this;
}

template <class T> Vector3<T> Vector3<T>::operator-() const
{
    return Vector3<T>(-x, -y, -z);
}

template <class T> Vector3<T> Vector3<T>::operator+(const Vector3<T> &_other) const
{
    return Vector3(x + _other.x, y + _other.y, z + _other.z);
}

template <class T> Vector3<T> Vector3<T>::operator-(const Vector3<T> &_other) const
{
    return Vector3(x - _other.x, y - _other.y, z - _other.z);
}

template <class T> Vector3<T> Vector3<T>::operator*(const Vector3<T> &_other) const
{
    return Vector3(x * _other.x, y * _other.y, z * _other.z);
}

template <class T> Vector3<T> Vector3<T>::operator*(T _s) const
{
    return Vector3(x * _s, y * _s, z * _s);
}

template <class T> Vector3<T> Vector3<T>::operator/(T _s) const
{
    return Vector3(x / _s, y / _s, z / _s);
}

//
//  --- (modifying) Arithematic Operators ---
//

template <class T> Vector3<T> &Vector3<T>::operator+=(const Vector3<T> &_other)
{
    x += _other.x;
    y += _other.y;
    z += _other.z;
    return *this;
}

template <class T> Vector3<T> &Vector3<T>::operator-=(const Vector3<T> &_other)
{
    x -= _other.x;
    y -= _other.y;
    z -= _other.z;
    return *this;
}

template <class T> Vector3<T> &Vector3<T>::operator*=(const Vector3<T> &_other)
{
    x *= _other.x;
    y *= _other.y;
    z *= _other.z;
    return *this;
}

template <class T> Vector3<T> &Vector3<T>::operator*=(T _s)
{
    x *= _s;
    y *= _s;
    z *= _s;
    return *this;
}

template <class T> Vector3<T> &Vector3<T>::operator/=(T _s)
{
    x /= _s;
    y /= _s;
    z /= _s;
    return *this;
}

//
// --- Method ---
//

template <class T> T Vector3<T>::dot(const Vector3<T> &_other) const
{
    return x * _other.x + y * _other.y + z * _other.z;
}

template <class T> Vector3<T> Vector3<T>::operator^(const Vector3<T> &_other)
{
    return Vector3<T>(
        y * _other.z - z * _other.y, z * _other.x - x * _other.z, x * _other.y - y * _other.x);
}

template <class T> T Vector3<T>::distance(const Vector3<T> &_other)
{
    Vector3<T> offset = _other - *this;
    return sqrt(offset.x * offset.x + offset.y * offset.y + offset.z * offset.z);
}

template <class T> T Vector3<T>::latitude() const
{
    return std::asin(z / length());
}

template <class T> T Vector3<T>::longitude() const
{
    return std::atan2(y, x);
}

template <class T> T Vector3<T>::angle(const Vector3<T> &_other) const
{
    const T cosAngle = dot(_other) / std::sqrt(lengthSquared() * _other.lengthSquared());
    return cosAngle >= 1 ? 0 : (cosAngle <= -1 ? M_PI : std::acos(cosAngle));
}

template <class T> T Vector3<T>::angleNormalized(const Vector3<T> &_other) const
{
    const T cosAngle = dot(_other);
    return cosAngle >= 1 ? 0 : (cosAngle <= -1 ? M_PI : std::acos(cosAngle));
}

template <class T> T Vector3<T>::length() const
{
    return (T)std::sqrt(x * x + y * y + z * z);
}

template <class T> T Vector3<T>::lengthSquared() const
{
    return (x * x + y * y + z * z);
}

template <class T> Vector3<T> &Vector3<T>::normalize()
{
    T s = length();
    x /= s;
    y /= s;
    z /= s;
    return *this;
}


#endif  // VECTOR3_H
