#include "Pawn.h"

Pawn::Pawn(const sf::Sprite& Sprite, EPieceColor Color, uint8_t BoardX, uint8_t BoardY)
	: Piece(Sprite, Color, BoardX, BoardY)
{
}

Pawn::Pawn(const sf::Texture& Texture, EPieceColor Color, uint8_t BoardX, uint8_t BoardY)
	: Piece(Texture, Color, BoardX, BoardY)
{
}

void Pawn::Move(const std::string& MoveNotation)
{
}
