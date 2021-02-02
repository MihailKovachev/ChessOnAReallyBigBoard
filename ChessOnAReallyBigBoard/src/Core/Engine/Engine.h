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

	class TextureManager& GetTextureManager() { return *m_TextureManager; }
	const class TextureManager& GetTextureManager() const { return *m_TextureManager; }
private:
	void PollEvents();
	void OnWindowResized(const class sf::Event& Event);
	void OnMouseButtonClicked(const class sf::Event& Event);
private:
	class Game* m_Game = nullptr;
	class sf::RenderWindow* m_RenderWindow = nullptr;
	class TextureManager* m_TextureManager = nullptr;

	bool m_ShouldShutdown = false;
};

