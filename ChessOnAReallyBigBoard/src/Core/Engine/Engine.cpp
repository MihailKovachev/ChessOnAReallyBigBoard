#include "Engine.h"

#include <iostream>

Engine::Engine()
{
}

Engine::~Engine()
{
	// delete m_Game;
}

void Engine::Run()
{
	int32_t i = 0;
	while (!m_ShouldShutdown && i < 5)
	{
		++i;
		std::cout << "Work..." << std::endl;
	}
}

void Engine::Shutdown()
{
	m_ShouldShutdown = true;
}
