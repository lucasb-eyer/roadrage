#include "Civilian.h"

#include <3d/Math/Matrix.h>

#include <SFML/System/Clock.hpp>

using namespace RoadRage;

Civilian::Civilian(Vector pos, Vector vel, float orientation, float angularVel, ShaderManager& shadmgr)
    : MobileEntity(pos, vel, Vector(0.0f, 0.0f, 0.0f), orientation, angularVel, 0.0f, Vector(0.1f, 0.5f, 1.0f))
    , m_model(shadmgr)
{
}

Civilian::~Civilian()
{
}

void Civilian::think(const GameClock& clock)
{
    MobileEntity::think(clock);
}

void Civilian::render(const GameClock& /*clock*/, const General4x4Matrix& in_viewProj)
{
    m_model.render(in_viewProj * this->getModelMatrix());
}
