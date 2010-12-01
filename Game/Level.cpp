#include "Level.h"

#include "Utilities/String.h"

#include <SFML/System/Randomizer.hpp>

#include <random>
#include <functional>

using namespace RoadRage;

Level::Level(const Configuration& in_settings, const std::string& in_sName)
    : m_shaderManager()
    , m_cam(General4x4Matrix::perspectiveProjection(45.0f, to<float>(in_settings.get("Width"))
                                                         / to<float>(in_settings.get("Height"))))
    , m_csys(m_shaderManager)
    , m_pAvatar(new Avatar(m_shaderManager))
{
    m_cam.pos(Vector(0.5f, 1.5f, 5.0f));

    // Create the randomization engine with a seed.
    std::mt19937 engine(sf::Randomizer::GetSeed());
    std::variate_generator<std::mt19937&, std::normal_distribution<>> generatorX(engine,std::normal_distribution<>(0.0f, 5.0f));
    std::variate_generator<std::mt19937&, std::normal_distribution<>> generatorY(engine,std::normal_distribution<>(0.0f, 5.0f));
    std::variate_generator<std::mt19937&, std::normal_distribution<>> generatorVelZ(engine,std::normal_distribution<>(0.0f, 1.0f));
    std::variate_generator<std::mt19937&, std::normal_distribution<>> generatorOri(engine,std::normal_distribution<>(0.0f, 30.0f*deg2rad));
    std::variate_generator<std::mt19937&, std::normal_distribution<>> generatorOriVel(engine,std::normal_distribution<>(0.0f, 30.0f*deg2rad));

    // This causes an endless loop somehow, even though it should work according to manuals.
//     auto r_norm = std::bind(rand_norm, eng);

    for(int i = 0 ; i < 20 ; ++i) {
        Vector pos(generatorX(), generatorY(), -5.0f);
/*        Vector vel(0.0f, 0.0f, generatorVelZ());
        float ori = generatorOri();
        float oriVel = generatorOriVel();*/
        Vector vel(0.0f, 0.0f, 0.0f);
        float ori = 0.0f;
        float oriVel = 0.0f;
        m_civs.push_back(new Civilian(pos, vel, ori, oriVel, m_shaderManager));
    }
}

Level::Ptr Level::load(const Configuration& in_settings, const std::string& in_sName)
{
    return Level::Ptr(new Level(in_settings, in_sName));
}

void Level::think(const GameClock& clock)
{
//     const float speed = 5.0f;
//     m_cam.orbitCenter(Vector(5.0f, 0.0f, 0.0f));
//     m_cam.orbit(Quaternion::rotation(0.0f, 1.0f, 0.0f, clock.now()*speed*deg2rad));

    m_pAvatar->think(clock);

    // Follow the avatar.
    m_cam.pos(Vector(0.0f, 0.0f, 10.0f));
    m_cam.orbitCenter(m_pAvatar->pos());

    // And the height/angle of the camera is dependend on the avatar's speed.
    const float fMinAngle = 25.0f*deg2rad;
    const float fMaxAngle = 45.0f*deg2rad;
    float fSpeedPercent = m_pAvatar->speed() / m_pAvatar->maxSpeed();
    float fAngle = lerp(fMaxAngle, fMinAngle, clamp(fSpeedPercent*1.5f, 0.0f, 1.0f));
    m_cam.orbit(Quaternion::rotation(1.0f, 0.0f, 0.0f, -fAngle));

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

Avatar& Level::avatar()
{
    return *m_pAvatar;
}

const Avatar& Level::avatar() const
{
    return *m_pAvatar;
}
