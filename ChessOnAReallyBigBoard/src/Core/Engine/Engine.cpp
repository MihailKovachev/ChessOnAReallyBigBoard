#include "Engine.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Game/Game.h"

Engine::Engine()
{
	m_RenderWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "Chess On A Really Big Board");

	m_Game = new Game(this, *m_RenderWindow);
}

Engine::~Engine()
{
	delete m_Game;
	delete m_RenderWindow;
}

void Engine::Run()
{
	while (!m_ShouldShutdown)
	{
		sf::Event e;
		while (m_RenderWindow->pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				Shutdown();
			}
		}
		m_Game->Run();
	}
}

void Engine::Shutdown()
{
	m_ShouldShutdown = true;
}
