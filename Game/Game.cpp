#include "Game.h"

#include "Utilities/String.h"

#include <SFML/Graphics/Text.hpp>

using namespace RoadRage;

Game::Game(Level::Ptr in_pLevel, const sf::Input& in_input)
    : m_clock()
    , m_pLevel(in_pLevel)
    , m_input(in_input)
{
}

void Game::think()
{
    m_clock.tick();

    m_pLevel->avatar().input(m_input);
    m_pLevel->think(m_clock);
}

void Game::render(sf::RenderTarget& in_rt)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    m_pLevel->render(m_clock);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    const Avatar& avatar = m_pLevel->avatar();
    std::string state;
    switch(avatar.state()) {
    case CarState::Breaking: state = "Breaking"; break;
    case CarState::Destroyed: state = "Destroyed"; break;
    case CarState::Driving: state = "Driving"; break;
    case CarState::Rolling: state = "Rolling"; break;
    case CarState::Standing: state = "Standing"; break;
    }

    std::string sDbg =
        "Avatar steering angle: " + to_s(avatar.steeringAngle() * rad2deg) + "\n" +
        "Avatar acceleration: " + to_s(avatar.accel()) + " (" + to_s(avatar.accel()*mss2kmhs) + "km/h/s)" "\n" +
        "Avatar speed: " + to_s(avatar.speed()) + " (" + to_s(avatar.speed()*ms2kmh) + "km/h)" + "\n" +
        "Avatar pos: " + avatar.pos().to_s() + " (m,m,m)\n" +
        "Avatar state: " + state + "\n";
    in_rt.Draw(sf::Text(sDbg));
}
