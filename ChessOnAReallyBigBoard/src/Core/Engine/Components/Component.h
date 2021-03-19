#pragma once

#include <cstdint>
#include "ComponentTypes.h"

class Component
{
public:
	Component() = delete;
	Component(ComponentType Type, class GameObject* Owner);
	virtual void Execute() = 0;

protected:
	class GameObject* m_Owner = nullptr;
	uint32_t m_ID;
	const ComponentType m_Type;

private:
	static uint32_t s_ComponentCount;

};