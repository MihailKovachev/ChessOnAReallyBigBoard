#include "Rook.h"

#include "Game/Board.h"

Rook::Rook(const sf::Sprite& Sprite, EPieceColor Color, Board& nBoard, uint8_t BoardX, uint8_t BoardY)
	: Piece(Sprite, Color, nBoard, BoardX, BoardY)
{
}

Rook::Rook(const sf::Texture& Texture, EPieceColor Color, Board& nBoard, uint8_t BoardX, uint8_t BoardY)
	: Piece(Texture, Color, nBoard, BoardX, BoardY)
{
}

bool Rook::Move(uint8_t NewX, uint8_t  NewY)
{
	if (NewX == m_BoardX && NewY == m_BoardY || !Board::IsWithinBoard(NewX, NewY))
		return false;

	std::array<sf::Vector2u, 2> BlockingFileSquares;
	if (IsBlockedOnFile(BlockingFileSquares))
	{
		EPieceColor Color;
		if ((NewY == BlockingFileSquares[0].y || NewY == BlockingFileSquares[1].y)
			&& m_Board.GetPieceColor(NewX, NewY, Color) && Color != m_Color)
		{
			m_BoardX = NewX;
			m_BoardY = NewY;
			return true;
		}
		else if (NewY < m_BoardY && (NewY < BlockingFileSquares[0].y || NewY < BlockingFileSquares[1].y))
		{
			return false;
		}
		else if (NewY > m_BoardY && (NewY > BlockingFileSquares[0].y || NewY > BlockingFileSquares[1].y))
		{
			return false;
		}
		else
		{
			m_BoardX = NewX;
			m_BoardY = NewY;
			return true;
		}
	}

	std::array<sf::Vector2u, 2> BlockingSquares;
	if (IsBlockedOnRow(BlockingSquares))
	{
		if (NewX == BlockingSquares[0].x || NewY == BlockingSquares[1].x)
		{
			m_BoardX = NewX;
			m_BoardY = NewY;
			return true;
		}
		else if (NewX < m_BoardX && (NewX < BlockingSquares[0].x || NewX < BlockingSquares[1].x))
		{
			return false;
		}
		else if (NewX > m_BoardX && (NewX > BlockingSquares[0].x || NewX > BlockingSquares[1].x))
		{
			return false;
		}
		else
		{
			m_BoardX = NewX;
			m_BoardY = NewY;
			return true;
		}
	}
	EPieceColor Color;
	if (m_Board.GetPieceColor(NewX, NewY, Color) && Color != m_Color)
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

bool Rook::IsBlockedOnFile(std::array<sf::Vector2u, 2>& BlockingSquares)
{
	uint8_t NumBlockingSquares = 0;
	for (uint8_t y = 0; y < Board::GetHeight(); ++y)
	{
		if (m_Board.HasPieceAt(m_BoardX, y) && y != m_BoardY)
		{
			BlockingSquares[NumBlockingSquares++] = sf::Vector2u(m_BoardX, y);
			if (NumBlockingSquares == 2)
				return true;
		}
	}

	if (NumBlockingSquares > 0)
	{
		return true;
	}

	return false;
}

bool Rook::IsBlockedOnRow(std::array<sf::Vector2u, 2>& BlockingSquares)
{
	uint8_t NumBlockingSquares = 0;
	for (uint8_t x = 0; x < Board::GetWidth(); ++x)
	{
		if (m_Board.HasPieceAt(x, m_BoardY) && x != m_BoardX)
		{
			BlockingSquares[NumBlockingSquares++] = sf::Vector2u(x, m_BoardY);
			if (NumBlockingSquares == 2)
				return true;
		}
	}

	if (NumBlockingSquares > 0)
	{
		return true;
	}

	return false;
}
