#include "GameClock.h"

using namespace RoadRage;

GameClock::GameClock()
    : m_clock()
    , m_fLastTick(0.0f)
    , m_fNow(0.001f)
{
}

void GameClock::tick()
{
    m_fLastTick = m_fNow;
    m_fNow = m_clock.GetElapsedTime();
}

float GameClock::deltaT() const
{
    return m_fNow - m_fLastTick;
}

float GameClock::now() const
{
    return m_fNow;
}
