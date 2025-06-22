#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/View.hpp>
#include <cmath>
#include "Player.h"
#include "Camera.h"

void Camera::SetTarget(Player* target)
{
	View.setCenter(target->GetPosition());
}

void Camera::Move(sf::Vector2f direction)
{
	View.move(direction);
}

void Camera::SetZoom(float zoom)
{
	View.setSize(sf::Vector2f(BaseZoom + (zoom * ZoomScale), BaseZoom + (zoom * ZoomScale)));
}

sf::View& Camera::GetView()
{
	return View;
}