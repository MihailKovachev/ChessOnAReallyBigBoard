#include "Queen.h"

Queen::Queen(const sf::Sprite& Sprite, EPieceColor Color, Board& nBoard, uint8_t BoardX, uint8_t BoardY)
	: Piece(Sprite, Color, nBoard, BoardX, BoardY)
{
}

Queen::Queen(const sf::Texture& Texture, EPieceColor Color, Board& nBoard, uint8_t BoardX, uint8_t BoardY)
	: Piece(Texture, Color, nBoard, BoardX, BoardY)
{
}

bool Queen::Move(uint8_t NewX, uint8_t  NewY)
{
	return false;
}

//bool Queen::IsBlockedOnDiagonal(int8_t DiagonalX, int8_t DiagonalY)
//{
//	return false;
//}

bool Queen::IsBlockedOnFile(std::array<sf::Vector2u, 2>& BlockingSquares)
{
	return false;
}

bool Queen::IsBlockedOnRow(std::array<sf::Vector2u, 2>& BlockingSquares)
{
	return false;
}
