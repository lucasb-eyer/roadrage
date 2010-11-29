#include "RoadRageDefaultSettings.h"

#include "Utilities/String.h"

#include <SFML/Window/VideoMode.hpp>

using namespace RoadRage;

RoadRageDefaultSettings::RoadRageDefaultSettings()
{
    sf::VideoMode defaultMode = sf::VideoMode::GetDesktopMode();

    add("Width", to_s(defaultMode.Width));
    add("Height", to_s(defaultMode.Height));
    add("Fullscreen", "1");
    add("AntiAliasing", "2");
}

RoadRageDefaultSettings::~RoadRageDefaultSettings()
{
}
