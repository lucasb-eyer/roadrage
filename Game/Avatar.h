#pragma once

#include "Car.h"
#include "GameClock.h"

#include "3d/BuiltinModel.h"

#include <SFML/Window/Input.hpp>

namespace RoadRage {

class Avatar : public Car {
public:
    Avatar(ShaderManager& shadmgr);
    virtual ~Avatar();

    void input(const sf::Input& in_input);
    void think(const GameClock& clock);
    void render(const GameClock& clock, const General4x4Matrix& in_viewProj);

private:
    BoxModel m_model;
};

}
