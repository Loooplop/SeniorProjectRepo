#pragma once
#include <fstream>
#include <SFML\Graphics.hpp>
#include "Tile.h"
#include <vector>
#include <iostream>
#define PANIC std::cout << "Panic" << std::endl;
#define PANICNUMBER(x) std::cout << "Panic: " <<x<<std::endl;
#define PANICSTRING(x) std::cout <<x<<std::endl;
class TileSet
{
public:
	TileSet(int tileSize)
	{
		TileSize = tileSize;
	};
	TileSet()
	{
		TileSize = 0;
	};
	~TileSet();
	void SetTileSize(int size)
	{
		TileSize = size;
	}
	void LoadTileSet(const char *TileImage, const char *TileData)
	{
		if (!tileSetTexture.loadFromFile(TileImage))
		{
			std::cout << "Error Loading: " << TileImage << std::endl;
		};
		TilesAcrossX = tileSetTexture.getSize().x / TileSize;
		TilesAcrossY = tileSetTexture.getSize().y / TileSize;
		tiles = new Tile[TilesAcrossX*TilesAcrossY];
		std::ifstream file(TileData);
		std::vector<int> TileDataV;
		if (file.is_open())
		{
			std::string string;
			while (std::getline(file,string))
			{
				TileDataV.push_back(std::atoi(string.c_str()));
			}
		}
		for (int y = 0; y < TilesAcrossY; y++)
		{
			for (int x = 0; x < TilesAcrossX; x++)
			{
				tiles[y*TilesAcrossX + x].setTexture(tileSetTexture);
				tiles[y*TilesAcrossX + x].setTextureRect(sf::IntRect(x*TileSize, y*TileSize, TileSize, TileSize));
				switch (TileDataV[y*TilesAcrossX + x])
				{
				case 0:
					tiles[y*TilesAcrossX + x].setType(Tile::AIR);
					break;
				case 1:
					tiles[y*TilesAcrossX + x].setType(Tile::SOLID);
					break;
				default:
					tiles[y*TilesAcrossX + x].setType(Tile::AIR);
					break;
				}
			}
		}
		file.close();
	}
	Tile *getTile(int index)
	{
		return &tiles[index];
	}
	int getTileSize(){ return TileSize; };
private:
	Tile *tiles;
	sf::Texture tileSetTexture;
	int TilesAcrossX;
	int TilesAcrossY;
	int TileSize;
};

