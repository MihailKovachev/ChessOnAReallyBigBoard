#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include <SFML/System/Vector2.hpp>

#include "Components/Component.h"
#include "Components/ComponentTypes.h"
#include <Game/Pieces/Color.h>

class GameObject
{
public:
	GameObject(uint8_t PosX, uint8_t PosY);

	sf::Vector2u GetPosition() const { return { m_BoardX, m_BoardY }; }
	void SetPosition(uint8_t X, uint8_t Y) { m_BoardX = X; m_BoardY = Y; }

	virtual EPieceColor GetColor() const { return m_Color; }

	virtual void AddComponent(const std::shared_ptr<Component>& Comp);
	virtual void RemoveComponent(uint32_t ID);
	virtual std::shared_ptr<Component> GetFirstComponentOfType(EComponentType Type);
protected:
	uint8_t m_BoardX = 0;
	uint8_t m_BoardY = 0;
	EPieceColor m_Color = EPieceColor::White;

	std::vector<std::shared_ptr<Component>> m_Components;
};