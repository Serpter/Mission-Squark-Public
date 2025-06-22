#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "Simulatable.h"
#include "Renderable.h"
#include "TextRecipe.h"

using namespace std;

TextRecipe::TextRecipe(TextFontTypes::FontForText font, sf::String string, int size, sf::Color colour, std::uint32_t style)
{
	sf::Font _baseFont;

	switch (font)
	{
	case TextFontTypes::Roboto:
		if (!_baseFont.openFromFile("Roboto.ttf"))
		{
			throw runtime_error("Failed to load font file path");
		}
		break;
	case TextFontTypes::Handjet:
		if (!_baseFont.openFromFile("Handjet.ttf"))
		{
			throw runtime_error("Failed to load font file path");
		}
		break;
	case TextFontTypes::Silkscreen:
		if (!_baseFont.openFromFile("Silkscreen.ttf"))
		{
			throw runtime_error("Failed to load font file path");
		}
		break;
	case TextFontTypes::Nabla:
		if (!_baseFont.openFromFile("Nabla.ttf"))
		{
			throw runtime_error("Failed to load font file path");
		}
		break;
	default:
		throw runtime_error("No font provided");
		break;
	}

	TextFont = _baseFont;
	TextString = string;
	TextSize = size;
	TextColour = colour;
	TextStyle = style;
	DrawPos = sf::Vector2f(0.0f, 0.0f);
	Origin = sf::Vector2f(0.0f, 0.0f);
}

void TextRecipe::SetPosition(sf::Vector2f position)
{
	DrawPos = position;
}

void TextRecipe::SetString(sf::String string)
{
	TextString = string;
}

void TextRecipe::SetSize(int size)
{
	TextSize = size;
}

void TextRecipe::SetOrigin(sf::Vector2f origin)
{
	Origin = origin;
}

sf::Vector2f TextRecipe::GetPosition()
{
	return sf::Vector2f();
}

void TextRecipe::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Text _drawnText(TextFont, TextString, TextSize);
	_drawnText.setPosition(DrawPos);
	_drawnText.setOrigin(sf::Vector2f(Origin.x, Origin.y + TextSize));
	_drawnText.setFillColor(TextColour);
	_drawnText.setStyle(TextStyle);
	target.draw(_drawnText, states);
}
