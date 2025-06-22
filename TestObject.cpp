#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Renderable.h"
#include "TestObject.h"

TestObject::TestObject(sf::Vector2f position, sf::Vector2f size)
{
    Position = position;
    Body.setSize(size); // Set test size
    Body.setFillColor(sf::Color::Blue);
    Body.setPosition(position);
}

sf::Vector2f TestObject::GetPosition()
{
    return Position;
}

void TestObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(Body, states);
}
