#include "KnightMovementComponent.h"

#include <Game/Board.h>

KnightMovementComponent::KnightMovementComponent(EComponentType Type, const std::shared_ptr<class GameObject>& Owner)
	: Component(Type, Owner)
{
}

bool KnightMovementComponent::Execute(uint8_t NewX, uint8_t NewY)
{
	uint8_t StartX = m_Owner->GetPosition().x;
	uint8_t StartY = m_Owner->GetPosition().y;

	if (!Board::IsWithinBoard(NewX, NewY) || NewX == StartX || NewY == StartY) return false;

	EPieceColor OwnerColor = m_Owner->GetColor();
	uint8_t DistanceToNewX = std::abs(NewX - StartX);
	uint8_t DistanceToNewY = std::abs(NewY - StartY);

	if ((DistanceToNewX == 2 && DistanceToNewY == 1) || (DistanceToNewY == 2 && DistanceToNewX == 1))
	{
		EPieceColor CapturedPieceColor;
		if ((Board::GetInstance().GetPieceColor(NewX, NewY, CapturedPieceColor) && CapturedPieceColor != OwnerColor)
			|| !Board::GetInstance().HasPieceAt(NewX, NewY))
		{
			m_Owner->SetPosition(NewX, NewY);
			return true;
		}
	}

	return false;
}
