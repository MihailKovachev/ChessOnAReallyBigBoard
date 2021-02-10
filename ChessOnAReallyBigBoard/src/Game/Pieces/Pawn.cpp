#include "Pawn.h"

#include "Game/Board.h"
#include "Core/Engine/Engine.h"

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
	int8_t Direction = m_Color == EPieceColor::Black ? +1 : -1;
	if ((NewX == m_BoardX && NewY == m_BoardY) || !Board::IsWithinBoard(NewX, NewY)
		||
		Engine::SignOf(NewY - m_BoardY) != Engine::SignOf(Direction)
		)
	{
		SetReadyToMove(false);
		return false;
	}

	EPieceColor CapturedPieceColor;

	bool bCanCapture = false;

	if ((NewX == m_BoardX + 1 || NewX == m_BoardX - 1))
	{
		bCanCapture = NewY == m_BoardY + Direction
			&& m_Board.GetPieceColor(NewX, NewY, CapturedPieceColor) && CapturedPieceColor != m_Color;
		if (bCanCapture)
		{
			m_BoardX = NewX;
			m_BoardY = NewY;
			bHasMoved = true;
			SetReadyToMove(false);
			return true;
		}
	}

	std::array<sf::Vector2u, 2> BlockingSquares;
	bool bBlockedOnFile = IsBlockedOnFile(BlockingSquares);

	if (!bHasMoved && bBlockedOnFile && !bCanCapture)
	{
		uint8_t DistanceToNewY = std::abs(m_BoardY - NewY);

		if ((BlockingSquares[0].x == m_BoardX && std::abs((int)(BlockingSquares[0].y - m_BoardY)) < DistanceToNewY + 1)
			||
			(BlockingSquares[1].x == m_BoardX && std::abs((int)(BlockingSquares[1].y - m_BoardY)) < DistanceToNewY + 1))
		{
			SetReadyToMove(false);
			return false;
		}
		else
		{
			m_BoardY = NewY;
			bHasMoved = true;
			SetReadyToMove(false);
			return true;
		}
	}
	else if (bCanCapture)
	{
		m_BoardX = NewX;
		m_BoardY = NewY;
		bHasMoved = true;
		SetReadyToMove(false);
		return true;
	}
	else if (!bHasMoved && !bBlockedOnFile)
	{
		if (std::abs(NewY - m_BoardY) <= 6 &&
			NewX == m_BoardX)
		{
			m_BoardX = NewX;
			m_BoardY = NewY;
			bHasMoved = true;
			SetReadyToMove(false);
			return true;
		}
	}
	else if (bHasMoved && bBlockedOnFile)
	{
		if ((BlockingSquares[0].y == m_BoardY + Direction || BlockingSquares[1].y == m_BoardY + Direction))
		{
			SetReadyToMove(false);
			return false;
		}
		else if (NewY == m_BoardY + Direction &&
			NewX == m_BoardX)
		{
			m_BoardY = NewY;
			SetReadyToMove(false);
			return true;
		}
	}
	else if (bHasMoved && !bBlockedOnFile)
	{
		if (NewY == m_BoardY + Direction &&
			NewX == m_BoardX)
		{
			m_BoardY = NewY;
			SetReadyToMove(false);
			return true;
		}
	}

	SetReadyToMove(false);
	return false;
}

bool Pawn::IsBlockedOnDiagonal(int8_t DiagonalX, int8_t DiagonalY, std::array<sf::Vector2u, 2>& BlockingSquares)
{
	return false;
}

bool Pawn::IsBlockedOnFile(std::array<sf::Vector2u, 2>& BlockingSquares)
{
	//switch (m_Color)
	//{
	//case EPieceColor::White:
	//	if (Board::IsWithinBoard(m_BoardX, m_BoardY - 1) && m_Board.HasPieceAt(m_BoardX, m_BoardY - 1)) return true;
	//	break;
	//case EPieceColor::Black:
	//	if (Board::IsWithinBoard(m_BoardX, m_BoardY + 1) && m_Board.HasPieceAt(m_BoardX, m_BoardY + 1)) return true;
	//	break;
	//}

	int8_t Direction = m_Color == EPieceColor::Black ? +1 : -1;

	if (!bHasMoved)
	{
		uint8_t NumBlockingSquares = 0;
		
		for (uint8_t y = 1; y <= 6; ++y)
		{
			if (m_Board.HasPieceAt(m_BoardX, m_BoardY + Direction * y))
			{
				BlockingSquares[NumBlockingSquares++] = sf::Vector2u(m_BoardX, m_BoardY + Direction * y);
				if (NumBlockingSquares == 2)
					return true;
			}
		}

		if (NumBlockingSquares > 0)
		{
			return true;
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
