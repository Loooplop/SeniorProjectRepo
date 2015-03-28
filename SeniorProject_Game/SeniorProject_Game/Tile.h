#pragma once
#include <SFML\Graphics.hpp>
class Tile
{
public:
	enum TileType
	{
		SOLID,
		AIR,
		PLAYER_SPAWN,
		ENEMY_SPAWN
	};

public:
	Tile();
	~Tile();
	void setType(TileType type)
	{
		this->type = type;
	}
	void setTexture(sf::Texture &tex)
	{
		tileSprite.setTexture(tex);
	}
	void setTextureRect(sf::IntRect texCoord)
	{
		tileSprite.setTextureRect(texCoord);
	}
	void draw(sf::RenderWindow &window, float x, float y)
	{
		tileSprite.setPosition(x, y);
		window.draw(tileSprite);
	}
	TileType getType()
	{
		return type;
	}
private:
	TileType type;
	sf::Sprite tileSprite;
};

