#pragma once
#include "Entity.h"
#include "TileMap.h"
#include <iostream>
class AIEntity :
	public Entity
{
#define TopLeft 0
#define TopRight 1
#define BottomRight 2
#define BottomLeft 3
public:
	enum AIBehavior
	{
		MovingLeft,
		MovingRight,
		NotMoving
	};
public:
	AIEntity(int id) : Entity(id)
	{
		entity.setSize(sf::Vector2f(10, 10));
		entity.setFillColor(sf::Color::Black);
		position = sf::Vector2f(600, 0);
		behavior = AIBehavior::NotMoving;
		isJumping = false;
		JumpingVelocity = 0;
	};
	AIEntity();
	~AIEntity();
	void handleInput(sf::Keyboard::Key key)
	{
		switch (behavior)
		{
		case AIBehavior::MovingRight:
			Velocity = sf::Vector2f(5, 0);
			break;

		case AIBehavior::MovingLeft:
			Velocity = sf::Vector2f(-5, 0);
			break;
		case AIBehavior::NotMoving:
			Velocity = sf::Vector2f(0, 0);
			break;
		default:
			break;
		}
	};
	sf::Vector2f getCornerPosition(int flag)
	{
		switch (flag)
		{
		case 0:
			return position;
			break;
		case 1:
			return position + sf::Vector2f(entity.getSize().x, 0);
			break;
		case 2:
			return position + entity.getSize();
			break;
		case 3:
			return position + sf::Vector2f(0, entity.getSize().y);
			break;
		default:
			return position;
		}

	};
	void Update(sf::Time deltaTime, void *ExternalData)
	{
		if (Velocity.x > 0)
		{
			if (!((TileMap*)ExternalData)->isTIleSolid(getCornerPosition(BottomRight) + Velocity) && !((TileMap*)ExternalData)->isTIleSolid(getCornerPosition(TopRight) + Velocity))
			{
				position += Velocity;

			}
			else
			{
				float distance = 0;
				float DistanceFromBottomRight = abs(((TileMap*)ExternalData)->getTIlePosition(getCornerPosition(BottomRight)).width - getCornerPosition(BottomRight).x);
				float DistanceFromBottomLeft = abs(((TileMap*)ExternalData)->getTIlePosition(getCornerPosition(TopRight)).width - getCornerPosition(TopRight).x);
				if (DistanceFromBottomLeft < DistanceFromBottomRight)
				{
					distance = DistanceFromBottomLeft;
				}
				else
				{
					distance = DistanceFromBottomRight;
				}
				std::cout << "Velocity" << distance << std::endl;
				position += sf::Vector2f(distance - 1, 0);
				behavior = AIBehavior::MovingLeft;
			}


		}
		else if (Velocity.x < 0)
		{
			if (!((TileMap*)ExternalData)->isTIleSolid(getCornerPosition(BottomLeft) + Velocity) && !((TileMap*)ExternalData)->isTIleSolid(getCornerPosition(TopLeft) + Velocity))
			{
				position += Velocity;

			}
			else
			{
				float distance = 0;
				float DistanceFromBottomRight = abs((((TileMap*)ExternalData)->getTIlePosition(getCornerPosition(BottomLeft)).left - getCornerPosition(BottomLeft).x));
				float DistanceFromBottomLeft = abs((((TileMap*)ExternalData)->getTIlePosition(getCornerPosition(TopLeft)).left - getCornerPosition(TopLeft).x));
				if (DistanceFromBottomLeft > DistanceFromBottomRight)
				{
					distance = DistanceFromBottomLeft;
				}
				else
				{
					distance = DistanceFromBottomRight;
				}
				std::cout << "Distance: " << -distance << std::endl;
				position += sf::Vector2f(-distance + 1, 0);
				behavior = AIBehavior::MovingRight;
			}

		}
		if (!isJumping)
		{
			if (!((TileMap*)ExternalData)->isTIleSolid(getCornerPosition(BottomRight) + sf::Vector2f(0, 4)) && !((TileMap*)ExternalData)->isTIleSolid(getCornerPosition(BottomLeft) + sf::Vector2f(0, 4)))
			{
				position += sf::Vector2f(0, 4);

			}
			else
			{
				float distance = 0;
				float DistanceFromBottomRight = abs(getCornerPosition(BottomRight).y - ((TileMap*)ExternalData)->getTIlePosition(getCornerPosition(BottomRight)).height);
				float DistanceFromBottomLeft = abs(getCornerPosition(BottomLeft).y - ((TileMap*)ExternalData)->getTIlePosition(getCornerPosition(BottomLeft)).height);
				if (DistanceFromBottomLeft < DistanceFromBottomRight)
				{
					distance = DistanceFromBottomLeft;
				}
				else
				{
					distance = DistanceFromBottomRight;
				}
				position += sf::Vector2f(0, distance - 1);
				if (behavior==AIBehavior::NotMoving)
				behavior = AIBehavior::MovingRight;
			}
		}
		else
		{
			std::cout << "Jumping" << std::endl;
			if (JumpingVelocity >= 0)
			{
				if (!((TileMap*)ExternalData)->isTIleSolid(getCornerPosition(BottomRight) + sf::Vector2f(0, 4)) && !((TileMap*)ExternalData)->isTIleSolid(getCornerPosition(BottomLeft) + sf::Vector2f(0, 4)))
				{
					position += sf::Vector2f(0, 4);

				}
				else
				{
					float distance = 0;
					float DistanceFromBottomRight = abs(getCornerPosition(BottomRight).y - ((TileMap*)ExternalData)->getTIlePosition(getCornerPosition(BottomRight)).height);
					float DistanceFromBottomLeft = abs(getCornerPosition(BottomLeft).y - ((TileMap*)ExternalData)->getTIlePosition(getCornerPosition(BottomLeft)).height);
					if (DistanceFromBottomLeft < DistanceFromBottomRight)
					{
						distance = DistanceFromBottomLeft;
					}
					else
					{
						distance = DistanceFromBottomRight;
					}
					position += sf::Vector2f(0, distance - 1);
					isJumping = false;
					JumpingVelocity = 0;
				}
			}
			else
			{

				position += sf::Vector2f(0, JumpingVelocity);
				JumpingVelocity += 4;
			}
		}

		std::cout << JumpingVelocity << std::endl;
		Velocity = sf::Vector2f();
		if (position.x < 0)
		{
			position.x = 0;
		}
		if (position.y < 0)
		{
			position.y = 0;
		}
	};
	void Draw(sf::RenderWindow &renderTarget)
	{
		entity.setPosition(position);
		renderTarget.draw(entity);
	};

private:
	sf::RectangleShape entity;
	sf::Vector2f position;
	AIBehavior behavior;
	float JumpingVelocity;
	bool isJumping;
};

