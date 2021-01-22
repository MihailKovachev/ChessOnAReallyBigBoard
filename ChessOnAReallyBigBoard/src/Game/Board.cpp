#include "Board.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

const sf::Color Board::DarkSquareColor = { 84, 48, 7 };
const sf::Color Board::LightSquareColor = { 219, 210, 180 };

Board::Board(const sf::Vector2u& Size)
{
	Resize(Size);
	GenerateBackground();
}

void Board::Render(sf::RenderWindow& Window)
{
	sf::Sprite BackgroundSprite;
	BackgroundSprite.setTexture(m_Background.getTexture());
	Window.draw(BackgroundSprite);
}

void Board::Resize(const sf::Vector2u& Size)
{
	SquareSize = Size.x < Size.y ? Size.x / Width : Size.y / Height;
	m_Background.create(Width * (unsigned int)SquareSize, Height * (unsigned int)SquareSize);
	GenerateBackground();
}

void Board::GenerateBackground()
{

	sf::RectangleShape Square;
	Square.setSize(sf::Vector2f(SquareSize, SquareSize));
	
	m_Background.clear();
	for (int x = 0; x < Width; ++x)
	{
		for (int y = 0; y < Height; ++y)
		{
			Square.setPosition(x * SquareSize, y * SquareSize);
			if ((x % 2 == 0 && y % 2 == 0) || (x % 2 != 0 && y % 2 != 0))
			{
				Square.setFillColor(LightSquareColor);
			}
			else
			{
				Square.setFillColor(DarkSquareColor);
			}
			
			m_Background.draw(Square);
		}
	}

	m_Background.display();
}
