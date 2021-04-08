#pragma once

#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <Core/Engine/GameObject.h>

class Piece : public GameObject
{
public:
	Piece(const sf::Sprite& Sprite, EPieceColor Color, class Board& nBoard, uint8_t BoardX, uint8_t BoardY);
	Piece(const sf::Texture& Texture, EPieceColor Color, class Board& nBoard ,uint8_t BoardX, uint8_t BoardY);

	const class Board& GetBoard() const { return m_Board; }

	virtual bool Move(uint8_t NewX, uint8_t NewY);
	void Render(sf::RenderTarget& RenderTarget);
	void ScaleSprite(const float Scale);

	bool IsReadyToMove() const { return bReadyToMove; }
	void SetReadyToMove(bool bReady) { bReadyToMove = bReady; }

protected:
	/** The sign represents the direction of the coordinate relative to the piece.
	* -x +y left up diagonal
	* +x +y right up diagonal
	* +x -y right down diagonal
	* -x -y left down diagonal

	
	*/
	virtual bool IsBlockedOnDiagonal(int8_t DiagonalX, int8_t DiagonalY, std::array<sf::Vector2u, 2>& BlockingSquares);
	virtual bool IsBlockedOnFile(std::array<sf::Vector2u, 2>& BlockingSquares);
	virtual bool IsBlockedOnRow(std::array<sf::Vector2u, 2>& BlockingSquares);
protected:
	sf::Sprite m_Sprite;
	/*
	* Coordinates from the top left corner viewed from white's perspective
	*/
	class Board& m_Board;

	bool bReadyToMove = false;
};