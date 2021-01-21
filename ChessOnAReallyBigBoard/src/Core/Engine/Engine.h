#pragma once

namespace sf
{
	class RenderWindow;
}

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
	class sf::RenderWindow* m_RenderWindow;

	bool m_ShouldShutdown = false;
};

