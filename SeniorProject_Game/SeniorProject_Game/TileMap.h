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



private:
	std::vector<sf::Vector3i> TileData;
	sf::Vector3i TileMapData;
	sf::Texture TileMapTexture;
	sf::Sprite TileMapSprite;
};

