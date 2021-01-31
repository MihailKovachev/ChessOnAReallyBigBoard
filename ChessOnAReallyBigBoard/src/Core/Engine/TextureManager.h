#pragma once

#include <SFML/Graphics/Texture.hpp>

#include <array>

enum class EPieceColor;

class TextureManager
{
public:
	TextureManager(const std::string& FolderPath);
	const sf::Texture& GetArchbishopTexture(EPieceColor Color) const;
	const sf::Texture& GetBishopTexture(EPieceColor Color) const;
	const sf::Texture& GetChampionTexture(EPieceColor Color) const;
	const sf::Texture& GetChancellorTexture(EPieceColor Color) const;
	const sf::Texture& GetFoolTexture(EPieceColor Color) const;
	const sf::Texture& GetKingTexture(EPieceColor Color) const;
	const sf::Texture& GetKnightTexture(EPieceColor Color) const;
	const sf::Texture& GetPawnTexture(EPieceColor Color) const;
	const sf::Texture& GetQueenTexture(EPieceColor Color) const;
	const sf::Texture& GetRookTexture(EPieceColor Color) const;
	const sf::Texture& GetRoseTexture(EPieceColor Color) const;
	const sf::Texture& GetWizardTexture(EPieceColor Color) const;
private:
	static const std::array<std::string, 12> s_Filenames;

	std::string m_Path = "../../resources";
	std::array<sf::Texture, 24> m_Textures;
};

