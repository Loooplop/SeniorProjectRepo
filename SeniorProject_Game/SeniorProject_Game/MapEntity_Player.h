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
		
		if (key == sf::Keyboard::T && isPressed == true)
		{
			if (isAttacking==false)
			{
				isAttacking = true;
				animationAttacking.SetFlip(currentanimation->FlipFlag());
				animationAttacking.Reset();
				currentanimation = &animationAttacking;
				cwidth = currentanimation->CollisionX();
				cheight = currentanimation->CollisionY();
			}

		}


		
	};
	void handleRealtimeInput()
	{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)&&!isAttacking)
			{
				velocity.x = -MovementSpeed;
				currentanimation = &animationWalking;
				cwidth = currentanimation->CollisionX();
				cheight = currentanimation->CollisionY();
				currentanimation->SetFlip(true);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !isAttacking)
			{
				velocity.x = MovementSpeed;
				currentanimation = &animationWalking;
				cwidth = currentanimation->CollisionX();
				cheight = currentanimation->CollisionY();
				currentanimation->SetFlip(false);
			}
			else
			{
				if (isAttacking)
				{
					
					if (currentanimation->hasPlayedOnce())
					{
						PANICSTRING("Player is Attacking")
						animationAttacking.Reset();
						currentanimation = &animationIdle;
						cwidth = currentanimation->CollisionX();
						cheight = currentanimation->CollisionY();
						isAttacking = false;
					}
				}
				else
				{
					animationIdle.SetFlip(currentanimation->FlipFlag());
					currentanimation = &animationIdle;
					cwidth = currentanimation->CollisionX();
					cheight = currentanimation->CollisionY();
				}
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
		currentanimation->Update();
		calculateNextPosition(delta);
		CollisionWithTileMap();
		position.x = temp.x;
		position.y = temp.y;
	};
	void Render(sf::RenderWindow &RenderTarget)
	{
		currentanimation->DrawFrame(RenderTarget, position);
	};
	sf::Vector2f getPosition()
	{
		return position;
	}
	bool AttackingFlag()
	{
		return isAttacking;
	}

	private:
	bool isAttacking;
	Animation *currentanimation;
	Animation animationIdle;
	Animation animationWalking;
	Animation animationAttacking;
	sf::Texture aniTextureIdle;
	sf::Texture aniTextureWalking;
	sf::Texture aniTextureAttacking;
};

