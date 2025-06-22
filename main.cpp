#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Simulater.h"
#include "Renderer.h"
#include "Controller.h"
#include "Camera.h"
#include "Player.h"
#include "Level.h"
#include "TestObject.h"
#include "TextRecipe.h"
#include "BackgroundLayer.h"

using namespace std;

// This version of SFML is statically linked, there is also the dynamically linked version as well.
int WinMain()
{
    // Create objects on stack
    sf::RenderWindow _gameWindow(sf::VideoMode({ 800, 800}), "Mission: Squark");
    Renderer _coreGameRenderer;
    Renderer _coreUIRenderer;
    Camera _gameCamera;
    Camera _uiCamera;
    Simulater _coreSimulater;
    Controller _coreController;
    Player _player;
    Level _level;
    BackgroundLayer _bgSky("BG_solid.png");
    BackgroundLayer _bgFarGround("BG_ground.png");
    BackgroundLayer _bgGround("BG_ground.png");
    BackgroundLayer _bgSeaFar("BG_solid.png");
    BackgroundLayer _bgSeaMid("BG_solid.png");
    BackgroundLayer _bgSeaNear("BG_solid.png");
    TextRecipe _uiBalloonCountTitle(TextFontTypes::FontForText::Silkscreen, "Takedowns:", 30, sf::Color::White, sf::Text::Bold);
    TextRecipe _uiBalloonCountValue(TextFontTypes::FontForText::Silkscreen, "0", 30, sf::Color::White, sf::Text::Bold);
    TextRecipe _uiSpeedTitle(TextFontTypes::FontForText::Silkscreen, "Velocity:", 30, sf::Color::White, sf::Text::Bold);
    TextRecipe _uiSpeedValue(TextFontTypes::FontForText::Silkscreen, "0", 30, sf::Color::White, sf::Text::Bold);
    sf::Music _bgmTrack;
    sf::SoundBuffer _sfxBuffHit;
    sf::Sound _sfxHit(_sfxBuffHit);

    // Core objects setup
    _coreController.AddControllable(&_player);
    _level.SetMapIndex(0);
    _level.SetPlayerRef(&_player);
    _player.SetPosition(_level.GetPlayerStartPos(_level.GetMapIndex()));

    // Background object setup
    _bgSky.SetParallaxSource(_player);
    _bgSky.SetParallaxFactor(sf::Vector2f(0.5f, 0.5f));
    _bgSky.SetPosition(sf::Vector2f(-800.0f, -4000.0f));
    _bgSky.SetBackgroundOffset(sf::Vector2f(0.0f, -200.0f));
    _bgSky.SetColourTint(sf::Color(155, 213, 255));

    _bgFarGround.SetParallaxSource(_player);
    _bgFarGround.SetParallaxFactor(sf::Vector2f(0.4, 0.4f));
    _bgFarGround.SetPosition(sf::Vector2f(-600.0f, -3800.0f));
    _bgFarGround.SetBackgroundOffset(sf::Vector2f(0.0f, -200.0f));
    _bgFarGround.SetColourTint(sf::Color(50, 150, 50));

    _bgGround.SetParallaxSource(_player);
    _bgGround.SetParallaxFactor(sf::Vector2f(0.3f, 0.3f));
    _bgGround.SetPosition(sf::Vector2f(-600.0f, -2900.0f));
    _bgGround.SetBackgroundOffset(sf::Vector2f(0.0f, -200.0f));
    _bgGround.SetColourTint(sf::Color(90, 206, 41));
    _bgGround.GetTexture().setRepeated(true);

    _bgSeaFar.SetParallaxSource(_player);
    _bgSeaFar.SetParallaxFactor(sf::Vector2f(0.5, 0.25f));
    _bgSeaFar.SetPosition(sf::Vector2f(-600.0f, 1500.0f));
    _bgSeaFar.SetBackgroundOffset(sf::Vector2f(0.0f, -200.0f));
    _bgSeaFar.SetColourTint(sf::Color(150, 150, 255));
    
    _bgSeaMid.SetParallaxSource(_player);
    _bgSeaMid.SetParallaxFactor(sf::Vector2f(0.5, 0.2f));
    _bgSeaMid.SetPosition(sf::Vector2f(-600.0f, 1550.0f));
    _bgSeaMid.SetBackgroundOffset(sf::Vector2f(0.0f, -200.0f));
    _bgSeaMid.SetColourTint(sf::Color(100, 100, 255));

    _bgSeaNear.SetParallaxSource(_player);
    _bgSeaNear.SetParallaxFactor(sf::Vector2f(0.5, 0.15f));
    _bgSeaNear.SetPosition(sf::Vector2f(-600.0f, 1600.0f));
    _bgSeaNear.SetBackgroundOffset(sf::Vector2f(0.0f, -200.0f));
    _bgSeaNear.SetColourTint(sf::Color(50, 50, 255));

    // UI objects setup
    _uiBalloonCountTitle.SetPosition(sf::Vector2f(350.0f, 100.0f));
    _uiBalloonCountValue.SetPosition(sf::Vector2f(650.0f, 100.0f));

    _uiSpeedTitle.SetPosition(sf::Vector2f(100.0f, 900.0f));
    _uiSpeedValue.SetPosition(sf::Vector2f(300.0f, 900.0f));
    _uiSpeedValue.SetOrigin(sf::Vector2f(0.0f, 1.0f));

    // Setup sound
    if (!_bgmTrack.openFromFile("MissionSquark_track.wav"))
    {
        throw runtime_error("Failed to load audio");
    }
    _bgmTrack.setLooping(true);
    _bgmTrack.play();

    if (!_sfxBuffHit.loadFromFile("MissionSquark_hit.wav"))
    {
        throw runtime_error("Failed to load audio");
    }

    // Add simulatables
    _coreSimulater.AddSimulatable(&_player);
    _coreSimulater.AddSimulatable(&_level);

    // Add game renderables
    _coreGameRenderer.AddRenderable(&_bgSky);
    _coreGameRenderer.AddRenderable(&_bgFarGround);
    _coreGameRenderer.AddRenderable(&_bgGround);
    _coreGameRenderer.AddRenderable(&_bgSeaFar);
    _coreGameRenderer.AddRenderable(&_bgSeaMid);
    _coreGameRenderer.AddRenderable(&_bgSeaNear);
    _coreGameRenderer.AddRenderable(&_level);
    _coreGameRenderer.AddRenderable(&_player);

    // Add UI renderables
    _coreUIRenderer.AddRenderable(&_uiBalloonCountValue);
    _coreUIRenderer.AddRenderable(&_uiBalloonCountTitle);
    _coreUIRenderer.AddRenderable(&_uiSpeedValue);
    _coreUIRenderer.AddRenderable(&_uiSpeedTitle);
    
    // Connect bindable functions
    _level.BalloonsUpdated = [&](int balloonCount)
        {
            _uiBalloonCountValue.SetString(std::to_string(balloonCount));
            _sfxHit.play();
        };
    _level.LevelCollided = [&]()
        {
            _sfxHit.play();
        };
    _player.SpeedUpdated = [&](int speedValue)
        {
            int speedThreshold = 10;
            int minTextSize = 30;
            int textSize = minTextSize + (speedValue / speedThreshold);

            _uiSpeedValue.SetString(std::to_string(speedValue));
            _uiSpeedValue.SetSize(textSize);
        };


    // Setup deltatime
    std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
    float deltaTime = 0.0f;
    float timeSiceLastPhysicsLoop = 0.0f;
    float physicsTimeStep = 2000.0f;

    // Main Loop (for when the window is open)
    while (_gameWindow.isOpen())
    {
        // Poll for events
        while (const std::optional event = _gameWindow.pollEvent())
        {
            // Window closing event
            if (event->is<sf::Event::Closed>())
            {
                _gameWindow.close();
            }
            else if (const sf::Event::KeyPressed* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                _coreController.BroadcastKeyPressed(keyPressed->code);
            }
            else if (const sf::Event::KeyReleased* keyreleased = event->getIf<sf::Event::KeyReleased>())
            {
                _coreController.BroadcastKeyReleased(keyreleased->code);
            }
        }

        // Deltatime phys loop
        deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - lastTime).count();
        lastTime = std::chrono::steady_clock::now();
        timeSiceLastPhysicsLoop += deltaTime;
        while (timeSiceLastPhysicsLoop > physicsTimeStep)
        {
            timeSiceLastPhysicsLoop -= physicsTimeStep;
            _coreSimulater.StepSimulatables();
        }

        // Rendering segment
        _gameCamera.SetTarget(&_player);
        _gameCamera.GetView().setSize(sf::Vector2f(_gameWindow.getSize()));
        _uiCamera.GetView().setSize(sf::Vector2f(_gameWindow.getSize()));

        _gameCamera.SetZoom(_player.GetFlightSpeed());
        _gameCamera.Move(sf::Vector2f(150.0f + (_player.GetFlightSpeed() * 200.0f), 0.0f));
        _uiCamera.SetZoom(1.0f);

        _gameWindow.clear();

        _gameWindow.setView(_gameCamera.GetView());
        _coreGameRenderer.DrawDrawables(&_gameWindow);

        _gameWindow.setView(_uiCamera.GetView());
        _coreUIRenderer.DrawDrawables(&_gameWindow);

        _gameWindow.display();
    }
} //Sometimes the RenderWindow causes a crash when closing the application. Most PCs have no issues with the RenderWindow deconstructor but some do.