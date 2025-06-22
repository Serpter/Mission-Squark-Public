#pragma once
#include "Renderable.h"

class Tile : Renderable
{
public:
	// Constructors and Destructors
	Tile();
	~Tile() = default;

private:
	// Members
	sf::Vector2f TileSize;
	sf::RectangleShape Body;

public:
	// Methods
	void SetSize(sf::Vector2f size);
	void SetColour(sf::Color colour);

public:
	// Inherited via Renderable
	sf::Vector2f GetPosition() override;
	void SetPosition(sf::Vector2f position) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

