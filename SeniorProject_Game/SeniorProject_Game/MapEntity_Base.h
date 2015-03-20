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
		sf::Vector2f BottomRightCorner(dest+sf::Vector2f(cwidth,cheight));
		sf::Vector2f TopLeftCorner(dest);
		sf::Vector2f BottomLeftCorner(dest + sf::Vector2f(0, cheight));

		Tile *TopLeft = tilemap->getTileDataFromPosition(TopLeftCorner);
		Tile *TopRight = tilemap->getTileDataFromPosition(TopRightCorner);
		Tile *BottomLeft = tilemap->getTileDataFromPosition(BottomLeftCorner);
		Tile *BottomRight = tilemap->getTileDataFromPosition(BottomRightCorner);
		//PANICNUMBER((bool)(BottomLeft->getType() == Tile::SOLID))


		
		if (isFalling)
		{
			if ((BottomLeft->getType() == Tile::TileType::SOLID) || (BottomRight->getType() == Tile::TileType::SOLID))
			{
				isFalling = false;
				int TileUpperY = (BottomRightCorner.y / tilemap->getTileSize())*tilemap->getTileSize();
				int penetration = dest.y - TileUpperY;
				if (penetration == 1)
				{
					position.y = dest.y - cheight - penetration;
				}
				else
				{
					position.y = dest.y - cheight - penetration - 2;
				}
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
			
		position.x = dest.x;
	}
protected:
	TileMap *tilemap;
    
	//Position
	sf::Vector2f position;
	sf::Vector2f velocity;
	//Movement
	sf::Vector2f currentMovement;
	float currentJumpingMovement;
	//EntityDimension
	float cwidth;
	float cheight;
	//Speed
	float MaximumSpeed;
	float MovementSpeed;
	float gravityConstant;
	float JumpImpulse;
	float JumpSlowing;
	//Boolean
	bool isJumping;
	bool isFalling;
};

