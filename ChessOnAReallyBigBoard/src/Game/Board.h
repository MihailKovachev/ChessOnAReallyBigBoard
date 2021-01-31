#pragma once

#include <cstdint>
#include <array>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "Pieces/Piece.h"

class Board
{
public:
	Board(const sf::Vector2u& Size, const class Engine& NEngine);

	void Render(sf::RenderWindow& Window);
	void Resize(const sf::Vector2u& Size);
private:
	void GenerateBackground(uint32_t SizeX, uint32_t SizeY);
	void SetupBoard();
private:
	struct Square
	{
		bool bHasPiece = false;
		Piece* m_Piece = nullptr;
	};

private:
	static constexpr uint8_t Width  = 16;
	static constexpr uint8_t Height = 16;

	static const sf::Color DarkSquareColor;
	static const sf::Color LightSquareColor;

	float SquareSize = 0.f;

	std::array<Square, Width * Height> m_BoardSquares;

	sf::RenderTexture m_BackgroundTexture;
	sf::Sprite m_BackgroundSprite;

	const class Engine& m_Engine;
};

