#pragma once

#include "Game/Entity.h"

#include "Utilities/StateMachine.h"

namespace RoadRage {

namespace CarState {
    enum Enum {
        Standing,
        Rolling,
        Driving,
        Breaking,
        Destroyed
    };
}

class Car : public MobileEntity, public StateMachine<RoadRage::CarState::Enum> {
public:

    Car(Vector in_pos, Vector in_vel, Vector in_accel = Vector(0.0f, 0.0f, 0.0f), float in_orientation = 0.0f, float in_angularVel = 0.0f, float in_angularAccel = 0.0f, Vector in_scale = Vector(1.0f, 1.0f, 1.0f), Vector in_scaleVel = Vector(0.0f, 0.0f, 0.0f), Vector in_scaleAccel = Vector(0.0f, 0.0f, 0.0f));
    virtual ~Car();

    virtual void think(const RoadRage::GameClock& in_clock);

    float speed() const;
    Car& speed(float v);

    float accel() const;
    Car& accel(float v);

    float steeringAngle() const;
    Car& steeringAngle(float v);

    float steeringVel() const;
    Car& steeringVel(float v);

    float maxSpeed() const;
    Car& maxSpeed(float v);
    float minSpeed() const;
    Car& minSpeed(float v);

    float maxAccel() const;
    Car& maxAccel(float v);
    float minAccel() const;
    Car& minAccel(float v);

    float maxSteeringAngle() const;
    Car& maxSteeringAngle(float v);

    float maxSteeringVel() const;
    Car& maxSteeringVel(float v);

protected:
    virtual bool onLeavingCurrentState();
    virtual bool onEnteringNewState(CarState::Enum next);

private:
    float m_steeringAngle;
    float m_steeringVel;
    float m_speed;
    float m_accel;

    float m_maxSteeringAngle;
    float m_maxSteeringVel;
    float m_maxSpeed;
    float m_minSpeed;
    float m_maxAccel;
    float m_minAccel;
};

}
