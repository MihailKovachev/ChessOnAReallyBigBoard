#pragma once

#include <array>
#include <Core/Engine/Components/Component.h>
#include <SFML/System/Vector2.hpp>

class BishopMovementComponent : public Component
{
public:
	BishopMovementComponent(ComponentType Type, const std::shared_ptr<class GameObject>& Owner);
	virtual bool Execute(uint8_t NewX, uint8_t  NewY) override;

private:
	bool IsBlockedOnDiagonal(int8_t DiagonalX, int8_t DiagonalY, std::array<sf::Vector2u, 2>& BlockingSquares);
};

