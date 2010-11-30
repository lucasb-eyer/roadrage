#include "Game.h"

using namespace RoadRage;

Game::Game(Level::Ptr in_pLevel)
    : m_clock()
    , m_pLevel(in_pLevel)
{
}

void Game::think()
{
    m_clock.tick();

    m_pLevel->think(m_clock);
}

void Game::render()
{
    m_pLevel->render(m_clock);
}
