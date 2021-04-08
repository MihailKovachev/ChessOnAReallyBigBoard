#pragma once

#include <cstdint>
#include <memory>

#include "ComponentTypes.h"

class Component
{
public:
	Component() = delete;
	Component(EComponentType Type, const std::shared_ptr<class GameObject>& Owner);
	virtual bool Execute(uint8_t NewX, uint8_t NewY) = 0;
	EComponentType GetComponentType() const { return m_Type; }
	uint32_t GetID() const { return m_ID; }

protected:
	std::shared_ptr<class GameObject> m_Owner = nullptr;
	uint32_t m_ID;
	const EComponentType m_Type;

private:
	static uint32_t s_ComponentCount;

};