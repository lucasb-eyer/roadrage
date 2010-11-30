#pragma once

#include "GameClock.h"
#include "Level.h"

namespace RoadRage {

class Game {
public:
    Game(Level::Ptr in_pLevel);

    void think();
    void render();

private:
    GameClock m_clock;

    Level::Ptr m_pLevel;
};

}
