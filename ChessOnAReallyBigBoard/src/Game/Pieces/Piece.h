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
	Piece(const sf::Sprite& Sprite, EPieceColor Color, class Board& nBoard, uint8_t BoardX, uint8_t BoardY);
	Piece(const sf::Texture& Texture, EPieceColor Color, class Board& nBoard ,uint8_t BoardX, uint8_t BoardY);

	EPieceColor GetColor() const { return m_Color; }

	virtual bool Move(uint8_t NewX, uint8_t NewY) = 0;
	void Render(sf::RenderTarget& RenderTarget);
	void ScaleSprite(const float Scale);

	bool IsReadyToMove() const { return bReadyToMove; }
	void SetReadyToMove(bool bReady) { bReadyToMove = bReady; }

protected:

protected:
	sf::Sprite m_Sprite;
	EPieceColor m_Color = EPieceColor::White;
	/*
	* Coordinates from the top left corner viewed from white's perspective
	*/
	uint8_t m_BoardX = 0;
	uint8_t m_BoardY = 0;
	class Board& m_Board;

	bool bReadyToMove = false;
};