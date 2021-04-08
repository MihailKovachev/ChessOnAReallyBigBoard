#pragma once

#include <Core/Engine/Components/Component.h>

class KnightMovementComponent : public Component
{
public:
	KnightMovementComponent(EComponentType Type, const std::shared_ptr<class GameObject>& Owner);
	virtual bool Execute(uint8_t NewX, uint8_t NewY) override;

};