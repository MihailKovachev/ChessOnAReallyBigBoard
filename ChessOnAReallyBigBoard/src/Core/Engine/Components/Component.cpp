#include "Component.h"

uint32_t Component::s_ComponentCount = 0;

Component::Component(EComponentType Type, const std::shared_ptr<class GameObject>& Owner)
	: m_Type(Type), 
	m_Owner(Owner)
{
	m_ID = s_ComponentCount++;
}

bool Component::Execute(uint8_t NewX, uint8_t NewY)
{
	return false;
}
