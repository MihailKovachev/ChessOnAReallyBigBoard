#include "Bishop.h"

#include <Core/Engine/Engine.h>
#include "Game/Board.h"

Bishop::Bishop(const sf::Sprite& Sprite, EPieceColor Color, Board& nBoard, uint8_t BoardX, uint8_t BoardY)
	: Piece(Sprite, Color, nBoard, BoardX, BoardY)
{
}

Bishop::Bishop(const sf::Texture& Texture, EPieceColor Color, Board& nBoard, uint8_t BoardX, uint8_t BoardY)
	: Piece(Texture, Color, nBoard, BoardX, BoardY)
{
}

bool Bishop::Move(uint8_t NewX, uint8_t  NewY)
{
	if (!Board::IsWithinBoard(NewX, NewY) 
		|| std::abs(NewX - m_BoardX) != std::abs(NewY - m_BoardY) || (NewX == m_BoardX && NewY == m_BoardY))
		return false;

	int8_t DiagonalX = Engine::SignOf(NewX - m_BoardX);
	int8_t DiagonalY = Engine::SignOf(NewY - m_BoardY);

	std::array<sf::Vector2u, 2> BlockingSquares;

	if (IsBlockedOnDiagonal(DiagonalX, DiagonalY, BlockingSquares))
	{
		uint8_t DistanceToNewSquare = std::abs(m_BoardX - NewX);
		uint8_t DistanceToBlockingSquare = std::abs(m_BoardX - (int8_t)BlockingSquares[0].x);

		EPieceColor BlockingPieceColor;
		m_Board.GetPieceColor(BlockingSquares[0].x, BlockingSquares[0].y, BlockingPieceColor);

		if (DistanceToNewSquare < DistanceToBlockingSquare 
			|| (DistanceToNewSquare == DistanceToBlockingSquare && BlockingPieceColor != m_Color) )
		{
			m_BoardX = NewX;
			m_BoardY = NewY;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		m_BoardX = NewX;
		m_BoardY = NewY;
		return true;
	}

	return false;
}

bool Bishop::IsBlockedOnDiagonal(int8_t DiagonalX, int8_t DiagonalY, std::array<sf::Vector2u, 2>& BlockingSquares)
{
	sf::Vector2i Position = { m_BoardX + DiagonalX, m_BoardY + DiagonalY };

	for (uint8_t k = 1; Board::IsWithinBoard(Position.x, Position.y); ++k)
	{
		if (m_Board.HasPieceAt(Position.x, Position.y))
		{
			BlockingSquares[0] = (sf::Vector2u)Position;
			return true;
		}
		Position = sf::Vector2i(m_BoardX + DiagonalX * k, m_BoardY + DiagonalY * k);
	}

	return false;
}
