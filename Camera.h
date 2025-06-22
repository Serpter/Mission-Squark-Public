#pragma once

class Player;
namespace sf {
	class Shape;
	class View;
}

/// <summary>
/// Adds behaviour on top of View to create a camera to capture visual information
/// </summary>
class Camera
{
public:
	// Constructors and Destructors
	Camera() = default;
	~Camera() = default;

public:
	// Members
	sf::View View;

private:
	// Private Members
	float BaseZoom = 500.0f;
	float ZoomScale = 400.0f;

public:
	// Methods
	void SetTarget(Player* target);
	void Move(sf::Vector2f direction);
	void SetZoom(float zoom);

public:
	// Type Methods
	sf::View& GetView();
};
