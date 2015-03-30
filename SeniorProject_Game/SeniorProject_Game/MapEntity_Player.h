#pragma once
#include "SFML\Audio.hpp"
#include "MapEntity_Base.h"
#include "MapEntity_Enemy.h"
#include "MapEntity_Projectile_Base.h"
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
				JumpSound.play();
				isJumping = true;
				currentJumpingMovement = initialJumpImpulse;
			}
		}
		
		if (key == sf::Keyboard::T && isPressed == true)
		{
			if (isAttacking == false && isGrounded == true)
			{
				AttackSound.play();
				isAttacking = true;
				animationAttacking.SetFlip(currentanimation->FlipFlag());
				animationAttacking.Reset();
				currentanimation = &animationAttacking;
				cwidth = currentanimation->CollisionX();
				cheight = currentanimation->CollisionY();
			}

		}
		if (key == sf::Keyboard::Y && isPressed == true)
		{

			if (fireBallShot < maxFireballs)
			{
				ExplosionSound.play();
				if (currentanimation->FlipFlag())
				{
					fireballs.push_back(new MapEntity_Projectile_Base("FireballTravel.png", "FireballHit.png", tilemap, getPosition().x, getPosition().y + 0.25*cheight, 5.0f, -1, 0.0f));
				}
				else
				{
					fireballs.push_back(new MapEntity_Projectile_Base("FireballTravel.png", "FireballHit.png", tilemap, getPosition().x + 0.75f*cwidth, getPosition().y + 0.25*cheight, 5.0f, 1, 0.0f));
				}
				fireBallShot++;
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
		if (fireballs.size() != 0)
		{
			for (int i = fireballs.size() - 1; i >= 0; i--)
			{
				if (fireballs[i]->NeedRemoval() == true)
				{
					fireballs.erase(fireballs.begin() + i);
				}
			}
		}

		currentanimation->Update();
		calculateNextPosition(delta);
		CollisionWithTileMap();
		position.x = temp.x;
		position.y = temp.y;
		for (int i = 0; i < fireballs.size(); i++)
		{
			fireballs[i]->Update(delta);
		}
	};
	bool PlayerProjectileCollisionWithOtherMapEntity(MapEntity_Enemy *other)
	{
		if (other->NeedRemoval())
			return false;

		for (int i = 0; i < fireballs.size(); i++)
		{
			if (fireballs[i]->IntersectsAnotherMapEntity(other)&&fireballs[i]->NeedRemoval()==false)
			{
				fireballs[i]->setHit(true);
				other->SetRemovalFlag(true);
				return true;
			}


		}
		return false;

	}
	void Render(sf::RenderWindow &RenderTarget)
	{
		currentanimation->DrawFrame(RenderTarget, position);
		for (int i = 0; i < fireballs.size(); i++)
		{
			fireballs[i]->Render(RenderTarget);
		}
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

	int maxFireballs;
	int fireBallShot;
	bool isAttacking;
	Animation *currentanimation;
	Animation animationIdle;
	Animation animationWalking;
	Animation animationAttacking;
	sf::Texture aniTextureIdle;
	sf::Texture aniTextureWalking;
	sf::Texture aniTextureAttacking;
	std::vector<MapEntity_Projectile_Base*> fireballs;
	sf::SoundBuffer JumpSoundData;
	sf::Sound JumpSound;
	sf::SoundBuffer ExplosionSoundData;
	sf::Sound ExplosionSound;
	sf::SoundBuffer AttackSoundData;
	sf::Sound AttackSound;
};

