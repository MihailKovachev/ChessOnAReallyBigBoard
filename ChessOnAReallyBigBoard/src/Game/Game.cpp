#include "Game.h"

#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Core/Engine/Engine.h"

Game::Game(class Engine* NEngine, sf::RenderWindow& Window)
	:
	m_Engine(NEngine),
	m_Window(Window),
	m_Board(Window.getSize())
{
}

void Game::Run()
{
	float DeltaTime = 0.f;
	Update(DeltaTime);
	Render();
}

void Game::Update(float DeltaTime)
{
	
}

void Game::Render()
{
	m_Window.clear();
	m_Board.Render(m_Window);
	m_Window.display();
}

void Game::OnWindowResized(const sf::Event& Event)
{
	m_Board.Resize(sf::Vector2u(Event.size.width, Event.size.height));
}