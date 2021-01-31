#pragma once

#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

enum class EPieceColor
{
	Black,
	White
};

class Piece
{
public:
	Piece(const sf::Sprite& Sprite, EPieceColor Color, uint8_t BoardX, uint8_t BoardY);
	Piece(const sf::Texture& Texture, EPieceColor Color, uint8_t BoardX, uint8_t BoardY);

	EPieceColor GetColor() const { return m_Color; }

	virtual void Move(const std::string& MoveNotation) = 0;
	void Render(sf::RenderTarget& RenderTarget);
	void ScaleSprite(const float Scale);
protected:
	sf::Sprite m_Sprite;
	EPieceColor m_Color = EPieceColor::White;
	/*
	* Coordinates from the bottom left corner viewed from white's perspective (square A1)
	*/
	uint8_t m_BoardX = 0;
	uint8_t m_BoardY = 0;
};