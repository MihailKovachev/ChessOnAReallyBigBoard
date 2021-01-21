#pragma once

namespace sf
{
	class RenderWindow;
}

#include "Board.h"

class Game
{
public:
	Game(class Engine* NEngine, class sf::RenderWindow& Window);

	void Run();

private:
	void Update(float DeltaTime);
	void Render();
private:
	class Engine* m_Engine = nullptr;
	class sf::RenderWindow& m_Window;

	Board m_Board;
};

