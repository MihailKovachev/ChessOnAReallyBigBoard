#pragma once

namespace sf
{
	class RenderWindow;
	class Event;
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
	void PollEvents();

	void OnWindowResized(const class sf::Event& Event);

private:
	class Game* m_Game = nullptr;
	class sf::RenderWindow* m_RenderWindow;

	bool m_ShouldShutdown = false;
};

