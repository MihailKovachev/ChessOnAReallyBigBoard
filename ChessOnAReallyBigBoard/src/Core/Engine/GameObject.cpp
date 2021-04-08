#include "GameObject.h"

GameObject::GameObject(uint8_t PosX, uint8_t PosY)
	:
	m_BoardX(PosX),
	m_BoardY(PosY)
{
}

void GameObject::AddComponent(const std::shared_ptr<Component>& Comp)
{
	m_Components.push_back(Comp);
}

void GameObject::RemoveComponent(uint32_t ID)
{
	for (int i = 0; i < m_Components.size(); ++i)
	{
		if (m_Components[i]->GetID() == ID)
		{
			m_Components.erase(m_Components.begin() + i);
		}
	}
}

std::shared_ptr<Component> GameObject::GetFirstComponentOfType(ComponentType Type)
{
	for (const auto& Comp : m_Components)
	{
		if (Comp->GetComponentType() == Type)
			return Comp;
	}
	return nullptr;
}
