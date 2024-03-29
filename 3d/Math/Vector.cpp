/**
 * \file vector.cpp
 * \author Pompei2
 * \date 1 February 2010
 * \brief This file contains the implementation of the vector class. This class defines a 3-component vector.
 **/

#include "Vector.h"
#include "Matrix.h"

#include <sstream>
#include <stdexcept>
#include <cmath>

using namespace RoadRage;

////////////////////////////////////////////
// Constructors and assignment operators. //
////////////////////////////////////////////

Vector::Vector()
    : m_v(new float[4])
{
    m_v[0] = 0.0f;
    m_v[1] = 0.0f;
    m_v[2] = 0.0f;
    m_v[3] = 1.0f;
}

Vector::Vector(float in_v[3])
    : m_v(new float[4])
{
    m_v[0] = in_v[0];
    m_v[1] = in_v[1];
    m_v[2] = in_v[2];
    m_v[3] = 1.0f;
}

Vector::Vector(const Vector& in_v)
    : m_v(new float[4])
{
    m_v[0] = in_v.x();
    m_v[1] = in_v.y();
    m_v[2] = in_v.z();
    m_v[3] = 1.0f;
}

const Vector& Vector::operator=(const Vector& in_v)
{
    m_v[0] = in_v.x();
    m_v[1] = in_v.y();
    m_v[2] = in_v.z();
    m_v[3] = 1.0f;

    return *this;
}

Vector::Vector(float in_fX, float in_fY, float in_fZ)
    : m_v(new float[4])
{
    m_v[0] = in_fX;
    m_v[1] = in_fY;
    m_v[2] = in_fZ;
    m_v[3] = 1.0f;
}

Vector::Vector(float in_fX, float in_fY, float in_fZ, float in_fW)
    : m_v(new float[4])
{
    if(nearZero(in_fW)) {
        m_v[0] = in_fX;
        m_v[1] = in_fY;
        m_v[2] = in_fZ;
        m_v[3] = 0.0f;
    } else {
        m_v[0] = in_fX/in_fW;
        m_v[1] = in_fY/in_fW;
        m_v[2] = in_fZ/in_fW;
        m_v[3] = 1.0f;
    }
}

Vector::Vector(const Vector& in_v, float in_fW)
    : m_v(new float[4])
{
    if(nearZero(in_fW)) {
        m_v[0] = in_v.x();
        m_v[1] = in_v.y();
        m_v[2] = in_v.z();
        m_v[3] = 0.0f;
    } else {
        m_v[0] = in_v.x()/in_fW;
        m_v[1] = in_v.y()/in_fW;
        m_v[2] = in_v.z()/in_fW;
        m_v[3] = 1.0f;
    }
}

Vector::Vector(Vector&& in_v)
{
    this->operator=(std::move(in_v));
}

const Vector& Vector::operator=(Vector&& in_v)
{
    m_v = in_v.m_v;
    in_v.m_v = 0;

    return *this;
}

Vector::~Vector()
{
    if(m_v) delete [] m_v;
}

///////////////////////////////////////
// Conversion methods and operators. //
///////////////////////////////////////

std::string Vector::to_s(unsigned int in_iDecimalPlaces) const
{
    std::stringstream ss;
    ss.precision(in_iDecimalPlaces);
    ss.fill(' ');
    ss <<  "(" << this->x() << ", " << this->y() << ", " << this->z() << ")";
    return ss.str();
}

Vector::operator std::string() const
{
    return this->to_s();
}

/////////////////////////////////////
// Accessors, getters and setters. //
/////////////////////////////////////

float& Vector::operator[](unsigned int idx)
{
    if(idx > 3)
        throw std::runtime_error("Index out of bounds in Vector[i]");

    return m_v[idx];
}

float Vector::operator[](unsigned int idx) const
{
    if(idx > 3)
        throw std::runtime_error("Index out of bounds in Vector[i] const");

    return m_v[idx];
}

////////////////////////////////
// Basic Vector calculations. //
////////////////////////////////

Vector Vector::operator -() const
{
    return Vector(-this->x(),
                  -this->y(),
                  -this->z());
}

Vector Vector::operator +(const Vector& in_v) const
{
    return Vector(this->x() + in_v.x(),
                  this->y() + in_v.y(),
                  this->z() + in_v.z());
}

Vector Vector::operator -(const Vector& in_v) const
{
    return (*this) + (-in_v);
}

Vector Vector::operator *(float in_f) const
{
    return Vector(this->x() * in_f,
                  this->y() * in_f,
                  this->z() * in_f);
}

void Vector::operator +=(const Vector& in_v)
{
    this->operator=((*this) + in_v);
}

void Vector::operator -=(const Vector& in_v)
{
    this->operator+=(-in_v);
}

void Vector::operator *=(float in_f)
{
    this->operator=((*this) * in_f);
}

Vector Vector::cross(const Vector& in_v) const
{
    return Vector(this->y()*in_v.z() - this->z()*in_v.y(),
                  this->z()*in_v.x() - this->x()*in_v.z(),
                  this->x()*in_v.y() - this->y()*in_v.x());
}

float Vector::dot(const Vector& in_v) const
{
    return this->x()*in_v.x()
         + this->y()*in_v.y()
         + this->z()*in_v.z();
}

///////////////////////////////////////
// Vector length related operations. //
///////////////////////////////////////

float Vector::len() const
{
    return sqrt(this->x()*this->x()
              + this->y()*this->y()
              + this->z()*this->z());
}

Vector& Vector::normalize()
{
    // The zero-vector stays the zero-vector.
    if(nearZero(this->x()) &&
       nearZero(this->y()) &&
       nearZero(this->z()) ) {
        return this->x(0.0f).y(0.0f).z(0.0f);
    }

    float l = this->len();

    // Very little vectors will be stretched to a unit vector in one direction.
    if(nearZero(l)) {
        if((this->x() >= this->y())
        && (this->x() >= this->z())
        && (this->x() >= 0.0f)) {
            return this->x(1.0f).y(0.0f).z(0.0f);
        } else if((this->x() <= this->y())
               && (this->x() <= this->z())
               && (this->x() <= 0.0f)) {
            return this->x(-1.0f).y(0.0f).z(0.0f);
        } else {
            if(this->y() >= this->z()
            && this->y() >= 0.0f) {
                return this->x(0.0f).y(1.0f).z(0.0f);
            } else if(this->y() <= this->z()
                   && this->y() <= 0.0f) {
                return this->x(0.0f).y(-1.0f).z(0.0f);
            } else {
                return this->x(0.0f).y(0.0f).z(this->z() >= 0.0f ? 1.0f : -1.0f);
            }
        }
    } else {
        // Follows the usual normalization rule.
        float m = 1.0f / l;
        return this->x(this->x()*m).y(this->y()*m).z(this->z()*m);
    }
}

Vector Vector::normalized() const
{
    Vector copy(*this);
    return copy.normalize();
}

//////////////////////////////////////
// Vector interpolation operations. //
//////////////////////////////////////

Vector Vector::lerp(const Vector& v2, float between) const
{
    return *this + (v2 - *this)*between;
}

////////////////////////////
// Vector transformation. //
////////////////////////////

Vector operator*(const Base4x4Matrix& m, const Vector& v)
{
    return Vector(m[0]*v[0] + m[4]*v[1] + m[8] *v[2] + m[12]*v[3],
                  m[1]*v[0] + m[5]*v[1] + m[9] *v[2] + m[13]*v[3],
                  m[2]*v[0] + m[6]*v[1] + m[10]*v[2] + m[14]*v[3],
                  m[3]*v[0] + m[7]*v[1] + m[11]*v[2] + m[15]*v[3]);
}
