#pragma once

class BackgroundLayer : public Renderable
{
public:
	// Constructors and Destructors
	BackgroundLayer(std::filesystem::path texturePath);
	~BackgroundLayer() = default;

private:
	// Members
	sf::Texture SourceTexture;
	sf::Vector2f Position;
	sf::Vector2f ParallaxFactor;
	Renderable* ParallaxSource;
	sf::Color ColourTint;
	sf::Vector2f BackgroundOffset;

public:
	// Methods
	void SetTexture(std::filesystem::path texturePath);
	void SetParallaxFactor(sf::Vector2f strength);
	void SetParallaxSource(Renderable& object);
	void SetColourTint(sf::Color colour);
	void SetBackgroundOffset(sf::Vector2f offset);

public:
	// Type Methods
	sf::Texture GetTexture();
	sf::Vector2f GetBackgroundOffset();

public:
	// Inherited via Renderable
	sf::Vector2f GetPosition() override;
	void SetPosition(sf::Vector2f position) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
