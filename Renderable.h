#pragma once
#include <SFML/Graphics/Drawable.hpp>

class Renderable : public sf::Drawable
{
public:
	// Constructors and Destructors
	Renderable() = default;
	~Renderable() = default;

public:
	// Virtual Pure Methods
	virtual sf::Vector2f GetPosition() = 0;

public:
	// Virtual Methods w/ Default Implementation
	virtual void SetPosition(sf::Vector2f position) {};

public:
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
};
