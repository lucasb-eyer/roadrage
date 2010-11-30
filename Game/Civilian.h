#pragma once

#include "GameClock.h"

#include "3d/Math/Vector.h"
#include "3d/BuiltinModel.h"

namespace RoadRage {

class Civilian {
public:
    Civilian(Vector pos, Vector vel, float orientation, float angularVel, ShaderManager& shadmgr);
    virtual ~Civilian();

    virtual void think(const GameClock& clock);
    virtual void render(const GameClock& clock, const General4x4Matrix& in_viewProj);

private:
    BoxModel m_model;

    Vector m_position;
    Vector m_velocity;
    float m_fOrientation;
    float m_fAngularVelocity;
};

}
