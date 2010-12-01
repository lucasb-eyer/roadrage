
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "3d/Math/Matrix.h"
#include "3d/OpenGLWrapper.h"

#include "Conf/Configuration.h"
#include "Conf/RoadRageDefaultSettings.h"

#include "Game/Game.h"
#include "Game/GameClock.h"
#include "Game/Level.h"

#include "Utilities/Path.h"
#include "Utilities/String.h"
#include "Utilities/i18n.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace RoadRage;

int DisplayError(const std::string& what);

////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main()
{
try {

    // Check that the system can use shaders
    if(!sf::Shader::IsAvailable())
        throw(_("Shaders are not supported by your graphics card!"));

    // Load the settings
    Configuration settings(getUserDir() + "/conf.xml", RoadRageDefaultSettings());

    // Create the main window
    long unsigned int style = to<bool>(settings.get("Fullscreen")) ? sf::Style::Fullscreen : sf::Style::Default;
    sf::ContextSettings ctx(24, 8, to<unsigned>(settings.get("AntiAliasing")), 3, 2);
    sf::VideoMode mode(to<unsigned>(settings.get("Width")), to<unsigned>(settings.get("Height")), 32);

    sf::RenderWindow window(mode, _("Road Rage by Pompei2"), style, ctx);

    // Set the color and depth clear values
    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.25f, 0.f);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    // Load the game engine with the level we want to play.
    Game game(Level::load(settings, "BlaBla"), window.GetInput());

    // Start the game loop
    while(window.IsOpened())
    {
        // Process events
        sf::Event event;
        while(window.GetEvent(event))
        {
            // Close window : exit
            if(event.Type == sf::Event::Closed)
                window.Close();

            // Escape key : exit
            if((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape))
                window.Close();

            // Resize event : adjust viewport
            if(event.Type == sf::Event::Resized)
                glViewport(0, 0, event.Size.Width, event.Size.Height);
        }

        // Simulate one step of the game.
        game.think();

        // This might have changed since we processed all events.
        if(!window.IsOpened())
            break;

        // Activate the window before using OpenGL commands.
        // This is useless here because we have only one window which is
        // always the active one, but don't forget it if you use multiple windows
        window.SetActive();

        // Clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw the whole game.
        game.render(window);

        // Finally, display the rendered frame on screen
        window.Display();
    }

    return EXIT_SUCCESS;
} catch(const std::exception& e) {
    return DisplayError(e.what());
}
}

////////////////////////////////////////////////////////////
/// Function called when the post-effects are not supported ;
/// Display an error message and wait until the user exits
///
////////////////////////////////////////////////////////////
int DisplayError(const std::string& what)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), _("RoadRage by Pompei2"));

    // Define a string for displaying the error message
    sf::Text error(what);
    error.SetCharacterSize(12);
    error.SetPosition(50.f, 250.f);
    error.SetColor(sf::Color(200, 100, 150));

    // Start the game loop
    while (window.IsOpened())
    {
        // Process events
        sf::Event event;
        while (window.GetEvent(event))
        {
            // Close window : exit
            if (event.Type == sf::Event::Closed)
                window.Close();

            // Escape key : exit
            if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape))
                window.Close();
        }

        // Clear the window
        window.Clear();

        // Draw the error message
        window.Draw(error);

        // Finally, display the rendered frame on screen
        window.Display();
    }

    return 0;
}
