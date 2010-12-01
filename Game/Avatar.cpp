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
        this->accel(this->accel() + 0.1f);
    } else if(in_input.IsKeyDown(sf::Key::Down)) {
        this->accel(-this->speed()*2.f);
    } else {
        // If no speed key is pressed, strive to no speed.
        this->accel(-this->speed()*0.5f);
    }

    /*
    // Banking to the left and right:
    if(in_input.IsKeyDown(sf::Key::Left)) {
        this->accel(this->accel().x(-2.0f));
    } else if(in_input.IsKeyDown(sf::Key::Right)) {
        this->accel(this->accel().x(2.0f));
    } else {
        // Break down in case we are still moving.
        if(!nearZero(this->vel().len())) {
            if((this->accel().x() < 0.0f) == (this->vel().x() < 0.0f)) {
                // If they got the same sign, break!
                this->accel().x(-this->accel().x());
            } else {
                // If they got different sign (i.e. we are breaking), check when to stop to break.
            }
        }
//         this->accel(this->accel().x(0.0f));
//         this->vel(this->vel().x(0.0f));
    }
    */
}

void Avatar::think(const RoadRage::GameClock& clock)
{
    Car::think(clock);
}

void RoadRage::Avatar::render(const RoadRage::GameClock& /*clock*/, const General4x4Matrix& in_viewProj)
{
    m_model.render(in_viewProj * this->getModelMatrix());
}
