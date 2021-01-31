#include "Piece.h"

#include <SFML/Graphics/Texture.hpp>

Piece::Piece(const sf::Sprite& Sprite, EPieceColor Color, uint8_t BoardX, uint8_t BoardY)
	: 
	m_Sprite(Sprite),
	m_Color(Color),
	m_BoardX(BoardX),
	m_BoardY(BoardY)
{
}

Piece::Piece(const sf::Texture& Texture, EPieceColor Color, uint8_t BoardX, uint8_t BoardY)
	: 
	m_Sprite(Texture),
	m_Color(Color),
	m_BoardX(BoardX),
	m_BoardY(BoardY)
{
	
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
