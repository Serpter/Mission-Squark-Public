#pragma once

class TestObject : public sf::RectangleShape, public Renderable
{
public:
	// Constructors and Destructors
	TestObject(sf::Vector2f position, sf::Vector2f size);
	~TestObject() = default;

private:
	// Members
	sf::RectangleShape Body;
	sf::Vector2f Position;

public: 
	// Inherited via Renderable
	sf::Vector2f GetPosition() override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
