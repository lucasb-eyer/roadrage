#include "Level.h"

#include "Utilities/String.h"

using namespace RoadRage;

Level::Level(const Configuration& in_settings, const std::string& in_sName)
    : m_shaderManager()
    , m_cam(General4x4Matrix::perspectiveProjection(45.0f, to<float>(in_settings.get("Width"))
                                                         / to<float>(in_settings.get("Height"))))
    , m_csys(m_shaderManager)
    , m_pAvatar(new Avatar(m_shaderManager))
{
    m_cam.pos(Vector(0.5f, 1.5f, 5.0f));
}

Level::Ptr Level::load(const Configuration& in_settings, const std::string& in_sName)
{
    return Level::Ptr(new Level(in_settings, in_sName));
}

void Level::think(const GameClock& clock)
{
    const float speed = 5.0f;
    m_cam.orbit(Quaternion::rotation(0.0f, 1.0f, 0.0f, clock.now()*speed*deg2rad));

    m_pAvatar->think(clock);

    for(auto i = m_civs.begin() ; i != m_civs.end() ; ++i) {
        (*i)->think(clock);
    }
}

void Level::render(const GameClock& clock)
{
    m_csys.render(m_cam);

    m_pAvatar->render(clock, m_cam);

    // TODO: Only those on screen?
    for(auto i = m_civs.begin() ; i != m_civs.end() ; ++i) {
        (*i)->render(clock, m_cam);
    }
}
