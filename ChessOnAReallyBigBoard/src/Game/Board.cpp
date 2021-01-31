#include "Board.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Pieces/Pawn.h"
#include "Core/Engine/Engine.h"
#include "Core/Engine/TextureManager.h"

const sf::Color Board::DarkSquareColor = { 84, 48, 7 };
const sf::Color Board::LightSquareColor = { 219, 210, 180 };

Board::Board(const sf::Vector2u& Size, const class Engine& NEngine)
	:
	m_Engine(NEngine)
{
	SetupBoard();

	SquareSize = Size.x < Size.y ? Size.x / Width : Size.y / Height;
	float PieceScale = SquareSize / m_Engine.GetTextureManager().GetArchbishopTexture(EPieceColor::White).getSize().x;

	for (Square& CurrentSquare : m_BoardSquares)
		if (CurrentSquare.bHasPiece)
			CurrentSquare.m_Piece->ScaleSprite(PieceScale);

	GenerateBackground(Size.x, Size.y);
}

void Board::Render(sf::RenderWindow& Window)
{
	Window.draw(m_BackgroundSprite);
	for (const Square& BoardSquare : m_BoardSquares)
	{
		if (BoardSquare.bHasPiece)
			BoardSquare.m_Piece->Render(Window);
	}
}

void Board::Resize(const sf::Vector2u& Size)
{
	float OldSquareSize = SquareSize;
	SquareSize = Size.x < Size.y ? Size.x / Width : Size.y / Height;
	float Scale = SquareSize / m_Engine.GetTextureManager().GetArchbishopTexture(EPieceColor::White).getSize().x;

	for (Square& CurrentSquare : m_BoardSquares)
		if (CurrentSquare.bHasPiece)
			CurrentSquare.m_Piece->ScaleSprite(Scale);

	GenerateBackground(Width * (unsigned int)SquareSize, Height * (unsigned int)SquareSize);
}

void Board::GenerateBackground(uint32_t SizeX, uint32_t SizeY)
{
	m_BackgroundTexture.create(SizeX, SizeY);

	sf::RectangleShape Square;
	Square.setSize(sf::Vector2f(SquareSize, SquareSize));

	m_BackgroundTexture.clear();
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

			m_BackgroundTexture.draw(Square);
		}
	}

	m_BackgroundTexture.display();
	m_BackgroundSprite.setTexture(m_BackgroundTexture.getTexture(), true);
}

void Board::SetupBoard()
{
	uint8_t BlackPieceRow = 0;
	uint8_t WhitePieceRow = Height - 1;
	// Pawns
	for (int x = 0; x < Width; ++x)
	{
		m_BoardSquares[1 * Width + x] = Square { true, 
			std::make_unique<Pawn>(m_Engine.GetTextureManager().GetPawnTexture(EPieceColor::Black), EPieceColor::Black, x, 1) };
		m_BoardSquares[(Height - 2) * Width + x] = Square{ true,
			std::make_unique<Pawn>(m_Engine.GetTextureManager().GetPawnTexture(EPieceColor::White), EPieceColor::White, x, (Height - 2)) };
	}

	// Kings
	m_BoardSquares[0 * Width + 8] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetKingTexture(EPieceColor::Black), EPieceColor::Black, 8, BlackPieceRow) };
	m_BoardSquares[(Height - 1) * Width + 8] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetKingTexture(EPieceColor::White), EPieceColor::White, 8, WhitePieceRow) };

	// Queens
	m_BoardSquares[BlackPieceRow * Width + 7] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetQueenTexture(EPieceColor::Black), EPieceColor::Black, 7, BlackPieceRow) };
	m_BoardSquares[WhitePieceRow * Width + 7] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetQueenTexture(EPieceColor::White), EPieceColor::White, 7, WhitePieceRow) };

	// Rooks
	// Black Rooks
	m_BoardSquares[BlackPieceRow * Width + 0] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetRookTexture(EPieceColor::Black), EPieceColor::Black, 0, BlackPieceRow) };
	m_BoardSquares[BlackPieceRow * Width + 15] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetRookTexture(EPieceColor::Black), EPieceColor::Black, 15, BlackPieceRow) };
	// White Rooks
	m_BoardSquares[WhitePieceRow * Width + 0] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetRookTexture(EPieceColor::White), EPieceColor::White, 0, WhitePieceRow) };
	m_BoardSquares[WhitePieceRow * Width + 15] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetRookTexture(EPieceColor::White), EPieceColor::White, 15, WhitePieceRow) };

	// Knights
	// Black Knights
	m_BoardSquares[BlackPieceRow * Width + 1] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetKnightTexture(EPieceColor::Black), EPieceColor::Black, 1, BlackPieceRow) };
	m_BoardSquares[BlackPieceRow * Width + 14] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetKnightTexture(EPieceColor::Black), EPieceColor::Black, 14, BlackPieceRow) };
	// White Knight
	m_BoardSquares[WhitePieceRow * Width + 1] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetKnightTexture(EPieceColor::White), EPieceColor::White, 1, WhitePieceRow) };
	m_BoardSquares[WhitePieceRow * Width + 14] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetKnightTexture(EPieceColor::White), EPieceColor::White, 14, WhitePieceRow) };

	// Wizards
	// Black Wizards
	m_BoardSquares[BlackPieceRow * Width + 2] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetWizardTexture(EPieceColor::Black), EPieceColor::Black, 2, BlackPieceRow) };
	m_BoardSquares[BlackPieceRow * Width + 13] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetWizardTexture(EPieceColor::Black), EPieceColor::Black, 13, BlackPieceRow) };
	// White Wizards
	m_BoardSquares[WhitePieceRow * Width + 2] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetWizardTexture(EPieceColor::White), EPieceColor::White, 2, WhitePieceRow) };
	m_BoardSquares[WhitePieceRow * Width + 13] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetWizardTexture(EPieceColor::White), EPieceColor::White, 13, WhitePieceRow) };

	// Champions
	// Black Champions
	m_BoardSquares[BlackPieceRow * Width + 3] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetChampionTexture(EPieceColor::Black), EPieceColor::Black, 3, BlackPieceRow) };
	m_BoardSquares[BlackPieceRow * Width + 12] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetChampionTexture(EPieceColor::Black), EPieceColor::Black, 12, BlackPieceRow) };
	// White Wizards
	m_BoardSquares[WhitePieceRow * Width + 3] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetChampionTexture(EPieceColor::White), EPieceColor::White, 3, WhitePieceRow) };
	m_BoardSquares[WhitePieceRow * Width + 12] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetChampionTexture(EPieceColor::White), EPieceColor::White, 12, WhitePieceRow) };

	// Bishops
	// Black Bishops
	m_BoardSquares[BlackPieceRow * Width + 4] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetBishopTexture(EPieceColor::Black), EPieceColor::Black, 4, BlackPieceRow) };
	m_BoardSquares[BlackPieceRow * Width + 11] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetBishopTexture(EPieceColor::Black), EPieceColor::Black, 11, BlackPieceRow) };
	// White Bishops
	m_BoardSquares[WhitePieceRow * Width + 4] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetBishopTexture(EPieceColor::White), EPieceColor::White, 4, WhitePieceRow) };
	m_BoardSquares[WhitePieceRow * Width + 11] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetBishopTexture(EPieceColor::White), EPieceColor::White, 11, WhitePieceRow) };

	// Roses
	// Black Rose
	m_BoardSquares[BlackPieceRow * Width + 5] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetRoseTexture(EPieceColor::Black), EPieceColor::Black, 5, BlackPieceRow) };
	// White Rose
	m_BoardSquares[WhitePieceRow * Width + 5] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetRoseTexture(EPieceColor::White), EPieceColor::White, 5, WhitePieceRow) };

	// Archbishops
	// Black Archbishop
	m_BoardSquares[BlackPieceRow * Width + 6] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetArchbishopTexture(EPieceColor::Black), EPieceColor::Black, 6, BlackPieceRow) };
	// White Archbishop
	m_BoardSquares[WhitePieceRow * Width + 6] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetArchbishopTexture(EPieceColor::White), EPieceColor::White, 6, WhitePieceRow) };

	// Chancellors
	// Black Chancellor
	m_BoardSquares[BlackPieceRow * Width + 9] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetChancellorTexture(EPieceColor::Black), EPieceColor::Black, 9, BlackPieceRow) };
	// White Chancellor
	m_BoardSquares[WhitePieceRow * Width + 9] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetChancellorTexture(EPieceColor::White), EPieceColor::White, 9, WhitePieceRow) };

	// Fools
	// Black Fool
	m_BoardSquares[BlackPieceRow * Width + 10] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetFoolTexture(EPieceColor::Black), EPieceColor::Black, 10, BlackPieceRow) };
	// White Fool
	m_BoardSquares[WhitePieceRow * Width + 10] = Square{ true,
		std::make_unique<Pawn>(m_Engine.GetTextureManager().GetFoolTexture(EPieceColor::White), EPieceColor::White, 10, WhitePieceRow) };
}
