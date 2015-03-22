#pragma once
#include "TileMap.h"
class MapEntity_Base
{
public:
	MapEntity_Base(TileMap *Map)
	{
		tilemap = Map;
	};
	MapEntity_Base();
	~MapEntity_Base();
	virtual void handleEventInput(sf::Keyboard::Key key, bool isPressed) = 0;
	virtual void handleRealtimeInput() = 0;
	virtual void Update(sf::Time delta) = 0;
	virtual void Render(sf::RenderWindow &RenderTarget) = 0;
	void setTileMap(TileMap *TileMapExt)
	{
		this->tilemap = TileMapExt;
	}

	void CollisionWithTileMap()
	{
		sf::Vector2f dest = position + sf::Vector2f(0,velocity.y);
		sf::Vector2f TopRightCorner(dest+sf::Vector2f(cwidth,0));
		sf::Vector2f BottomRightCorner(dest+sf::Vector2f(cwidth,cheight+1));
		sf::Vector2f TopLeftCorner(dest);
		sf::Vector2f BottomLeftCorner(dest + sf::Vector2f(0, cheight+1));

		Tile *TopLeft = tilemap->getTileDataFromPosition(TopLeftCorner);
		Tile *TopRight = tilemap->getTileDataFromPosition(TopRightCorner);
		Tile *BottomLeft = tilemap->getTileDataFromPosition(BottomLeftCorner);
		Tile *BottomRight = tilemap->getTileDataFromPosition(BottomRightCorner);


		
		if (isFalling)
		{
			if ((BottomLeft->getType() == Tile::TileType::SOLID) || (BottomRight->getType() == Tile::TileType::SOLID) || (BottomLeft->getType() == Tile::TileType::SOLID) && (BottomRight->getType() == Tile::TileType::SOLID))
			{
				isFalling = false;
				int TileUpperY = (BottomRightCorner.y / tilemap->getTileSize())*tilemap->getTileSize();
				position.y = TileUpperY-cheight;
			}

			else
			{
				position.y = dest.y;
			}
		}
		else
		{
			if ((!BottomLeft->getType() == Tile::TileType::SOLID) && (!BottomRight->getType() == Tile::TileType::SOLID))
			{
				isFalling = true;
				position.y = dest.y;
			}
		}
		position.x += MovementSpeed;
	}
protected:
	TileMap *tilemap;
    
	//Position
	sf::Vector2f position;
	sf::Vector2f velocity;
	//Movement
	sf::Vector2f currentMovement;
	float currentJumpingMovement;
	float initialJumpImpulse;
	//EntityDimension
	float cwidth;
	float cheight;
	//Speed
	float MaximumSpeed;
	float MovementSpeed;
	float currentGravity;
	float gravityAcceleration;
	float JumpImpulse;
	float JumpSlowingSpeed;
	//Boolean
	bool isJumping;
	bool isFalling;
};

