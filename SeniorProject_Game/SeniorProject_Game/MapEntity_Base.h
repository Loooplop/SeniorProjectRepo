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
		int currRow = (int)position.x / tilemap->getTileSize();
		int currCol = (int)position.y / tilemap->getTileSize();
		temp = position;
		sf::Vector2f dest = position + velocity;
		Tile::TileType TopLeft;
		Tile::TileType TopRight;
		Tile::TileType BottomLeft;
		Tile::TileType BottomRight;
		getCornerTileValues(position.x, dest.y, TopLeft, TopRight, BottomLeft, BottomRight);

		if (velocity.y > 0)
		{
			if (BottomLeft == Tile::SOLID || BottomRight == Tile::SOLID)
			{
				isGrounded = true;
				isFalling = false;
				velocity.y = 0;
				temp.y = (currCol + 1)*tilemap->getTileSize()-cheight;
				PANICSTRING("Collided with Bottom")
			}
			else
			{
				
				temp.y += velocity.y;
			}

		}

		if (velocity.y < 0)
		{
			if ((TopLeft == Tile::SOLID || TopRight == Tile::SOLID)&&(BottomLeft!=Tile::SOLID&&BottomRight!=Tile::SOLID))
			{
				velocity.y = 0;
				temp.y = (currCol)*tilemap->getTileSize() + tilemap->getTileSize();
				if (isJumping == true)
				{
					isFalling = true;
					isJumping = false;
					currentJumpingMovement = 0;
				}
			}
			else
			{
				temp.y += velocity.y;
			}
		}


		getCornerTileValues(dest.x, position.y, TopLeft, TopRight, BottomLeft, BottomRight);

		if (velocity.x > 0)
		{
			if (TopRight == Tile::SOLID)
			{
				velocity.x = 0;
				temp.x = (currRow + 1)*tilemap->getTileSize() - cwidth;
			}
			else
			{
				temp.x += velocity.x;
			}

		}

		if (velocity.x < 0)
		{
			if (TopLeft == Tile::SOLID)
			{
				PANICNUMBER(0)
				velocity.x = 0;
				temp.x = (currRow)*tilemap->getTileSize()+tilemap->getTileSize();
			}
			else
			{
				PANIC
				temp.x += velocity.x;
			}


		}

		
		getCornerTileValues(position.x, position.y-1, TopLeft, TopRight, BottomLeft, BottomRight);

		if (BottomLeft != Tile::SOLID&&BottomRight != Tile::SOLID&&!isJumping)
		{
			PANICSTRING("is falling")
				isGrounded = false;

		}
	};
	void getCornerTileValues(float positionX, float positionY, Tile::TileType &TopLeft, Tile::TileType &TopRight, Tile::TileType &BottomLeft, Tile::TileType &BottomRight)
	{
		int LeftX = (int)(position.x) / (int)tilemap->getTileSize();
		int RightX = (int)(position.x + cwidth+1) / (int)tilemap->getTileSize();
		int TopY = (int)(position.y) / (int)tilemap->getTileSize();
		int BottomY = (int)(position.y + cheight) / (int)tilemap->getTileSize();

		Tile *topLeft = tilemap->getTileFromTileCoordinates(LeftX, TopY);
		Tile *topRight = tilemap->getTileFromTileCoordinates(RightX, TopY);
		Tile *bottomLeft = tilemap->getTileFromTileCoordinates(LeftX, BottomY);
		Tile *bottomRight = tilemap->getTileFromTileCoordinates(RightX, BottomY);
		TopLeft = topLeft->getType();
		TopRight = topRight->getType();
		BottomLeft = bottomLeft->getType();
		BottomRight = bottomRight->getType();
	}
	bool Jummping(){ return isJumping; };
	bool Falling(){ return isFalling; };
	bool Grounded(){ return isGrounded; };
protected:
	TileMap *tilemap;
    
	//Position
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f temp;
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
	bool isGrounded;
};

