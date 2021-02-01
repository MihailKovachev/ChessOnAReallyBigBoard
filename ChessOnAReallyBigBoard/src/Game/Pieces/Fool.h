#pragma once
#include "Piece.h"

class Fool : public Piece
{
public:
	Fool(const sf::Sprite& Sprite, EPieceColor Color, uint8_t BoardX, uint8_t BoardY);
	Fool(const sf::Texture& Texture, EPieceColor Color, uint8_t BoardX, uint8_t BoardY);
	virtual void Move(const std::string& MoveNotation) override;
};

