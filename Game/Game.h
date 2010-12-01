#pragma once

#include "GameClock.h"
#include "Level.h"

#include <SFML/Window/Input.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace RoadRage {

class Game {
public:
    Game(Level::Ptr in_pLevel, const sf::Input& in_input);

    void think();
    void render(sf::RenderTarget& in_rt);

private:
    GameClock m_clock;

    Level::Ptr m_pLevel;

    const sf::Input& m_input;
};

}
