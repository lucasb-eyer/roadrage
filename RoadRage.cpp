
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "3d/OpenGLWrapper.h"

#include "Conf/Configuration.h"
#include "Conf/RoadRageDefaultSettings.h"

#include "Utilities/Path.h"
#include "Utilities/String.h"
#include "Utilities/i18n.h"

#include "3d/Math/Matrix.h"
#include "3d/Math/Quaternion.h"
#include "3d/Math/Vector.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "3d/BuiltinModel.h"

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

    sf::Window window(mode, _("Road Rage by Pompei2"), style, ctx);

    // Create a clock for measuring the time elapsed
    sf::Clock clock;

    // Set the color and depth clear values
    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.25f, 0.f);

    // Enable Z-buffer read and write
//     glEnable(GL_DEPTH_TEST);
//     glDepthMask(GL_TRUE);

    // Setup a perspective projection
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     gluPerspective(90.f, 1.f, 1.f, 500.f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    ShaderManager mgr;
    BoxModel mdl(&mgr);

    float ratio = to<float>(settings.get("Width")) / to<float>(settings.get("Height"));
    General4x4Matrix cam = General4x4Matrix::perspectiveProjection(45.0f, ratio) * AffineMatrix::translation(-1.5f, -1.0f, -5.0f);

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

        // This might have changed since we processed all events.
        if(!window.IsOpened())
            break;

        // Activate the window before using OpenGL commands.
        // This is useless here because we have only one window which is
        // always the active one, but don't forget it if you use multiple windows
        window.SetActive();

        // Clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mdl.render(cam);

        // Apply some transformations
//         glMatrixMode(GL_MODELVIEW);
//         glLoadIdentity();
//         glTranslatef(0.f, 0.f, -200.f);
//         glRotatef(clock.GetElapsedTime() * 50, 1.f, 0.f, 0.f);
//         glRotatef(clock.GetElapsedTime() * 30, 0.f, 1.f, 0.f);
//         glRotatef(clock.GetElapsedTime() * 90, 0.f, 0.f, 1.f);

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
