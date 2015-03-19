#include "TileMap.h"
#include <iostream>

TileMap::TileMap()
{
}


TileMap::~TileMap()
{
}
void TileMap::LoadTileSet(const int TileSize,const char *TileImage, const char *TileData)
{
	tileset.SetTileSize(TileSize);
	tileset.LoadTileSet(TileImage, TileData);
};
void TileMap::LoadMapData(const char *mapData)
{
	std::vector<int> dataV;
	std::ifstream file(mapData);
	int y = 0;
	if (file.is_open())
	{
		std::string string;
		while (std::getline(file, string,'e'))
		{
			TilesX=((string.size() - 1) / 2)+1;
			for (int i = 0; i < string.size(); i = i + 2)
			{
				dataV.push_back( atoi  ( &string.c_str()[i] )  );
			}
			y++;
		}
	}
	file.close();
	TilesY = y;
	MapData = new int[TilesX*TilesY];
	for (int Y = 0; Y < TilesY; Y++)
	{
		for (int x = 0; x < TilesX; x++)
		{
			MapData[Y*TilesX + x] = dataV[Y*TilesX + x];
		}
	}

};
void TileMap::Draw(sf::RenderWindow &RenderTarget)
{
	for (int y = 0; y < TilesY; y++)
	{
		for (int x = 0; x < TilesX; x++)
		{
			tileset.getTile(MapData[y*TilesX + x])->draw(RenderTarget, x*tileset.getTileSize(), y*tileset.getTileSize());
		}
	}
};