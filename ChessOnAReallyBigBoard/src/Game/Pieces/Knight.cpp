#include "Knight.h"
#include <Game/Board.h>

Knight::Knight(const sf::Sprite& Sprite, EPieceColor Color, Board& nBoard, uint8_t BoardX, uint8_t BoardY)
	: Piece(Sprite, Color, nBoard, BoardX, BoardY)
{
}

Knight::Knight(const sf::Texture& Texture, EPieceColor Color, Board& nBoard, uint8_t BoardX, uint8_t BoardY)
	: Piece(Texture, Color, nBoard, BoardX, BoardY)
{
}

bool Knight::Move(uint8_t NewX, uint8_t  NewY)
{
	if (!Board::IsWithinBoard(NewX, NewY) || NewX == m_BoardX || NewY == m_BoardY) return false;

	uint8_t DistanceToNewX = std::abs(NewX - m_BoardX);
	uint8_t DistanceToNewY = std::abs(NewY - m_BoardY);

	if ((DistanceToNewX == 2 && DistanceToNewY == 1) || (DistanceToNewY == 2 && DistanceToNewX == 1))
	{
		EPieceColor CapturedPieceColor;
		m_Board.GetPieceColor(NewX, NewY, CapturedPieceColor);
		if ((m_Board.GetPieceColor(NewX, NewY, CapturedPieceColor) && CapturedPieceColor != m_Color)
			|| !m_Board.HasPieceAt(NewX, NewY))
		{
			m_BoardX = NewX;
			m_BoardY = NewY;
			return true;
		}
	}

	return false;
}
