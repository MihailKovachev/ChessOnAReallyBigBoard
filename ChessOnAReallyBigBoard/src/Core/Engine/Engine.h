#pragma once

#include "Core/Singleton/Singleton.h"

class Engine
{
public:
	Engine();
	virtual ~Engine();

	// Run method, contains the game loop
	void Run();
	void Shutdown();
private:
	class Game* m_Game = nullptr;

	bool m_ShouldShutdown = false;
};

