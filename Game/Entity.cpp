#include "Entity.h"

using namespace RoadRage;

VisibleEntity::VisibleEntity(Vector in_pos, float in_orientation, Vector in_scale)
    : m_position(in_pos)
    , m_fOrientation(in_orientation)
    , m_scale(in_scale)
{
    this->recalcCachedModelMatrix();
}

VisibleEntity::~VisibleEntity()
{
}

Vector VisibleEntity::pos() const
{
    return m_position;
}

VisibleEntity& VisibleEntity::pos(Vector v)
{
    m_position = v;
    return this->recalcCachedModelMatrix();
}

float VisibleEntity::ori() const
{
    return m_fOrientation;
}

VisibleEntity& VisibleEntity::ori(float v)
{
    m_fOrientation = v;
    return this->recalcCachedModelMatrix();
}

Vector VisibleEntity::scale() const
{
    return m_scale;
}

VisibleEntity& VisibleEntity::scale(Vector v)
{
    m_scale = v;
    return this->recalcCachedModelMatrix();
}

AffineMatrix VisibleEntity::getModelMatrix() const
{
    return m_cachedModelMatrix;
}

VisibleEntity& VisibleEntity::recalcCachedModelMatrix()
{
    m_cachedModelMatrix = AffineMatrix::translation(m_position) * AffineMatrix::rotationY(m_fOrientation) * AffineMatrix::scale(m_scale);

    return *this;
}

ThinkingEntity::ThinkingEntity()
{
}

ThinkingEntity::~ThinkingEntity()
{
}

MobileEntity::MobileEntity(Vector in_pos, Vector in_vel, Vector in_accel, float in_orientation, float in_angularVel, float in_angularAccel, Vector in_scale, Vector in_scaleVel, Vector in_scaleAccel)
    : VisibleEntity(in_pos, in_orientation, in_scale)
    , ThinkingEntity()
    , m_velocity(in_vel)
    , m_acceleration(in_accel)
    , m_fAngularVelocity(in_angularVel)
    , m_fAngularAcceleration(in_angularAccel)
    , m_scaleVelocity(in_scaleVel)
    , m_scaleAcceleration(in_scaleAccel)
{
}

MobileEntity::~MobileEntity()
{
}

Vector MobileEntity::vel() const
{
    return m_velocity;
}

MobileEntity& MobileEntity::vel(Vector v)
{
    m_velocity = v;
    return *this;
}

Vector MobileEntity::accel() const
{
    return m_acceleration;
}

MobileEntity& MobileEntity::accel(Vector v)
{
    m_acceleration = v;
    return *this;
}

float MobileEntity::angularVel() const
{
    return m_fAngularVelocity;
}

MobileEntity& MobileEntity::angularVel(float v)
{
    m_fAngularVelocity = v;
    return *this;
}

float MobileEntity::angularAccel() const
{
    return m_fAngularAcceleration;
}

MobileEntity& MobileEntity::angularAccel(float v)
{
    m_fAngularAcceleration = v;
    return *this;
}

Vector MobileEntity::scaleVel() const
{
    return m_scaleVelocity;
}

MobileEntity& MobileEntity::scaleVel(Vector v)
{
    m_scaleVelocity = v;
    return *this;
}

Vector MobileEntity::scaleAccel() const
{
    return m_scaleAcceleration;
}

MobileEntity& MobileEntity::scaleAccel(Vector v)
{
    m_scaleAcceleration = v;
    return *this;
}

void MobileEntity::think(const GameClock& in_clock)
{
    // Update the velocity according to the acceleration.
    if(!nearZero(this->accel().len()))
        this->vel(this->vel() + this->accel() * in_clock.deltaT());

    // Update the position according to the velocity.
    if(!nearZero(this->vel().len()))
        this->pos(this->pos() + this->vel() * in_clock.deltaT());

    // Update the angular velocity according to the acceleration.
    if(!nearZero(this->angularAccel()))
        this->angularVel(this->angularVel() + this->angularAccel() * in_clock.deltaT());

    // Update the orientation according to the angular velocity.
    if(!nearZero(this->angularVel()))
        this->ori(this->ori() + this->angularVel() * in_clock.deltaT());

    // Update the scaling velocity according to the scaling acceleration.
    if(!nearZero(this->scaleAccel().len()))
        this->scaleVel(this->scaleVel() + this->scaleAccel() * in_clock.deltaT());

    // Update the scale according to the scaling velocity.
    if(!nearZero(this->scaleVel().len()))
        this->scale(this->scale() + this->scaleVel() * in_clock.deltaT());
}
