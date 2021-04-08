#include "Piece.h"

#include <SFML/Graphics/Texture.hpp>

#include "Game/Board.h"

Piece::Piece(const sf::Sprite& Sprite, EPieceColor Color, Board& nBoard, uint8_t BoardX, uint8_t BoardY)
	: 
	m_Sprite(Sprite),
	m_Board(nBoard),
	GameObject(BoardX, BoardY)
{
	m_Color = Color;
}

Piece::Piece(const sf::Texture& Texture, EPieceColor Color, Board& nBoard, uint8_t BoardX, uint8_t BoardY)
	: 
	m_Sprite(Texture),
	m_Board(nBoard),
	GameObject(BoardX, BoardY)
{
	m_Color = Color;
}

bool Piece::Move(uint8_t NewX, uint8_t NewY)
{
	for (const auto& Comp : m_Components)
	{
		if (Comp->Execute(NewX, NewY))
			return true;
	}
	return false;
}

void Piece::Render(sf::RenderTarget& RenderTarget)
{
	float SpriteSize = m_Sprite.getScale().x * m_Sprite.getTexture()->getSize().x;
	m_Sprite.setPosition(sf::Vector2f(m_BoardX * SpriteSize, m_BoardY * SpriteSize));
	RenderTarget.draw(m_Sprite);
}

void Piece::ScaleSprite(const float Scale)
{
	m_Sprite.setScale(Scale, Scale);
}

bool Piece::IsBlockedOnDiagonal(int8_t DiagonalX, int8_t DiagonalY, std::array<sf::Vector2u, 2>& BlockingSquares)
{
	return false;
}

bool Piece::IsBlockedOnFile(std::array<sf::Vector2u, 2>& BlockingSquares)
{
	return false;
}

bool Piece::IsBlockedOnRow(std::array<sf::Vector2u, 2>& BlockingSquares)
{
	return false;
}
