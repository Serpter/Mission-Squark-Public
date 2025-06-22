#pragma once

namespace sf {
	class RenderWindow;
}
class Renderable;

/// <summary>
/// Adds behaviour on top of RenderWindow to draw graphics to the screen
/// </summary>
class Renderer
{
public:
	// Constructors and Destructors
	Renderer() = default;
	~Renderer() = default;

private:
	// Members
	std::vector<Renderable*> RenderQueue;

public:
	// Methods
	void AddRenderable(Renderable* renderable);
	void RemoveRenderable(int shapeIndex);
	void DrawDrawables(sf::RenderWindow * window);

public:
	// Type Methods
	int FindRenderable(Renderable& shape);
	std::vector<Renderable*>* GetRenderables();
};
