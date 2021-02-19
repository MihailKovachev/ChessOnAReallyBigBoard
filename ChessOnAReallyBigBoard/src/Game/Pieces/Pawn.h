#pragma once
#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn(const sf::Sprite& Sprite, EPieceColor Color, Board& nBoard, uint8_t BoardX, uint8_t BoardY);
	Pawn(const sf::Texture& Texture, EPieceColor Color, Board& nBoard, uint8_t BoardX, uint8_t BoardY);
	virtual bool Move(uint8_t NewX, uint8_t  NewY) override;

	// Diagonal coordinates are ignored for pawns, so they can just be set to 0
	virtual bool IsBlockedOnDiagonal(int8_t DiagonalX, int8_t DiagonalY, std::array<sf::Vector2u, 2>& BlockingSquares) override;
	virtual bool IsBlockedOnFile(std::array<sf::Vector2u, 2>& BlockingSquares) override;

private:
	// Shows the direction in which the pawn can move. Black pawns move down, so their y increases. They have a positive direction;
	// White pawns move up, so their y decreases. They have a negative direction.
	int8_t Direction = 0;

	bool bHasMoved = false;
};

