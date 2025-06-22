#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <functional>
#include "Simulatable.h"
#include "Renderable.h"
#include "Controllable.h"

class Level;
namespace sf {
    class Sprite;
}

class Player : public Simulatable, public Renderable, public Controllable
{
public:
    // Constructors and Destructors
    Player();
    ~Player() = default;

private:
    // Members

    /// <summary>
    /// The number of flight angles
    /// </summary>
    const int FlightDirections = 5;

    /// <summary>
    /// The span which each multiple of flightDirections rotates the player by
    /// </summary>
    const float FlightDirectionAngleIncrement = 22.0f;

    /// <summary>
    /// Increment amount to raise currentSoarValue by
    /// </summary>
    const int SwoopIncrement = 3;

    /// <summary>
    /// Decrement amount to lower currentSoarValue by
    /// </summary>
    const int GlideIncrement = 2;

    /// <summary>
    /// Numeric threshold which will raise flightCurrentDirection by 1 once exceeded
    /// </summary>
    const int SwoopThresholdIncrement = 100;

    const sf::Vector2f BaseSoarDirection = sf::Vector2f(0.1f, 0.1f);
    const sf::Vector2f HorizontalVelocityLimits = sf::Vector2f(999.0f, 999.0f);
    const sf::Vector2f VerticalVelocityLimits = sf::Vector2f(-0.025f, 0.02f);

    const int MaxLandingWaitTime = 1000;
    const int MaxLaunchingWaitTime = 200;
    const float PlatformLandingRate = 0.0006f;
    const float PlatformLaunchingRate = 0.0004f;
    const float PlatformLaunchTargetSpeed = 1.0f;

    int FlightCurrentDirection; // what direction are we using right now?
    float FlightCurrentAngle; // what is the current stored angle
    float FlightCurrentSpeed; // what is the current stored speed
    int CurrentSoarValue; 

    sf::Vector2f Position;
    sf::Vector2f StoredInput;
    sf::RectangleShape Body;
    sf::Vector2f VelocityDirection;

    bool IsLandingSequence;
    int CurrentLandingSequenceStage;
    int CurrentLandingWaitTime;
    bool CanSoar;

    sf::Texture Soar1;
    sf::Texture Soar2;
    sf::Texture Soar3;
    sf::Texture Soar4;
    sf::Texture Soar5;
    sf::Texture CurrentTexture;

public:
    // Methods
    void SetInput(sf::Vector2f input);
    void ClearVelocitySpeed();
    void SetLandingStatus(bool status);
    void SetCanSoar(bool value);

public:
    // Type Methods
    int GetCollidingStatus(Level* level);
    sf::Vector2f GetInput();
    sf::Vector2f GetVelocity();
    bool GetLandingStatus();
    float GetFlightSpeed();

private:
    // Private Type Methods
    sf::Vector2f RotateVector(const sf::Vector2f vector, float angleDegrees);

public:
    // Wrapped Functions
    std::function<void(int)> SpeedUpdated;

public:
    // Inherited via Simulatable
	void Step() final override;

public:
    // Inherited via Renderable
    sf::Vector2f GetPosition() final override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final override;
    void SetPosition(sf::Vector2f position) final override;

public:
    // Inherited via Controllable
    void KeyPressed_Space() final override;
    void KeyReleased_Space() final override;
};
