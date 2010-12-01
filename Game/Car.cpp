#include "Car.h"

#include <3d/Math/Quaternion.h>

#include <cmath>

using namespace RoadRage;

Car::Car(Vector in_pos, Vector in_vel, Vector in_accel, float in_orientation, float in_angularVel, float in_angularAccel, Vector in_scale, Vector in_scaleVel, Vector in_scaleAccel)
    : MobileEntity(in_pos, in_vel, in_accel, in_orientation, in_angularVel, in_angularAccel, in_scale, in_scaleVel, in_scaleAccel)
    , m_steeringAngle(0.0f)
    , m_speed(0.0f)
    , m_accel(0.0f)
    , m_maxSteeringAngle(45.0f*deg2rad)
    , m_maxSteeringVel(360.0f*deg2rad)
    , m_maxSpeed(120.0f*kmh2ms)
    , m_minSpeed(0.0f)
    , m_maxAccel(20.0f*kmhs2mss)
    , m_minAccel(-50.0f*kmhs2mss)
{

}

Car::~Car()
{
}

void Car::think(const GameClock& in_clock)
{
    // Update the speed according to the acceleration
    this->speed(this->speed() + this->accel() * in_clock.deltaT());

    // Update the steering angle according to the steering velocity.
    this->steeringAngle(this->steeringAngle() + this->steeringVel() * in_clock.deltaT());

    // Now update the "driving velocity" vector, that is the velocity solely
    // by driving action, not affected by collisions and the like.
    Vector drivingVel = Vector(0.0f, 0.0f, -1.0f) * this->speed();
    drivingVel = Quaternion::rotation(0.0f, 1.0f, 0.0f, this->steeringAngle()).rotate(drivingVel);

    // First do all the normal calculations, without considering the "driving".
    MobileEntity::think(in_clock);

    // Then, add the "driving" movements on top of it.
    this->pos(this->pos() + drivingVel * in_clock.deltaT());

    if(std::abs(this->steeringAngle()) < this->maxSteeringAngle())
        this->ori(this->ori() + this->steeringVel() * in_clock.deltaT());
}

float Car::steeringAngle() const
{
    return m_steeringAngle;
}

Car& Car::steeringAngle(float v)
{
    while(v > 360.0f*deg2rad) v -= 360.0f*deg2rad;
    while(v < -360.0f*deg2rad) v += 360.0f*deg2rad;

    // Check for too small angles (if there is no angular velocity)
    if(nearZero(v, 1.0f*deg2rad) && nearZero(this->steeringVel()))
        v = 0.0f;

    // But also check for too big angles
    clamp(v, -this->maxSteeringAngle(), this->maxSteeringAngle());

    m_steeringAngle = v;
    return *this;
}

float Car::steeringVel() const
{
    return m_steeringVel;
}

Car& Car::steeringVel(float v)
{
    // Check for too small steering velocities
    if(nearZero(v, 1.0f*deg2rad))
        v = 0.0f;

    // But also for too big ones
    clamp(v, -this->maxSteeringVel(), this->maxSteeringVel());

    m_steeringVel = v;
    return *this;
}

float Car::speed() const
{
    return m_speed;
}

Car& Car::speed(float v)
{
    // Check for too small speeds (but only when there is no acceleration)
    if(nearZero(v, 0.2f) && nearZero(this->accel()))
        v = 0.0f;

    // But also for too big speeds
    clamp(v, this->minSpeed(), this->maxSpeed());

    m_speed = v;
    return *this;
}

float Car::accel() const
{
    return m_accel;
}

Car& Car::accel(float v)
{
    // Check for too small acceleration
    if(nearZero(v, 0.1f))
        v = 0.0f;

    // But also for too big acceleration
    clamp(v, this->minAccel(), this->maxAccel());

    m_accel = v;
    return *this;
}

float Car::maxSteeringAngle() const
{
    return m_maxSteeringAngle;
}

Car& Car::maxSteeringAngle(float v)
{
    while(v > 360.0f*deg2rad) v -= 360.0f*deg2rad;
    while(v < -360.0f*deg2rad) v += 360.0f*deg2rad;

    if(nearZero(v, 1.0f*deg2rad))
        m_maxSteeringAngle = 0.0f;
    else
        m_maxSteeringAngle = v;

    return *this;
}

float Car::maxSteeringVel() const
{
    return m_maxSteeringVel;
}

Car& Car::maxSteeringVel(float v)
{
    if(nearZero(v, 1.0f*deg2rad))
        m_maxSteeringVel = 0.0f;
    else
        m_maxSteeringVel = v;

    return *this;
}

float Car::maxSpeed() const
{
    return m_maxSpeed;
}

Car& Car::maxSpeed(float v)
{
    if(nearZero(v, 0.2f))
        m_maxSpeed = 0.0f;
    else
        m_maxSpeed = v;

    return *this;
}

float Car::minSpeed() const
{
    return m_minSpeed;
}

Car& Car::minSpeed(float v)
{
    if(nearZero(v, 0.2f))
        m_minSpeed = 0.0f;
    else
        m_minSpeed = v;

    return *this;
}

float Car::maxAccel() const
{
    return m_maxAccel;
}

Car& Car::maxAccel(float v)
{
    if(nearZero(v, 0.1f))
        m_maxAccel = 0.0f;
    else
        m_maxAccel = v;

    return *this;
}

float Car::minAccel() const
{
    return m_minAccel;
}

Car& Car::minAccel(float v)
{
    if(nearZero(v, 0.1f))
        m_minAccel = 0.0f;
    else
        m_minAccel = v;

    return *this;
}
