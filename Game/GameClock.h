#pragma once
#include <SFML/System/Clock.hpp>

namespace RoadRage {

class GameClock {
public:
    GameClock();

    void tick();

    float deltaT() const;
    float now() const;

private:
    sf::Clock m_clock;

    float m_fLastTick;
    float m_fNow;
};

}
