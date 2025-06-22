#pragma once

class TextFont;

class TextFontTypes {
public:
	enum FontForText
	{
		Roboto,
		Handjet,
		Silkscreen,
		Nabla
	};
};

class TextRecipe : public Renderable
{
public: 
	// Constructors and Destructors
	TextRecipe(TextFontTypes::FontForText font, sf::String string, int size, sf::Color colour, std::uint32_t style);
	~TextRecipe() = default;

private: 
	// Members
	sf::Font TextFont;
	sf::String TextString;
	int TextSize;
	sf::Color TextColour;
	std::uint32_t TextStyle;
	sf::Vector2f DrawPos;
	sf::Vector2f Origin;

public: 
	// Methods
	void SetPosition(sf::Vector2f position);
	void SetString(sf::String string);
	void SetSize(int size);
	void SetOrigin(sf::Vector2f origin);

public: 
	// Inherited via Renderable
	sf::Vector2f GetPosition() override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
