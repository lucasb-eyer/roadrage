#pragma once

#include "Entity.h"

#include "3d/BuiltinModel.h"

namespace RoadRage {

class Civilian : public MobileEntity {
public:
    // Civilians travel at constant speed for now!
    Civilian(Vector pos, Vector vel, float orientation, float angularVel, ShaderManager& shadmgr);
    virtual ~Civilian();

    virtual void think(const GameClock& clock);
    virtual void render(const GameClock& clock, const General4x4Matrix& in_viewProj);

private:
    BoxModel m_model;
};

}
