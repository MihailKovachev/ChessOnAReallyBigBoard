#pragma once
#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn(const sf::Sprite& Sprite, EPieceColor Color, uint8_t BoardX, uint8_t BoardY);
	Pawn(const sf::Texture& Texture, EPieceColor Color, uint8_t BoardX, uint8_t BoardY);
	virtual void Move(const std::string& MoveNotation) override;
};

