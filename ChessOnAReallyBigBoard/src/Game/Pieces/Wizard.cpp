#include "Wizard.h"

Wizard::Wizard(const sf::Sprite& Sprite, EPieceColor Color, uint8_t BoardX, uint8_t BoardY)
	: Piece(Sprite, Color, BoardX, BoardY)
{
}

Wizard::Wizard(const sf::Texture& Texture, EPieceColor Color, uint8_t BoardX, uint8_t BoardY)
	: Piece(Texture, Color, BoardX, BoardY)
{
}

bool Wizard::Move(uint8_t NewX, uint8_t  NewY)
{
	return false;
}