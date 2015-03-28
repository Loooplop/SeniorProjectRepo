#pragma once
#include <SFML\Graphics.hpp>
class TilesMap
{
public:
	struct Tile
	{
		sf::Vector2f TextureCoordinates;
		bool isSolid;
	};
public:
	TilesMap();
	~TilesMap();



private:
	Tile *tiles;
	int TileSize;
	int TilesAcrossX;
	int TilesAcrossY;
	sf::Texture texture;
};

