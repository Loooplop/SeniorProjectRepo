#pragma once
#include "MapEntity_Base.h"
class MapEntity_Player :
	public MapEntity_Base
{
public:
	MapEntity_Player();
	~MapEntity_Player();
	void handleEventInput(sf::Keyboard::Key key, bool isPressed)
	{
		
		
	};
	void handleRealtimeInput()
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)||sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			MovementSpeed = 5;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			MovementSpeed = -5;
		}
		else
		{
			MovementSpeed = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{

			if (!isJumping&&!isFalling)
			{
				isJumping = true;
				isFalling = false;
				currentJumpingMovement = initialJumpImpulse;
			}
		}


		if (isJumping)
		{
			if (currentJumpingMovement >= 0)
			{
				isJumping = false;
				isFalling = true;
				currentJumpingMovement = 0.0f;
			}
			else
			{
				currentJumpingMovement += JumpSlowingSpeed;
			}
			velocity.y = currentJumpingMovement;

		}
		else
		{

			if (isFalling)
			{
				velocity.y = gravityAcceleration;
			}
		}
		velocity.x = std::min(velocity.x, MaximumSpeed);
		velocity.y = std::min(velocity.y, MaximumSpeed);
	}
	void Update(sf::Time delta)
	{
		CollisionWithTileMap();
	};
	void Render(sf::RenderWindow &RenderTarget)
	{
		rect.setPosition(position);
		RenderTarget.draw(rect);
	};
	sf::RectangleShape rect;

};

