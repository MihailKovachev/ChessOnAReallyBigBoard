#pragma once
#include "Piece.h"

class Rose : public Piece
{
public:
	Rose(const sf::Sprite& Sprite, EPieceColor Color, Board& nBoard, uint8_t BoardX, uint8_t BoardY);
	Rose(const sf::Texture& Texture, EPieceColor Color, Board& nBoard, uint8_t BoardX, uint8_t BoardY);
	virtual bool Move(uint8_t NewX, uint8_t  NewY) override;

	//virtual bool IsBlockedOnDiagonal(int8_t DiagonalX, int8_t DiagonalY) override;
	//virtual bool IsBlockedOnFile(int8_t X) override;
	//virtual bool IsBlockedOnRow(int8_t Y) override;
};
