#include "Fool.h"

Fool::Fool(const sf::Sprite& Sprite, EPieceColor Color, uint8_t BoardX, uint8_t BoardY)
	: Piece(Sprite, Color, BoardX, BoardY)
{
}

Fool::Fool(const sf::Texture& Texture, EPieceColor Color, uint8_t BoardX, uint8_t BoardY)
	: Piece(Texture, Color, BoardX, BoardY)
{
}

bool Fool::Move(uint8_t NewX, uint8_t  NewY)
{
	return false;
}