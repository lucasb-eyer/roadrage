#pragma once

#include "Entity.h"
#include "GameClock.h"

#include "3d/BuiltinModel.h"

namespace RoadRage {

class Avatar : public MobileEntity {
public:
    Avatar(ShaderManager& shadmgr);
    virtual ~Avatar();

    void think(const GameClock& clock);
    void render(const GameClock& clock, const General4x4Matrix& in_viewProj);

private:
    BoxModel m_model;
};

}
