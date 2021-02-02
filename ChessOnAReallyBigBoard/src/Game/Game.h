#pragma once

namespace sf
{
	class RenderWindow;
	class Event;
}

#include "Board.h"

class Game
{
public:
	Game(class Engine* NEngine, class sf::RenderWindow& Window);

	void Run();

	void OnWindowResized(const class sf::Event& Event);
	void OnMouseButtonClicked(const class sf::Event& Event);
private:
	void Update(float DeltaTime);
	void Render();
private:
	class Engine* m_Engine = nullptr;
	class sf::RenderWindow& m_Window;

	Board m_Board;
};

