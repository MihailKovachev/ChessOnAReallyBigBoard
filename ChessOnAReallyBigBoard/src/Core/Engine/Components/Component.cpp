#include "Component.h"

uint32_t Component::s_ComponentCount = 0;

Component::Component(ComponentType Type, class GameObject* Owner)
	: m_Type(Type), 
	m_Owner(Owner)
{
	m_ID = s_ComponentCount++;
}
