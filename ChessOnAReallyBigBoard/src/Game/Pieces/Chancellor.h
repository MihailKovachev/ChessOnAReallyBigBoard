#pragma once
#include "Piece.h"

class Chancellor : public Piece
{
public:
	Chancellor(const sf::Sprite& Sprite, EPieceColor Color, uint8_t BoardX, uint8_t BoardY);
	Chancellor(const sf::Texture& Texture, EPieceColor Color, uint8_t BoardX, uint8_t BoardY);
	virtual void Move(const std::string& MoveNotation) override;
};

