#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Tile.h"

Tile::Tile()
{
    TileSize = sf::Vector2f(0.0f, 0.0f);
    Body = sf::RectangleShape(TileSize);
}

sf::Vector2f Tile::GetPosition()
{
    return Body.getPosition();
}

void Tile::SetPosition(sf::Vector2f position)
{
    Body.setPosition(position);
}

void Tile::SetSize(sf::Vector2f size)
{
    TileSize = size;
    Body.setSize(TileSize);
}

void Tile::SetColour(sf::Color colour)
{
    Body.setFillColor(colour);
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}
