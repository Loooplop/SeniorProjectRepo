#pragma once
#include "MapEntity_Base.h"
#include "Animation.h"
class MapEntity_Player :
	public MapEntity_Base
{
public:
	MapEntity_Player();
	~MapEntity_Player();
	void handleEventInput(sf::Keyboard::Key key, bool isPressed)
	{
		if (key == sf::Keyboard::Space&&isPressed == true)
		{
			if (!isJumping&&isGrounded)
			{
				isJumping = true;
				currentJumpingMovement = initialJumpImpulse;
			}
		}
		
	};
	void handleRealtimeInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			velocity.x = -MovementSpeed;
			animation.SetFlip(true);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			velocity.x = MovementSpeed;
			animation.SetFlip(false);
		}
		else
		{
			velocity.x = 0;
		}
	}
	void calculateNextPosition(sf::Time delta)
	{
		if (!isGrounded||isFalling)
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
	}
	void Update(sf::Time delta)
	{
		animation.Update();
		calculateNextPosition(delta);
		CollisionWithTileMap();
		position.x = temp.x;
		position.y = temp.y;
	};
	void Render(sf::RenderWindow &RenderTarget)
	{
		animation.DrawFrame(RenderTarget, position);
	};
	sf::Vector2f getPosition()
	{
		return position;
	}
	Animation animation;
	sf::Texture aniTexture;
};

