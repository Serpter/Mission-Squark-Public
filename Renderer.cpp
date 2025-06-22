#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "Camera.h"
#include "Renderable.h"
#include "Renderer.h"

void Renderer::AddRenderable(Renderable* renderable)
{
	RenderQueue.push_back(renderable);
}

void Renderer::RemoveRenderable(int shapeIndex)
{
	RenderQueue.erase(RenderQueue.begin() + shapeIndex);
}

int Renderer::FindRenderable(Renderable& shape)
{
	for (int _i = 0; _i < RenderQueue.size(); _i++)
	{
		if (RenderQueue[_i] == &shape)
		{
			return _i;
		}
	}
	return -1;
}

std::vector<Renderable*>* Renderer::GetRenderables()
{
	return &RenderQueue;
}

void Renderer::DrawDrawables(sf::RenderWindow* window)
{
	std::vector<Renderable*> _renderables = *GetRenderables();

	for (Renderable* _renderable : _renderables)
	{
		sf::Vector2f _position = _renderable->GetPosition();

		window->draw(*_renderable);
	}
}
