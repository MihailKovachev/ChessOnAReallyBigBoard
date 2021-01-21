#pragma once

#include <cstdint>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/VideoMode.hpp>


class Board
{
public:
	Board(const sf::Vector2u& Size);

	void Render(sf::RenderWindow& Window);
private:
	void GenerateBackground();
private:
	static constexpr uint16_t Width  = 16;
	static constexpr uint16_t Height = 16;

	static const sf::Color DarkSquareColor;
	static const sf::Color LightSquareColor;

	float SquareSize;

	sf::RenderTexture m_Background;
};

