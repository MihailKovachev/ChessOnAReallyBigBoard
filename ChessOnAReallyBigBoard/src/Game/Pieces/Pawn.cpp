#include "Pawn.h"

#include "Game/Board.h"
#include "Core/Engine/Engine.h"

Pawn::Pawn(const sf::Sprite& Sprite, EPieceColor Color, Board& nBoard, uint8_t BoardX, uint8_t BoardY)
	: Piece(Sprite, Color, nBoard, BoardX, BoardY)
{
	Direction = m_Color == EPieceColor::Black ? +1 : -1;
}

Pawn::Pawn(const sf::Texture& Texture, EPieceColor Color, Board& nBoard, uint8_t BoardX, uint8_t BoardY)
	: Piece(Texture, Color, nBoard, BoardX, BoardY)
{
	Direction = m_Color == EPieceColor::Black ? +1 : -1;
}

bool Pawn::Move(uint8_t NewX, uint8_t  NewY)
{
	if ((NewX == m_BoardX && NewY == m_BoardY) || !Board::IsWithinBoard(NewX, NewY)
		||
		Engine::SignOf(NewY - m_BoardY) != Direction)
		return false;

	std::array<sf::Vector2u, 2> BlockingSquares;

	EPieceColor CapturedPieceColor;
	bool bCanCapture = IsBlockedOnDiagonal(0, 0, BlockingSquares);
	if (bCanCapture &&
		((NewX == BlockingSquares[0].x && NewY == BlockingSquares[0].y)
			|| (NewX == BlockingSquares[1].x && NewY == BlockingSquares[1].y)) && 
		m_Board.GetPieceColor(NewX, NewY, CapturedPieceColor) && CapturedPieceColor != m_Color)
	{
		m_BoardX = NewX;
		m_BoardY = NewY;
		bHasMoved = true;
		return true;
	}
	
	bool bBlockedOnFile = IsBlockedOnFile(BlockingSquares);

	uint8_t DistanceToNewY = (uint8_t)std::abs(m_BoardY - NewY);
	uint8_t DistanceToBlockingPiece = (uint8_t)std::abs(m_BoardY - (uint8_t)BlockingSquares[0].y);
	if (bBlockedOnFile && DistanceToNewY < DistanceToBlockingPiece)
	{
		m_BoardX = NewX;
		m_BoardY = NewY;
		bHasMoved = true;
		return true;
	}
	else if (!bBlockedOnFile)
	{
		if (bHasMoved)
		{
			if (NewY == m_BoardY + Direction && NewX == m_BoardX)
			{
				m_BoardY = NewY;
				return true;
			}
		}
		else
		{
			if (NewX == m_BoardX && DistanceToNewY < 7)
			{
				m_BoardY = NewY;
				bHasMoved = true;
				return true;
			}
		}
	}
	
	return false;
}

bool Pawn::IsBlockedOnDiagonal(int8_t DiagonalX, int8_t DiagonalY, std::array<sf::Vector2u, 2>& BlockingSquares)
{
	uint8_t NumberOfBlockingPieces = 0;
	if(Board::IsWithinBoard(m_BoardX + 1, m_BoardY + Direction) && m_Board.HasPieceAt(m_BoardX + 1, m_BoardY + Direction))
	{
		BlockingSquares[NumberOfBlockingPieces++] = sf::Vector2u(m_BoardX + 1, m_BoardY + Direction);
		
	}
	if (Board::IsWithinBoard(m_BoardX - 1, m_BoardY + Direction) && m_Board.HasPieceAt(m_BoardX - 1, m_BoardY + Direction))
	{
		BlockingSquares[NumberOfBlockingPieces++] = sf::Vector2u(m_BoardX - 1, m_BoardY + Direction);
	}
	return NumberOfBlockingPieces > 0;
}

bool Pawn::IsBlockedOnFile(std::array<sf::Vector2u, 2>& BlockingSquares)
{
	if (!bHasMoved)
	{
		for (uint8_t y = 1; y <= 6; ++y)
		{
			if (m_Board.HasPieceAt(m_BoardX, m_BoardY + Direction * y))
			{
				BlockingSquares[0] = sf::Vector2u(m_BoardX, m_BoardY + Direction * y);
				return true;
			}
		}
	}
	else
	{
		if (m_Board.HasPieceAt(m_BoardX, m_BoardY + Direction))
		{
			BlockingSquares[0] = sf::Vector2u(m_BoardX, m_BoardY + Direction);
			return true;
		}
	}
	return false;
}
