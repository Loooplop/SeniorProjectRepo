#pragma once
#include "MapEntity_Base.h"
#include "Animation.h"
class MapEntity_Enemy: public MapEntity_Base 
{
public:
	MapEntity_Enemy();
	MapEntity_Enemy(const char *filename,TileMap *tilemap)
	{
		position = sf::Vector2f(800, 430);
		tex.loadFromFile(filename);
		animation.SetTexture(&tex, 30, 40);
		animation.SetDelay(0.05f);
		cwidth = animation.FrameWidth();
		cheight = animation.FrameHeight();
		isJumping = false;
		isGrounded = false;
		initialJumpImpulse = -30.0f;
		currentJumpingMovement = 0.0f;
		JumpSlowingSpeed = 1.8f;
		MaximumSpeed = 20.0f;
		MovementSpeed = 3.0f;
		gravityAcceleration = 4.0f;
		velocity.x = MovementSpeed;
		MovingRight = true;
		this->tilemap = tilemap;
		toBeRemoved = false;
	}
	MapEntity_Enemy(const char *filename, TileMap *tilemap,float SpawnX,float SpawnY)
	{
		position = sf::Vector2f(SpawnX, SpawnY);
		tex.loadFromFile(filename);
		animation.SetTexture(&tex, 30, 40);
		animation.SetDelay(0.05f);
		cwidth = animation.FrameWidth();
		cheight = animation.FrameHeight();
		isJumping = false;
		isGrounded = false;
		initialJumpImpulse = -30.0f;
		currentJumpingMovement = 0.0f;
		JumpSlowingSpeed = 1.8f;
		MaximumSpeed = 20.0f;
		MovementSpeed = 3.0f;
		gravityAcceleration = 4.0f;
		velocity.x = MovementSpeed;
		MovingRight = true;
		this->tilemap = tilemap;
		toBeRemoved = false;
	}
	~MapEntity_Enemy(); 
	void handleEventInput(sf::Keyboard::Key key, bool isPressed)
	{

	};
	void handleRealtimeInput()
	{
		if (!isGrounded || isFalling)
		{
			velocity.y = gravityAcceleration;
		}
		else
		{
			if (isJumping)
			{
				if (currentJumpingMovement >= 0)
				{
					isJumping = false;
					currentJumpingMovement = 0;
				}
				else
				{
					currentJumpingMovement += JumpSlowingSpeed;
					velocity.y = currentJumpingMovement;
				}


			}
		}
		velocity.x = std::min(velocity.x, MaximumSpeed);
		velocity.y = std::min(velocity.y, MaximumSpeed);
	};
	void Update(sf::Time delta)
	{
		CollisionWithTileMap();
		position = temp;
		if (velocity.x == 0)
		{
			if (MovingRight == true)
			{
				MovingRight = false;
				animation.SetFlip(true);
			}
			else
			{
				animation.SetFlip(false);
				MovingRight = true;
			};
		}
		if (MovingRight)
		{
			velocity.x = MovementSpeed;
		}
		else
		{
			velocity.x = -MovementSpeed;
		}
		animation.Update();
	};
	void Render(sf::RenderWindow &RenderTarget)
	{
		animation.DrawFrame(RenderTarget, position);
	};
	bool NeedRemoval()
	{
		return toBeRemoved;
	}
	void SetRemovalFlag(bool flag)
	{
		toBeRemoved = flag;
	}
	sf::Texture tex;
	Animation animation;
	bool MovingRight;
	bool toBeRemoved;
};

