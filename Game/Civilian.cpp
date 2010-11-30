#include "Civilian.h"

#include <SFML/System/Clock.hpp>

using namespace RoadRage;

Civilian::Civilian(Vector pos, Vector vel, float orientation, float angularVel, ShaderManager& shadmgr)
    : m_model(shadmgr)
    , m_position(pos)
    , m_velocity(vel)
    , m_fOrientation(orientation)
    , m_fAngularVelocity(angularVel)
{
}

Civilian::~Civilian()
{
}

void Civilian::think(const GameClock& clock)
{
    m_position += m_velocity * clock.deltaT();
}

void Civilian::render(const GameClock& /*clock*/, const General4x4Matrix& in_viewProj)
{
    m_model.render(in_viewProj);
}
