#include "Avatar.h"

using namespace RoadRage;

Avatar::Avatar(ShaderManager& shadmgr)
    : m_model(shadmgr)
{
}

Avatar::~Avatar()
{
}

void Avatar::think(const RoadRage::GameClock& /*clock*/)
{
}

void RoadRage::Avatar::render(const RoadRage::GameClock& /*clock*/, const General4x4Matrix& in_viewProj)
{
    m_model.render(in_viewProj);
}
