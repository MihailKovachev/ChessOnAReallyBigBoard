#include "Pawn.h"

Pawn::Pawn(const sf::Sprite& Sprite, EPieceColor Color, uint8_t BoardX, uint8_t BoardY)
	: Piece(Sprite, Color, BoardX, BoardY)
{
}

Pawn::Pawn(const sf::Texture& Texture, EPieceColor Color, uint8_t BoardX, uint8_t BoardY)
	: Piece(Texture, Color, BoardX, BoardY)
{
}

bool Pawn::Move(uint8_t NewX, uint8_t  NewY)
{
	if (NewX == m_BoardX && NewY == m_BoardY)
		return false;

	m_BoardX = NewX;
	m_BoardY = NewY;

	SetReadyToMove(false);
	return true;
}
