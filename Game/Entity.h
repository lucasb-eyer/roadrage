#pragma once

#include "GameClock.h"

#include "3d/Math/Vector.h"
#include "3d/Math/Matrix.h"

namespace RoadRage {

class VisibleEntity {
public:
    VisibleEntity(Vector in_pos, float in_orientation = 0.0f, Vector in_scale = Vector(1.0f, 1.0f, 1.0f));
    virtual ~VisibleEntity();

    virtual void render(const GameClock& in_clock, const General4x4Matrix& in_viewProj) = 0;

    Vector pos() const;
    VisibleEntity& pos(Vector v);
    float ori() const;
    VisibleEntity& ori(float v);
    Vector scale() const;
    VisibleEntity& scale(Vector v);

protected:
    AffineMatrix getModelMatrix() const;

private:
    VisibleEntity& recalcCachedModelMatrix();

    Vector m_position;
    float m_fOrientation;
    Vector m_scale;

    AffineMatrix m_cachedModelMatrix;
};

class ThinkingEntity {
public:
    ThinkingEntity();
    virtual ~ThinkingEntity();

    virtual void think(const GameClock& in_clock) = 0;
};

class MobileEntity : public VisibleEntity, public ThinkingEntity {
public:
    MobileEntity(Vector in_pos, Vector in_vel, Vector in_accel = Vector(0.0f, 0.0f, 0.0f), float in_orientation = 0.0f, float in_angularVel = 0.0f, float in_angularAccel = 0.0f, Vector in_scale = Vector(1.0f, 1.0f, 1.0f), Vector in_scaleVel = Vector(0.0f, 0.0f, 0.0f), Vector in_scaleAccel = Vector(0.0f, 0.0f, 0.0f));
    virtual ~MobileEntity();

    virtual void think(const GameClock& in_clock);
    virtual void render(const GameClock& in_clock, const General4x4Matrix& in_viewProj) = 0;

    Vector vel() const;
    MobileEntity& vel(Vector v);
    Vector accel() const;
    MobileEntity& accel(Vector v);
    float angularVel() const;
    MobileEntity& angularVel(float v);
    float angularAccel() const;
    MobileEntity& angularAccel(float v);
    Vector scaleVel() const;
    MobileEntity& scaleVel(Vector v);
    Vector scaleAccel() const;
    MobileEntity& scaleAccel(Vector v);

private:
    Vector m_velocity;
    Vector m_acceleration;
    float m_fAngularVelocity;
    float m_fAngularAcceleration;
    Vector m_scaleVelocity;
    Vector m_scaleAcceleration;
};

}
