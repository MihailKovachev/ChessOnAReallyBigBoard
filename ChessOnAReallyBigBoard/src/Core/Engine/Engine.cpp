#include "Engine.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Game/Game.h"
#include "TextureManager.h"

Engine::Engine()
{
	m_RenderWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "Chess On A Really Big Board");
	m_TextureManager = new TextureManager("resources/");
	m_Game = new Game(this, *m_RenderWindow);
}

Engine::~Engine()
{
	delete m_Game;
	delete m_TextureManager;
	delete m_RenderWindow;
}

void Engine::Run()
{
	while (!m_ShouldShutdown)
	{
		PollEvents();
		m_Game->Run();
	}
}

void Engine::Shutdown()
{
	m_ShouldShutdown = true;
}

void Engine::PollEvents()
{
	sf::Event Event;
	while (m_RenderWindow->pollEvent(Event))
	{
		switch (Event.type)
		{
		case sf::Event::Closed:
			Shutdown();
			break;
		case sf::Event::Resized:
			OnWindowResized(Event);
			break;
		case sf::Event::MouseButtonPressed:
			OnMouseButtonClicked(Event);
			break;
		}
	}
}

void Engine::OnWindowResized(const sf::Event& Event)
{
	m_RenderWindow->setView(sf::View(sf::FloatRect(0.f, 0.f, Event.size.width, Event.size.height)));
	m_Game->OnWindowResized(Event);
}

void Engine::OnMouseButtonClicked(const sf::Event& Event)
{
	m_Game->OnMouseButtonClicked(Event);
}
