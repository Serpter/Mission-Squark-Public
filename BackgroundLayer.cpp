#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cmath>
#include <functional>
#include "Renderable.h"
#include "Simulatable.h"
#include "BackgroundLayer.h"

using namespace std;

BackgroundLayer::BackgroundLayer(std::filesystem::path texturePath)
{
	if (!SourceTexture.loadFromFile(texturePath))
	{
		throw runtime_error("Failed to load texture file path");
	}

	Position = sf::Vector2f(0.0f, 0.0f);
	ParallaxFactor = sf::Vector2f(0.0f, 0.0f);
	ParallaxSource = nullptr;
	ColourTint = sf::Color(255, 255, 255);
	BackgroundOffset = sf::Vector2f(0.0f, -200.0f);
}

void BackgroundLayer::SetTexture(std::filesystem::path texturePath)
{
	if (!SourceTexture.loadFromFile(texturePath))
	{
		throw runtime_error("Failed to load texture file path");
	}
}

void BackgroundLayer::SetParallaxFactor(sf::Vector2f strength)
{
	ParallaxFactor = strength;
}

void BackgroundLayer::SetParallaxSource(Renderable& object)
{
	ParallaxSource = &object;
}

void BackgroundLayer::SetColourTint(sf::Color colour)
{
	ColourTint = colour;
}

sf::Texture BackgroundLayer::GetTexture()
{
	return SourceTexture;
}

void BackgroundLayer::SetBackgroundOffset(sf::Vector2f offset)
{
	BackgroundOffset = offset;
}

sf::Vector2f BackgroundLayer::GetBackgroundOffset()
{
	return BackgroundOffset;
}

sf::Vector2f BackgroundLayer::GetPosition()
{
	return Position;
}

void BackgroundLayer::SetPosition(sf::Vector2f position)
{
	Position = position;
}

void BackgroundLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Sprite _sprite(SourceTexture);
	_sprite.setScale(sf::Vector2f(10.0f, 10.0f));
	_sprite.setColor(ColourTint);

	if (ParallaxSource != nullptr)
	{
		float _x = (Position.x * (1 - ParallaxFactor.x) + ParallaxSource->GetPosition().x * ParallaxFactor.x);
		float _y = (Position.y * (1 - ParallaxFactor.y) + ParallaxSource->GetPosition().y * ParallaxFactor.y);

		_sprite.setPosition(sf::Vector2f(_x, _y) + BackgroundOffset);
	}
	else
	{
		_sprite.setPosition(Position + BackgroundOffset);
	}

	target.draw(_sprite, states);
}