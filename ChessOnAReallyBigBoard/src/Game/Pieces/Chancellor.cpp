#include "Chancellor.h"
#include <Game/Board.h>
#include <Core/Engine/Engine.h>

Chancellor::Chancellor(const sf::Sprite& Sprite, EPieceColor Color, Board& nBoard, uint8_t BoardX, uint8_t BoardY)
	: Piece(Sprite, Color, nBoard, BoardX, BoardY)
{
}

Chancellor::Chancellor(const sf::Texture& Texture, EPieceColor Color, Board& nBoard, uint8_t BoardX, uint8_t BoardY)
	: Piece(Texture, Color, nBoard, BoardX, BoardY)
{
}

bool Chancellor::Move(uint8_t NewX, uint8_t  NewY)
{
	if (!Board::IsWithinBoard(NewX, NewY)
		|| (NewX == m_BoardX && NewY == m_BoardY))
		return false;

	int8_t DirectionX = Engine::SignOf(NewX - m_BoardX);
	int8_t DirectionY = Engine::SignOf(NewY - m_BoardY);

	uint8_t DistanceToNewX = std::abs(NewX - m_BoardX);
	uint8_t DistanceToNewY = std::abs(NewY - m_BoardY);

	bool bRookMove = (m_BoardX == NewX && m_BoardY != NewY) || (m_BoardY == NewY && m_BoardX != NewX);
	bool bKnightMove = (DistanceToNewX == 2 && DistanceToNewY == 1) || (DistanceToNewY == 2 && DistanceToNewX == 1);

	if (!bRookMove && !bKnightMove) return false;

	EPieceColor CapturedPieceColor;
	// Ensure we don't capture a piece of the same color
	if (m_Board.GetPieceColor(NewX, NewY, CapturedPieceColor) && CapturedPieceColor == m_Color)
		return false;

	std::array<sf::Vector2u, 2> ObstructedSquares;

	if (bRookMove && NewY != m_BoardY && IsBlockedOnFile(ObstructedSquares))
	{
		uint8_t DistanceToNewY = (uint8_t)std::abs(m_BoardY - NewY);

		// We need to perserve direction information, which is why we need the sign of the value, too.
		int8_t DistanceToFirstObstructedSquare = ObstructedSquares[0].y - m_BoardY;
		int8_t DistanceToSecondObstructedSquare = ObstructedSquares[1].y - m_BoardY;

		EPieceColor FirstObstructingPieceColor;
		m_Board.GetPieceColor(ObstructedSquares[0].x, ObstructedSquares[0].y, FirstObstructingPieceColor);
		EPieceColor SecondObstructingPieceColor;
		m_Board.GetPieceColor(ObstructedSquares[1].x, ObstructedSquares[1].y, SecondObstructingPieceColor);


		if (DirectionY == Engine::SignOf(DistanceToFirstObstructedSquare))
		{
			if ((DistanceToNewY <= std::abs(DistanceToFirstObstructedSquare) && FirstObstructingPieceColor != m_Color)
				|| (DistanceToNewY < std::abs(DistanceToFirstObstructedSquare) && FirstObstructingPieceColor == m_Color))
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
		else if (DirectionY == Engine::SignOf(DistanceToSecondObstructedSquare))
		{
			if ((DistanceToNewY <= std::abs(DistanceToSecondObstructedSquare) && SecondObstructingPieceColor != m_Color)
				|| (DistanceToNewY < std::abs(DistanceToSecondObstructedSquare) && SecondObstructingPieceColor == m_Color))
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
			m_BoardY = NewY;
			SetReadyToMove(false);
			return true;
		}
	}

	if (bRookMove && NewX != m_BoardX && IsBlockedOnRow(ObstructedSquares))
	{
		uint8_t DistanceToNewX = (uint8_t)std::abs(m_BoardX - NewX);

		// We need to perserve direction information, which is whx we need the sign of the value, too.
		int8_t DistanceToFirstObstructedSquare = ObstructedSquares[0].x - m_BoardX;
		int8_t DistanceToSecondObstructedSquare = ObstructedSquares[1].x - m_BoardX;

		EPieceColor FirstObstructingPieceColor;
		m_Board.GetPieceColor(ObstructedSquares[0].x, ObstructedSquares[0].y, FirstObstructingPieceColor);
		EPieceColor SecondObstructingPieceColor;
		m_Board.GetPieceColor(ObstructedSquares[1].x, ObstructedSquares[1].y, SecondObstructingPieceColor);

		if (DirectionX == Engine::SignOf(DistanceToFirstObstructedSquare))
		{
			if ((DistanceToNewX <= std::abs(DistanceToFirstObstructedSquare) && FirstObstructingPieceColor != m_Color)
				|| (DistanceToNewX < std::abs(DistanceToFirstObstructedSquare) && FirstObstructingPieceColor == m_Color))
			{
				m_BoardX = NewX;
				SetReadyToMove(false);
				return true;
			}
			else
			{
				SetReadyToMove(false);
				return false;
			}
		}
		else if (DirectionX == Engine::SignOf(DistanceToSecondObstructedSquare))
		{
			if ((DistanceToNewX <= std::abs(DistanceToSecondObstructedSquare) && SecondObstructingPieceColor != m_Color)
				|| (DistanceToNewX < std::abs(DistanceToSecondObstructedSquare) && SecondObstructingPieceColor == m_Color))
			{
				m_BoardX = NewX;
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
			SetReadyToMove(false);
			return false;
		}
	}

	m_BoardX = NewX;
	m_BoardY = NewY;
	SetReadyToMove(false);
	return true;
}

bool Chancellor::IsBlockedOnFile(std::array<sf::Vector2u, 2>& BlockingSquares)
{
	BlockingSquares.fill(sf::Vector2u());

	uint8_t NumberOfObstructedSquares = 0;

	for (int8_t y = m_BoardY - 1; y > 0; --y)
	{
		if (m_Board.HasPieceAt(m_BoardX, y))
		{
			BlockingSquares[NumberOfObstructedSquares].x = m_BoardX;
			BlockingSquares[NumberOfObstructedSquares].y = y;
			++NumberOfObstructedSquares;
			break;
		}
	}

	for (int8_t y = m_BoardY + 1; y < Board::GetHeight(); ++y)
	{
		if (m_Board.HasPieceAt(m_BoardX, y))
		{
			BlockingSquares[NumberOfObstructedSquares].x = m_BoardX;
			BlockingSquares[NumberOfObstructedSquares].y = y;
			++NumberOfObstructedSquares;
			break;
		}
	}

	return NumberOfObstructedSquares > 0;
}

bool Chancellor::IsBlockedOnRow(std::array<sf::Vector2u, 2>& BlockingSquares)
{
	BlockingSquares.fill(sf::Vector2u());

	uint8_t NumberOfObstructedSquares = 0;

	for (int8_t x = m_BoardX - 1; x > 0; --x)
	{
		if (m_Board.HasPieceAt(x, m_BoardY))
		{
			BlockingSquares[NumberOfObstructedSquares].x = x;
			BlockingSquares[NumberOfObstructedSquares].y = m_BoardY;
			++NumberOfObstructedSquares;
			break;
		}
	}

	for (int8_t x = m_BoardX + 1; x < Board::GetWidth(); ++x)
	{
		if (m_Board.HasPieceAt(x, m_BoardY))
		{
			BlockingSquares[NumberOfObstructedSquares].x = x;
			BlockingSquares[NumberOfObstructedSquares].y = m_BoardY;
			++NumberOfObstructedSquares;
			break;
		}
	}

	return NumberOfObstructedSquares > 0;
}
