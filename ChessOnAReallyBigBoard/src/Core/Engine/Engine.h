#pragma once

#include <type_traits>

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

	template <typename T> 
	static int SignOf(T val) {
		return (T(0) < val) - (val < T(0));
	}

	template<typename T, typename U>
	static constexpr bool AreTypesEqual() { return IsSame<T, U>::value; }

	class TextureManager& GetTextureManager() { return *m_TextureManager; }
	const class TextureManager& GetTextureManager() const { return *m_TextureManager; }
private:
	void PollEvents();
	void OnWindowResized(const class sf::Event& Event);
	void OnMouseButtonClicked(const class sf::Event& Event);

private:
	template<typename T, typename U>
	struct IsSame : std::false_type { };

	template<typename T>
	struct IsSame<T, T> : std::true_type { };

private:
	class Game* m_Game = nullptr;
	class sf::RenderWindow* m_RenderWindow = nullptr;
	class TextureManager* m_TextureManager = nullptr;

	bool m_ShouldShutdown = false;
};

