#include "BishopMovementComponent.h"

#include <Core/Engine/Engine.h>
#include <Game/Board.h>

BishopMovementComponent::BishopMovementComponent(EComponentType Type, const std::shared_ptr<class GameObject>& Owner)
    : Component(Type, Owner)
{
}

bool BishopMovementComponent::Execute(uint8_t NewX, uint8_t NewY)
{
	uint8_t StartX = m_Owner->GetPosition().x;
	uint8_t StartY = m_Owner->GetPosition().y;

	if (!Board::IsWithinBoard(NewX, NewY)
		|| std::abs(NewX - StartX) != std::abs(NewY - StartY) || (NewX == StartX && NewY == StartY))
		return false;

	int8_t DiagonalX = Engine::SignOf(NewX - StartX);
	int8_t DiagonalY = Engine::SignOf(NewY - StartY);
	EPieceColor OwnerColor = m_Owner->GetColor();

	std::array<sf::Vector2u, 2> BlockingSquares;

	if (IsBlockedOnDiagonal(DiagonalX, DiagonalY, BlockingSquares))
	{
		uint8_t DistanceToNewSquare = std::abs(StartX - NewX);
		uint8_t DistanceToBlockingSquare = std::abs(StartX - (int8_t)BlockingSquares[0].x);

		EPieceColor BlockingPieceColor;
		Board::GetInstance().GetPieceColor(BlockingSquares[0].x, BlockingSquares[0].y, BlockingPieceColor);

		if (DistanceToNewSquare < DistanceToBlockingSquare
			|| (DistanceToNewSquare == DistanceToBlockingSquare && BlockingPieceColor != OwnerColor))
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
		m_Owner->SetPosition(NewX, NewY);
		return true;
	}

	return false;
}

bool BishopMovementComponent::IsBlockedOnDiagonal(int8_t DiagonalX, int8_t DiagonalY, std::array<sf::Vector2u, 2>& BlockingSquares)
{
	uint8_t StartX = m_Owner->GetPosition().x;
	uint8_t StartY = m_Owner->GetPosition().y;

	sf::Vector2i Position = { StartX + DiagonalX, StartY + DiagonalY };

	for (uint8_t k = 1; Board::IsWithinBoard(Position.x, Position.y); ++k)
	{
		if (Board::GetInstance().HasPieceAt(Position.x, Position.y))
		{
			BlockingSquares[0] = (sf::Vector2u)Position;
			return true;
		}
		Position = sf::Vector2i(StartX + DiagonalX * k, StartY + DiagonalY * k);
	}

	return false;
}
