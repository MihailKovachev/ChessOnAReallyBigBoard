#include "Pawn.h"

#include "Game/Board.h"

Pawn::Pawn(const sf::Sprite& Sprite, EPieceColor Color, Board& nBoard, uint8_t BoardX, uint8_t BoardY)
	: Piece(Sprite, Color, nBoard, BoardX, BoardY)
{
}

Pawn::Pawn(const sf::Texture& Texture, EPieceColor Color, Board& nBoard, uint8_t BoardX, uint8_t BoardY)
	: Piece(Texture, Color, nBoard, BoardX, BoardY)
{
}

bool Pawn::Move(uint8_t NewX, uint8_t  NewY)
{
	if (NewX == m_BoardX && NewY == m_BoardY && Board::IsWithinBoard(NewX, NewY)
		|| (m_Color == EPieceColor::White && NewY > m_BoardY)
		|| (m_Color == EPieceColor::Black && NewY < m_BoardY))
		return false;

	EPieceColor CapturedPieceColor;

	bool bCanCapture = false;

	if ((NewX == m_BoardX + 1 || NewX == m_BoardX - 1))
	{
		switch (m_Color)
		{
		case EPieceColor::White:
			bCanCapture = NewY == m_BoardY - 1
				&& m_Board.GetPieceColor(NewX, NewY, CapturedPieceColor) && CapturedPieceColor != m_Color;
			break;
		case EPieceColor::Black:
			bCanCapture = NewY == m_BoardY + 1
				&& m_Board.GetPieceColor(NewX, NewY, CapturedPieceColor) && CapturedPieceColor != m_Color;
			break;
		}
	}

	if (!bCanCapture)
	{
		switch (m_Color)
		{
		case EPieceColor::White:
			if (Board::IsWithinBoard(m_BoardX, m_BoardY - 1) && m_Board.HasPieceAt(m_BoardX, m_BoardY - 1)) return false;
			break;
		case EPieceColor::Black:
			if (Board::IsWithinBoard(m_BoardX, m_BoardY + 1) && m_Board.HasPieceAt(m_BoardX, m_BoardY + 1)) return false;
			break;
		}
	}

	switch (m_Color)
	{
	case EPieceColor::White:
		if (!bHasMoved)
		{
			if (std::abs(NewY - m_BoardY) <= 6 && NewY < m_BoardY &&
				(NewX == m_BoardX || bCanCapture))
			{
				m_BoardX = NewX;
				m_BoardY = NewY;
				bHasMoved = true;
				return true;
			}
		}
		else
		{
			if (NewY == m_BoardY - 1 &&
				(NewX == m_BoardX || bCanCapture))
			{
				m_BoardX = NewX;
				m_BoardY = NewY;
				return true;
			}
		}
		break;
	case EPieceColor::Black:
		if (!bHasMoved)
		{
			if (std::abs(NewY - m_BoardY) <= 6 && NewY > m_BoardY &&
				(NewX == m_BoardX ||
					bCanCapture))
			{
				m_BoardX = NewX;
				m_BoardY = NewY;
				bHasMoved = true;
				return true;
			}
		}
		else
		{
			if (NewY == m_BoardY + 1 &&
				(NewX == m_BoardX || bCanCapture))
			{
				m_BoardX = NewX;
				m_BoardY = NewY;
				return true;
			}
		}
		break;
	}

	SetReadyToMove(false);
	return false;
}
