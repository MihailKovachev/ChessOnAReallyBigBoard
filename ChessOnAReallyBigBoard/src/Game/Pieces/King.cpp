#include "King.h"

King::King(const sf::Sprite& Sprite, EPieceColor Color, Board& nBoard, uint8_t BoardX, uint8_t BoardY)
	: Piece(Sprite, Color, nBoard, BoardX, BoardY)
{
}

King::King(const sf::Texture& Texture, EPieceColor Color, Board& nBoard, uint8_t BoardX, uint8_t BoardY)
	: Piece(Texture, Color, nBoard, BoardX, BoardY)
{
}

bool King::Move(uint8_t NewX, uint8_t  NewY)
{
	return false;
}

//bool King::IsBlockedOnDiagonal(int8_t DiagonalX, int8_t DiagonalY)
//{
//	return false;
//}

bool King::IsBlockedOnFile(std::array<sf::Vector2u, 2>& BlockingSquares)
{
	return false;
}

bool King::IsBlockedOnRow(std::array<sf::Vector2u, 2>& BlockingSquares)
{
	return false;
}
