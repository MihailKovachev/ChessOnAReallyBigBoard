#pragma once

#include <Core/Engine/Components/Component.h>

#include <array>
#include <SFML/System/Vector2.hpp>

class RookMovementComponent : public Component
{
public:
	RookMovementComponent(EComponentType Type, const std::shared_ptr<class GameObject>& Owner);
	virtual bool Execute(uint8_t NewX, uint8_t NewY) override;

private:
	bool IsBlockedOnFile(std::array<sf::Vector2u, 2>& BlockingSquares);
	bool IsBlockedOnRow(std::array<sf::Vector2u, 2>& BlockingSquares);
};