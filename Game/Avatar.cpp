#include "Avatar.h"

#include <SFML/Window/Input.hpp>

using namespace RoadRage;

Avatar::Avatar(ShaderManager& shadmgr)
    : Car(Vector(), Vector())
    , m_model(shadmgr)
{
}

Avatar::~Avatar()
{
}

void Avatar::input(const sf::Input& in_input)
{
    if(in_input.IsKeyDown(sf::Key::Left)) {
        this->steeringVel(45.0f*deg2rad);
    } else if(in_input.IsKeyDown(sf::Key::Right)) {
        this->steeringVel(-45.0f*deg2rad);
    } else {
        // If no direction key is pressed, strive to drive straight.
        this->steeringVel(-this->steeringAngle()*5.f);
    }

    if(in_input.IsKeyDown(sf::Key::Up)) {
        this->state(CarState::Driving);
//         this->accel(this->accel() + 0.1f);
    } else if(in_input.IsKeyDown(sf::Key::Down)) {
        this->state(CarState::Breaking);
//         this->accel(-this->speed()*2.f);
    } else {
        // If no speed key is pressed, strive to no speed.
        this->state(CarState::Rolling);
//         this->accel(-this->speed()*0.5f);
    }
}

void Avatar::think(const RoadRage::GameClock& clock)
{
    Car::think(clock);
}

void RoadRage::Avatar::render(const RoadRage::GameClock& /*clock*/, const General4x4Matrix& in_viewProj)
{
    m_model.render(in_viewProj * this->getModelMatrix());
}
