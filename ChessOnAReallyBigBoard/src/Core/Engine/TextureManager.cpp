#include "TextureManager.h"
#include "Game/Pieces/Piece.h"


const std::array<std::string, 12> TextureManager::s_Filenames = { "archbishop", "bishop", "champion",
"chancellor", "fool", "king", "knight", "pawn", "queen", "rook", "rose", "wizard" };

TextureManager::TextureManager(const std::string& FolderPath)
{
    for (uint8_t i = 0; i < 2 * s_Filenames.size(); ++i)
    {
        if (i % 2 == 0)
            m_Textures[i].loadFromFile(FolderPath + s_Filenames[i / 2] + "b" + ".png"); // integer division truncates decimal part
        else
            m_Textures[i].loadFromFile(FolderPath + s_Filenames[i / 2] + "w" + ".png"); // integer division truncates decimal part
    }
}

const sf::Texture& TextureManager::GetArchbishopTexture(EPieceColor Color) const
{
    switch (Color)
    {
    case  EPieceColor::Black:
        return m_Textures[0 * 2];
    case EPieceColor::White:
        return m_Textures[0 * 2 + 1];
    }
}

const sf::Texture& TextureManager::GetBishopTexture(EPieceColor Color) const
{
    switch (Color)
    {
    case  EPieceColor::Black:
        return m_Textures[1 * 2];
    case EPieceColor::White:
        return m_Textures[1 * 2 + 1];
    }
}

const sf::Texture& TextureManager::GetChampionTexture(EPieceColor Color) const
{
    switch (Color)
    {
    case  EPieceColor::Black:
        return m_Textures[2 * 2];
    case EPieceColor::White:
        return m_Textures[2 * 2 + 1];
    }
}

const sf::Texture& TextureManager::GetChancellorTexture(EPieceColor Color) const
{
    switch (Color)
    {
    case  EPieceColor::Black:
        return m_Textures[3 * 2];
    case EPieceColor::White:
        return m_Textures[3 * 2 + 1];
    }
}

const sf::Texture& TextureManager::GetFoolTexture(EPieceColor Color) const
{
    switch (Color)
    {
    case  EPieceColor::Black:
        return m_Textures[4 * 2];
    case EPieceColor::White:
        return m_Textures[4 * 2 + 1];
    }
}

const sf::Texture& TextureManager::GetKingTexture(EPieceColor Color) const
{
    switch (Color)
    {
    case  EPieceColor::Black:
        return m_Textures[5 * 2];
    case EPieceColor::White:
        return m_Textures[5 * 2 + 1];
    }
}

const sf::Texture& TextureManager::GetKnightTexture(EPieceColor Color) const
{
    switch (Color)
    {
    case  EPieceColor::Black:
        return m_Textures[6 * 2];
    case EPieceColor::White:
        return m_Textures[6 * 2 + 1];
    }
}

const sf::Texture& TextureManager::GetPawnTexture(EPieceColor Color) const
{
    switch (Color)
    {
    case  EPieceColor::Black:
        return m_Textures[7 * 2];
    case EPieceColor::White:
        return m_Textures[7 * 2 + 1];
    }
}

const sf::Texture& TextureManager::GetQueenTexture(EPieceColor Color) const
{
    switch (Color)
    {
    case  EPieceColor::Black:
        return m_Textures[8 * 2];
    case EPieceColor::White:
        return m_Textures[8 * 2 + 1];
    }
}

const sf::Texture& TextureManager::GetRookTexture(EPieceColor Color) const
{
    switch (Color)
    {
    case  EPieceColor::Black:
        return m_Textures[9 * 2];
    case EPieceColor::White:
        return m_Textures[9 * 2 + 1];
    }
}

const sf::Texture& TextureManager::GetRoseTexture(EPieceColor Color) const
{
    switch (Color)
    {
    case  EPieceColor::Black:
        return m_Textures[10 * 2];
    case EPieceColor::White:
        return m_Textures[10 * 2 + 1];
    }
}

const sf::Texture& TextureManager::GetWizardTexture(EPieceColor Color) const
{
    switch (Color)
    {
    case  EPieceColor::Black:
        return m_Textures[11 * 2];
    case EPieceColor::White:
        return m_Textures[11 * 2 + 1];
    }
}