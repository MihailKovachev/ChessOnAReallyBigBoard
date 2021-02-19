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
	int8_t Direction = m_Color == EPieceColor::Black ? +1 : -1;
	if ((NewX == m_BoardX && NewY == m_BoardY) || !Board::IsWithinBoard(NewX, NewY)
		||
		Engine::SignOf(NewY - m_BoardY) != Engine::SignOf(Direction)
		)
	{
		SetReadyToMove(false);
		return false;
	}

	std::array<sf::Vector2u, 2> BlockingSquares;

	EPieceColor CapturedPieceColor;
	bool bCanCapture = IsBlockedOnDiagonal(0, 0, BlockingSquares);
	if (bCanCapture &&
		((NewX == BlockingSquares[0].x && NewY == BlockingSquares[0].y)
			|| (NewX == BlockingSquares[1].x && NewY == BlockingSquares[1].y)) && 
		m_Board.GetPieceColor(NewX, NewY, CapturedPieceColor) && CapturedPieceColor != m_Color)
	{
		SetReadyToMove(false);
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
		SetReadyToMove(false);
		return true;
	}
	else if (!bBlockedOnFile)
	{
		if (bHasMoved)
		{
			if (NewY == m_BoardY + Direction && NewX == m_BoardX)
			{
				m_BoardY = NewY;
				SetReadyToMove(false);
				return true;
			}
			else
			{
				SetReadyToMove(false);
				return false;
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
	
	SetReadyToMove(false);
	return false;
}

bool Pawn::IsBlockedOnDiagonal(int8_t DiagonalX, int8_t DiagonalY, std::array<sf::Vector2u, 2>& BlockingSquares)
{
	uint8_t NumberOfBlockingPieces = 0;
	if(m_Board.HasPieceAt(m_BoardX + 1, m_BoardY + Direction))
	{
		BlockingSquares[0] = sf::Vector2u(m_BoardX + 1, m_BoardY + Direction);
		++NumberOfBlockingPieces;
	}
	if (m_Board.HasPieceAt(m_BoardX - 1, m_BoardY + Direction))
	{
		BlockingSquares[1] = sf::Vector2u(m_BoardX - 1, m_BoardY + Direction);
		++NumberOfBlockingPieces;
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
