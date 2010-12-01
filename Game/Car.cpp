#include "Car.h"

#include <3d/Math/Quaternion.h>

#include <cmath>

using namespace RoadRage;

Car::Car(Vector in_pos, Vector in_vel, Vector in_accel, float in_orientation, float in_angularVel, float in_angularAccel, Vector in_scale, Vector in_scaleVel, Vector in_scaleAccel)
    : MobileEntity(in_pos, in_vel, in_accel, in_orientation, in_angularVel, in_angularAccel, in_scale, in_scaleVel, in_scaleAccel)
    , StateMachine<CarState::Enum>(CarState::Standing)
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
    switch(this->state()) {
    case CarState::Driving:
        // If we are driving, constantly increase the acceleration.
        this->accel(this->accel() + 5.0f*kmhs2mss*in_clock.deltaT());
        break;
    case CarState::Breaking:
        // I say, we break with a constant force.
        this->accel(-50.0f*kmhs2mss);
        break;
    case CarState::Rolling:
        // They say the amount of friction is proportional to the velocity...
        static const float fDynFrictionCoeff = 1.0f;
        this->accel(-this->speed()*fDynFrictionCoeff);
        break;
    case CarState::Standing:
        break;
    case CarState::Destroyed:
        break;
    }

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

    /// TODO: use the steering angle for the tires, not the whole car!
    if(std::abs(this->steeringAngle()) < this->maxSteeringAngle())
        this->ori(this->ori() + this->steeringVel() * in_clock.deltaT());


    // After the thinking, we may have entered a new state.
    switch(this->state()) {
    case CarState::Driving:
        break;
    case CarState::Breaking:
        break;
    case CarState::Rolling:
        // May it be that we're done with rolling?
        if(this->speed() < 1.0f*kmh2ms)
            this->state(CarState::Standing);
        break;
    case CarState::Standing:
        break;
    case CarState::Destroyed:
        break;
    }
}

float Car::steeringAngle() const
{
    return m_steeringAngle;
}

Car& Car::steeringAngle(float v)
{
    while(v > 360.0f*deg2rad) v -= 360.0f*deg2rad;
    while(v < -360.0f*deg2rad) v += 360.0f*deg2rad;

    // For very small angles (<1°), we just stick to 0°.
    if(nearZero(v, 1.0f*deg2rad) && nearZero(this->steeringVel()))
        v = 0.0f;

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
    // For very small steering velocities angles (<0.1°/s), we stand still.
    if(nearZero(v, .1f*deg2rad))
        v = 0.0f;

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

    m_maxSteeringAngle = v;

    return *this;
}

float Car::maxSteeringVel() const
{
    return m_maxSteeringVel;
}

Car& Car::maxSteeringVel(float v)
{
    m_maxSteeringVel = v;
    return *this;
}

float Car::maxSpeed() const
{
    return m_maxSpeed;
}

Car& Car::maxSpeed(float v)
{
    m_maxSpeed = v;
    return *this;
}

float Car::minSpeed() const
{
    return m_minSpeed;
}

Car& Car::minSpeed(float v)
{
    m_minSpeed = v;
    return *this;
}

float Car::maxAccel() const
{
    return m_maxAccel;
}

Car& Car::maxAccel(float v)
{
    m_maxAccel = v;
    return *this;
}

float Car::minAccel() const
{
    return m_minAccel;
}

Car& Car::minAccel(float v)
{
    m_minAccel = v;
    return *this;
}

bool Car::onLeavingCurrentState()
{
    return StateMachine<CarState::Enum>::onLeavingCurrentState();
}

bool Car::onEnteringNewState(CarState::Enum next)
{
    switch(next) {
    case CarState::Driving:
        break;
    case CarState::Breaking:
        break;
    case CarState::Rolling:
        break;
    case CarState::Standing:
        this->accel(0.0f);
        this->speed(0.0f);
        break;
    case CarState::Destroyed:
        break;
    }

    return StateMachine<CarState::Enum>::onEnteringNewState(next);
}
