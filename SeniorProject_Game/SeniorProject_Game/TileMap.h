#pragma once
#include "TileSet.h"
class TileMap
{
public:
	TileMap();
	~TileMap();
	void LoadTileSet(const int TileSize, const char *TileImage, const char *TileData);
	void LoadMapData(const char *mapData);
	void Draw(sf::RenderWindow &RenderTarget);
	int getTileSize()
	{
		return tileset.getTileSize();
	}
	Tile *getTileDataFromPosition(sf::Vector2f pos)
	{
		int TileX = pos.x / tileset.getTileSize();
		int TileY = pos.y / tileset.getTileSize();

		return tileset.getTile(MapData[TileY*TilesX + TileX]);
	}
private:
	int TilesX, TilesY;
	TileSet tileset;
	int *MapData;
};

