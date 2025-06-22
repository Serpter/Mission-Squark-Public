#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <cmath>
#include <iostream>
#include "Level.h"
#include "Player.h"

using namespace std;

Player::Player() {
    FlightCurrentDirection = 0;
    FlightCurrentAngle = 90.0f;
    FlightCurrentSpeed = 0.0f;
    CurrentSoarValue = 0;

    Position = sf::Vector2f(0.0f, 0.0f);
    StoredInput = sf::Vector2f(0.0f, 0.0f);
    Body.setSize(sf::Vector2f(50,50));
    Body.setFillColor(sf::Color::Red);
    Body.setPosition(Position);
    Body.setOrigin(sf::Vector2f(0.5f, 0.5f));
    VelocityDirection = sf::Vector2f(0.0f, 0.0f);

    CurrentLandingSequenceStage = 0;
    CurrentLandingWaitTime = 0;
    IsLandingSequence = true;
    CanSoar = true;

    {
        if (!Soar1.loadFromFile("Plr_ReallyLow.png", false, sf::IntRect({ 0, 0 }, { 16, 16 })))
        {
            throw runtime_error("Failed to load texture");
        }
        if (!Soar2.loadFromFile("Plr_Low.png", false, sf::IntRect({ 0, 0 }, { 16, 16 })))
        {
            throw runtime_error("Failed to load texture");
        }
        if (!Soar3.loadFromFile("Plr_Mid.png", false, sf::IntRect({ 0, 0 }, { 16, 16 })))
        {
            throw runtime_error("Failed to load texture");
        }
        if (!Soar4.loadFromFile("Plr_High.png", false, sf::IntRect({ 0, 0 }, { 16, 16 })))
        {
            throw runtime_error("Failed to load texture");
        }
        if (!Soar5.loadFromFile("Plr_ReallyHigh.png", false, sf::IntRect({ 0, 0 }, { 16, 16 })))
        {
            throw runtime_error("Failed to load texture");
        }
    }
}

void Player::SetInput(sf::Vector2f input)
{
    StoredInput = input;
}

void Player::ClearVelocitySpeed()
{
    FlightCurrentSpeed = 0;
}

void Player::SetLandingStatus(bool status)
{
    IsLandingSequence = status;
}

void Player::SetCanSoar(bool value)
{
    CanSoar = value;
}

int Player::GetCollidingStatus(Level* level)
{
    if (level == nullptr) { return -2; }
    int _collidedTile = level->GetTileAtWorldPosition(Position);

    if (_collidedTile == -1)
    {
        return -1;
    }
    else if (_collidedTile > 0)
    {
        switch (_collidedTile)
        {
        case 10:
            return 2;
        default:
            return 1;
            break;
        }
    }
    else
    {
        return 0;
    }
}

sf::Vector2f Player::GetInput()
{
    return StoredInput;
}

sf::Vector2f Player::GetVelocity()
{
    return VelocityDirection * FlightCurrentSpeed;
}

bool Player::GetLandingStatus()
{
    return IsLandingSequence;
}

float Player::GetFlightSpeed()
{
    return FlightCurrentSpeed;
}

sf::Vector2f Player::RotateVector(sf::Vector2f vector, float angle)
{
    float _angleRadians = angle * 3.141f / 180.0f;
    float _cosAngle = std::cos(_angleRadians);
    float _sinAngle = std::sin(_angleRadians);

    return
    {
        vector.x * _cosAngle - vector.y * _sinAngle,
        vector.x * _sinAngle + vector.y * _cosAngle
    };
}

void Player::Step()
{
    if (IsLandingSequence) // Auto control
    {
        switch (CurrentLandingSequenceStage)
        {
        case 0: // Slowdown stage
            if (FlightCurrentSpeed > 0)
            {
                FlightCurrentDirection = 0;
                FlightCurrentSpeed -= PlatformLandingRate;
                VelocityDirection = sf::Vector2f(1.0f, 0.0f);
            }
            else //First point where a non looping execution happens - can reset state here
            {
                CurrentSoarValue = 0; 
                FlightCurrentDirection = 0;

                if (FlightCurrentSpeed < 0)
                {
                    FlightCurrentSpeed = 0;
                }
                CanSoar = true;
                CurrentLandingSequenceStage = 1;
            }

            break;
        case 1: // Wait stage
            CurrentLandingWaitTime += 1;

            if (CurrentLandingWaitTime >= MaxLandingWaitTime)
            {
                CurrentLandingSequenceStage = 2;
            }
            break;
        case 2: // Launch stage
            VelocityDirection = sf::Vector2f(1.0f, 0.0f);
            FlightCurrentSpeed += PlatformLaunchingRate;

            if (FlightCurrentSpeed > PlatformLaunchTargetSpeed)
            {
                FlightCurrentSpeed = PlatformLaunchTargetSpeed;
                CurrentLandingSequenceStage = 3;
            }
            break;
        case 3: // Incline Stage
            CurrentSoarValue += 1;

            if (CurrentSoarValue >= SwoopThresholdIncrement) // We have crossed the threshold for swooping
            { 
                if (FlightCurrentDirection + 1 <= FlightDirections) // We can go up a direction
                { 
                    CurrentSoarValue = 0;
                    FlightCurrentDirection += 1;
                }
                else // We have hit the limit of directions
                { 
                    if (CurrentSoarValue > MaxLaunchingWaitTime) // The soar value has reached the launching swoop hold duration
                    { 
                        CurrentSoarValue = SwoopThresholdIncrement - SwoopIncrement;
                        CurrentLandingSequenceStage = 4;
                    }
                }
            }

            // This setting the Y manually makes the player move up too fast. How to do what usually happens but clamp it so it cant descend?
            VelocityDirection = sf::Vector2f(FlightCurrentSpeed, (-CurrentSoarValue + -(FlightCurrentDirection * SwoopThresholdIncrement)) * 0.002f);
            FlightCurrentAngle = FlightCurrentDirection * -FlightDirectionAngleIncrement;
            break;
        case 4: // Clearing launch sequence/cleanup
            IsLandingSequence = false;
            CurrentLandingWaitTime = 0;
            CurrentLandingSequenceStage = 0;
            break;
        default:
            break;
        }
    }
    else // Player control
    {
        if (StoredInput.y > 0 && CanSoar)
        {
            if ((CurrentSoarValue + SwoopIncrement) < SwoopThresholdIncrement)
            {
                CurrentSoarValue += SwoopIncrement;
            }
            else
            {
                if (FlightCurrentDirection + 1 < FlightDirections)
                {
                    CurrentSoarValue = 0;
                    FlightCurrentDirection += 1;
                }
            }
        }
        else
        {
            if ((CurrentSoarValue - GlideIncrement) > 0)
            {
                CurrentSoarValue -= GlideIncrement;
            }
            else
            {
                if (FlightCurrentDirection - 1 > -1)
                {
                    CurrentSoarValue = SwoopThresholdIncrement;
                    FlightCurrentDirection -= 1;
                }
            }
        }
    }

    if ((IsLandingSequence && CurrentLandingSequenceStage > 3) || (!IsLandingSequence))
    {
        // Figuring direction and rotation of it based on turn counter
        VelocityDirection = RotateVector(BaseSoarDirection, FlightCurrentDirection * -FlightDirectionAngleIncrement);
        float _velocityDirectionMagnitude = std::sqrt((VelocityDirection.x * VelocityDirection.x) + (VelocityDirection.y * VelocityDirection.y));
        VelocityDirection = sf::Vector2f(VelocityDirection.x / _velocityDirectionMagnitude, VelocityDirection.y / _velocityDirectionMagnitude);

        // Calculating speed change
        FlightCurrentAngle = FlightCurrentDirection * -FlightDirectionAngleIncrement;

        int _directiondiff = 2 - FlightCurrentDirection;

        if (_directiondiff > 0) // Accelerative speed change
        {
            FlightCurrentSpeed += _directiondiff * 0.00010f;
        }
        else if (_directiondiff < 0) // Decelerative speed change
        {
            FlightCurrentSpeed += _directiondiff * 0.00005f;
        }
    }

    Position += VelocityDirection * FlightCurrentSpeed;

    // Move body by velocity
    Body.setPosition(Position); 

    // Update display speed
    if (SpeedUpdated)
    {
        SpeedUpdated((int)(FlightCurrentSpeed * 100));
    }
}

sf::Vector2f Player::GetPosition()
{
    return Position;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Sprite _playerSprite(Soar5);

    switch (FlightCurrentDirection)
    {
    case 0:
        _playerSprite.setTexture(Soar1);
        break;
    case 1:
        _playerSprite.setTexture(Soar2);
        break;
    case 2:
        _playerSprite.setTexture(Soar3);
        break;
    case 3:
        _playerSprite.setTexture(Soar4);
        break;
    case 4:
        _playerSprite.setTexture(Soar5);
        break;
    default:
        break;
    }

    _playerSprite.setPosition(Position);
    _playerSprite.setScale(sf::Vector2f(5.0f, 5.0f));
    _playerSprite.setOrigin(sf::Vector2f(7.0f, 5.0f));

    target.draw(_playerSprite, states);
}

void Player::SetPosition(sf::Vector2f position)
{
    Position = position;
    Body.setPosition(Position);
}

void Player::KeyPressed_Space()
{
    SetInput(sf::Vector2f(GetInput().x, 1.0f));
}

void Player::KeyReleased_Space()
{
    SetInput(sf::Vector2f(GetInput().x, 0.0f));
}
