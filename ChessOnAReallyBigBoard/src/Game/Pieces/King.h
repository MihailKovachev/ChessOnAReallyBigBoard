#pragma once
#include "Piece.h"

class King : public Piece
{
public:
	King(const sf::Sprite& Sprite, EPieceColor Color, Board& nBoard, uint8_t BoardX, uint8_t BoardY);
	King(const sf::Texture& Texture, EPieceColor Color, Board& nBoard, uint8_t BoardX, uint8_t BoardY);
	virtual bool Move(uint8_t NewX, uint8_t  NewY) override;

	//virtual bool IsBlockedOnDiagonal(int8_t DiagonalX, int8_t DiagonalY) override;
	virtual bool IsBlockedOnFile(std::array<sf::Vector2u, 2>& BlockingSquares) override;
	virtual bool IsBlockedOnRow(std::array<sf::Vector2u, 2>& BlockingSquares) override;
};

