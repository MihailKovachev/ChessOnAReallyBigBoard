#pragma once
#include "Piece.h"

class Champion : public Piece
{
public:
	Champion(const sf::Sprite& Sprite, EPieceColor Color, uint8_t BoardX, uint8_t BoardY);
	Champion(const sf::Texture& Texture, EPieceColor Color, uint8_t BoardX, uint8_t BoardY);
	virtual bool Move(uint8_t NewX, uint8_t  NewY) override;
};

