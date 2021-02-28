#include "King.h"

#include <Game/Board.h>

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
	uint8_t DistanceToNewX = std::abs(NewX - m_BoardX);
	uint8_t DistanceToNewY = std::abs(NewY - m_BoardY);
	if (!Board::IsWithinBoard(NewX, NewY) 
		|| (DistanceToNewX == DistanceToNewY && DistanceToNewX != 1)
		|| (DistanceToNewX != DistanceToNewY && (DistanceToNewX > 1 || DistanceToNewY > 1))
		) return false;

	EPieceColor CapturedPieceColor;
	if (m_Board.HasPieceAt(NewX, NewY) && m_Board.GetPieceColor(NewX, NewY, CapturedPieceColor) && CapturedPieceColor != m_Color)
	{
		m_BoardX = NewX;
		m_BoardY = NewY;
		bHasMoved = true;
		return true;
	}
	else if (!m_Board.HasPieceAt(NewX, NewY))
	{
		m_BoardX = NewX;
		m_BoardY = NewY;
		bHasMoved = true;
		return true;
	}

	return false;
}

