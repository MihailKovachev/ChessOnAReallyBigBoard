#pragma once

#include <cstdint>

class GameObject
{
public:
	GameObject(uint8_t PosX, uint8_t PosY);

protected:
	uint8_t m_BoardX = 0;
	uint8_t m_BoardY = 0;
};