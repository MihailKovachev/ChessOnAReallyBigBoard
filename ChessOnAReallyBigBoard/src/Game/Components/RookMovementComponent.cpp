#include "RookMovementComponent.h"

#include <Core/Engine/GameObject.h>
#include <Core/Engine/Engine.h>
#include <Game/Board.h>

bool RookMovementComponent::Execute(uint8_t NewX, uint8_t NewY)
{
	uint8_t StartX = m_Owner->GetPosition().x;
	uint8_t StartY = m_Owner->GetPosition().y;

	if ((NewX == StartX && NewY == StartY) || !Board::IsWithinBoard(NewX, NewY)
		|| (NewX != StartX && NewY != StartY))
		return false;

	int8_t DirectionX = Engine::SignOf(NewX - StartX);
	int8_t DirectionY = Engine::SignOf(NewY - StartY);

	EPieceColor PieceColor = m_Owner->GetColor();

	EPieceColor CapturedPieceColor;
	// Ensure we don't capture a piece of the same color
	if (Board::GetInstance().GetPieceColor(NewX, NewY, CapturedPieceColor) && CapturedPieceColor == PieceColor)
		return false;

	std::array<sf::Vector2u, 2> ObstructedSquares;

	if (NewY != StartY && IsBlockedOnFile(ObstructedSquares))
	{
		uint8_t DistanceToNewY = (uint8_t)std::abs(StartY - NewY);

		// We need to preserve direction information, which is why we need the sign of the value, too.
		int8_t DistanceToFirstObstructedSquare = ObstructedSquares[0].y - StartY;
		int8_t DistanceToSecondObstructedSquare = ObstructedSquares[1].y - StartY;

		EPieceColor FirstObstructingPieceColor;
		Board::GetInstance().GetPieceColor(ObstructedSquares[0].x, ObstructedSquares[0].y, FirstObstructingPieceColor);
		EPieceColor SecondObstructingPieceColor;
		Board::GetInstance().GetPieceColor(ObstructedSquares[1].x, ObstructedSquares[1].y, SecondObstructingPieceColor);


		if (DirectionY == Engine::SignOf(DistanceToFirstObstructedSquare))
		{
			if ((DistanceToNewY <= std::abs(DistanceToFirstObstructedSquare) && FirstObstructingPieceColor != PieceColor)
				|| (DistanceToNewY < std::abs(DistanceToFirstObstructedSquare) && FirstObstructingPieceColor == PieceColor))
			{
				m_Owner->SetPosition(StartX, NewY);
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (DirectionY == Engine::SignOf(DistanceToSecondObstructedSquare))
		{
			if ((DistanceToNewY <= std::abs(DistanceToSecondObstructedSquare) && SecondObstructingPieceColor != PieceColor)
				|| (DistanceToNewY < std::abs(DistanceToSecondObstructedSquare) && SecondObstructingPieceColor == PieceColor))
			{
				m_Owner->SetPosition(StartX, NewY);
				return true;
			}
			else
			{
				return false;
			}

		}
		else
		{
			m_Owner->SetPosition(StartX, NewY);
			return true;
		}
	}

	if (NewX != StartX && IsBlockedOnRow(ObstructedSquares))
	{
		uint8_t DistanceToNewX = (uint8_t)std::abs(StartX - NewX);

		// We need to preserve direction information, which is why we need the sign of the value, too.
		int8_t DistanceToFirstObstructedSquare = ObstructedSquares[0].x - StartX;
		int8_t DistanceToSecondObstructedSquare = ObstructedSquares[1].x - StartX;

		EPieceColor FirstObstructingPieceColor;
		Board::GetInstance().GetPieceColor(ObstructedSquares[0].x, ObstructedSquares[0].y, FirstObstructingPieceColor);
		EPieceColor SecondObstructingPieceColor;
		Board::GetInstance().GetPieceColor(ObstructedSquares[1].x, ObstructedSquares[1].y, SecondObstructingPieceColor);

		if (DirectionX == Engine::SignOf(DistanceToFirstObstructedSquare))
		{
			if ((DistanceToNewX <= std::abs(DistanceToFirstObstructedSquare) && FirstObstructingPieceColor != PieceColor)
				|| (DistanceToNewX < std::abs(DistanceToFirstObstructedSquare) && FirstObstructingPieceColor == PieceColor))
			{
				m_Owner->SetPosition(NewX, NewY);
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (DirectionX == Engine::SignOf(DistanceToSecondObstructedSquare))
		{
			if ((DistanceToNewX <= std::abs(DistanceToSecondObstructedSquare) && SecondObstructingPieceColor != PieceColor)
				|| (DistanceToNewX < std::abs(DistanceToSecondObstructedSquare) && SecondObstructingPieceColor == PieceColor))
			{
				m_Owner->SetPosition(NewX, NewY);
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	m_Owner->SetPosition(NewX, NewY);
	return true;
}

RookMovementComponent::RookMovementComponent(ComponentType Type, const std::shared_ptr<class GameObject>& Owner)
	: Component(Type, Owner)
{
}

bool RookMovementComponent::IsBlockedOnFile(std::array<sf::Vector2u, 2>& ObstructedSquares)
{
	ObstructedSquares.fill(sf::Vector2u());

	uint8_t BoardX = m_Owner->GetPosition().x;
	uint8_t BoardY = m_Owner->GetPosition().y;

	uint8_t NumberOfObstructedSquares = 0;

	for (int8_t y = BoardY - 1; y > 0; --y)
	{
		if (Board::GetInstance().HasPieceAt(BoardX, y))
		{
			ObstructedSquares[NumberOfObstructedSquares].x = BoardX;
			ObstructedSquares[NumberOfObstructedSquares].y = y;
			++NumberOfObstructedSquares;
			break;
		}
	}

	for (int8_t y = BoardY + 1; y < Board::GetHeight(); ++y)
	{
		if (Board::GetInstance().HasPieceAt(BoardX, y))
		{
			ObstructedSquares[NumberOfObstructedSquares].x = BoardX;
			ObstructedSquares[NumberOfObstructedSquares].y = y;
			++NumberOfObstructedSquares;
			break;
		}
	}

	return NumberOfObstructedSquares > 0;
}

bool RookMovementComponent::IsBlockedOnRow(std::array<sf::Vector2u, 2>& ObstructedSquares)
{
	ObstructedSquares.fill(sf::Vector2u());

	uint8_t NumberOfObstructedSquares = 0;

	uint8_t BoardX = m_Owner->GetPosition().x;
	uint8_t BoardY = m_Owner->GetPosition().y;

	for (int8_t x = BoardX - 1; x > 0; --x)
	{
		if (Board::GetInstance().HasPieceAt(x, BoardY))
		{
			ObstructedSquares[NumberOfObstructedSquares].x = x;
			ObstructedSquares[NumberOfObstructedSquares].y = BoardY;
			++NumberOfObstructedSquares;
			break;
		}
	}

	for (int8_t x = BoardX + 1; x < Board::GetWidth(); ++x)
	{
		if (Board::GetInstance().HasPieceAt(x, BoardY))
		{
			ObstructedSquares[NumberOfObstructedSquares].x = x;
			ObstructedSquares[NumberOfObstructedSquares].y = BoardY;
			++NumberOfObstructedSquares;
			break;
		}
	}

	return NumberOfObstructedSquares > 0;

}