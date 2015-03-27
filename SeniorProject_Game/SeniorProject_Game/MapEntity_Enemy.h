#pragma once
#include "MapEntity_Base.h"
#include "Animation.h"
class MapEntity_Enemy: public MapEntity_Base 
{
public:
	MapEntity_Enemy();
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
	sf::Texture tex;
	Animation animation;
	bool MovingRight;
};

