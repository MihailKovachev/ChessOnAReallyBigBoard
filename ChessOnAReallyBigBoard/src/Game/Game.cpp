#include "Game.h"

#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Core/Engine/Engine.h"

Game::Game(class Engine* NEngine, sf::RenderWindow& Window)
	:
	m_Engine(NEngine),
	m_Window(Window),
	m_Board(Window.getSize(), *m_Engine)
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

void Game::OnMouseButtonClicked(const sf::Event& Event)
{
	if (Event.mouseButton.button == sf::Mouse::Button::Left)
	{
		int32_t MouseX = Event.mouseButton.x;
		int32_t MouseY = Event.mouseButton.y;

		sf::Vector2u BoardPadding(m_Window.getSize() - m_Board.GetSize());

		uint32_t BoardX = static_cast<uint32_t>(MouseX / m_Board.GetSquareSize());
		uint32_t BoardY = static_cast<uint32_t>(MouseY / m_Board.GetSquareSize());

		m_Board.OnSquareSelected(BoardX, BoardY);
	}
}
