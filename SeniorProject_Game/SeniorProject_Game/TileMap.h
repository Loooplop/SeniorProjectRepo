#pragma once
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <fstream>
#include <vector>
class TileMap
{
public:
	TileMap();
	~TileMap();
	void LoadTileData(const char *filepath);
	void Draw(sf::RenderWindow *renderTarget);
	void ChangeTexture(const char *textureFilePath);
	void ChangeTileData(std::vector<sf::Vector3i> newData);
	bool isTIleSolid(sf::Vector2f positionToCheck);
	bool isTileSolid(int XPosition, int YPosition);
	sf::Vector3i getTileData(sf::Vector2i indexPosition);
	sf::Vector3i getTileData(int XPosition, int YPosition);
	int getTileSize()
	{
		return TileMapData.x;
	}
	sf::IntRect getTIlePosition(sf::Vector2f indexPosition)
	{
		sf::Vector2i CellIndex = sf::Vector2i((int)indexPosition.x / TileMapData.x, (int)indexPosition.y / TileMapData.x);
		CellIndex *= 25;
		return sf::IntRect(CellIndex.x, CellIndex.y, CellIndex.x + getTileSize(), CellIndex.y + getTileSize());
	}
	sf::Sprite *getTileMapSprite();
	sf::Texture *getTileMapTexture();
private:
	int VectorToIndex(sf::Vector2f position);
	std::vector<sf::Vector3i> TileData;
	sf::Vector3i TileMapData;
	sf::Texture TileMapTexture;
	sf::Sprite TileMapSprite;
};

