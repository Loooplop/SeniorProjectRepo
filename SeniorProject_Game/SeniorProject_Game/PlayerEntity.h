#pragma once
#include "Entity.h"
#include "TileMap.h"
#include <iostream>
#define TopLeft 0
#define TopRight 1
#define BottomRight 2
#define BottomLeft 3
class PlayerEntity :
	public Entity
{
public:
	PlayerEntity(int id) : Entity(id)
	{
		player.setSize(sf::Vector2f(10, 10));
		player.setFillColor(sf::Color::Magenta);
		position = sf::Vector2f(400, 0);
	};
	PlayerEntity();
	~PlayerEntity();

	void handleInput(sf::Keyboard::Key key)
	{
		switch (key)
		{
		case sf::Keyboard::Left:
			Velocity += sf::Vector2f(-3, 0);
			break;
		case sf::Keyboard::Right:
			Velocity += sf::Vector2f(3, 0);
			break;
		}

	};
	void Update(sf::Time deltaTime, void *ExternalData)
	{
		if (Velocity.x > 0)
		{
			if (
				((TileMap*)ExternalData)->isTIleSolid(getCornerPosition(TopRight)) && 
				((TileMap*)ExternalData)->isTIleSolid(getCornerPosition(BottomRight))
			   )
			{
				Velocity = sf::Vector2f();
			}
		}
		else if (Velocity.x < 0)
		{
			if (
				((TileMap*)ExternalData)->isTIleSolid(getCornerPosition(TopLeft)) ||
				((TileMap*)ExternalData)->isTIleSolid(getCornerPosition(BottomLeft))
				)
			{
				Velocity = sf::Vector2f();
			}
		}
		position += Velocity;
		if (!((TileMap*)ExternalData)->isTIleSolid(getCornerPosition(BottomRight) + sf::Vector2f(0, 4)) && !((TileMap*)ExternalData)->isTIleSolid(getCornerPosition(BottomLeft) + sf::Vector2f(0, 4)))
		{
			position += sf::Vector2f(0, 4);

		}
		else
		{
			int pos = ((TileMap*)ExternalData)->getTIlePosition(getCornerPosition(BottomRight)).height;
			int distance = getCornerPosition(BottomRight).y;
			distance = abs(distance-pos);
			int DistanceFromBottomRight = abs(getCornerPosition(BottomRight).y - pos);
			int DistanceFromBottomLeft = abs(getCornerPosition(BottomRight).y - ((TileMap*)ExternalData)->getTIlePosition(getCornerPosition(BottomLeft)).height);
			if (DistanceFromBottomLeft < DistanceFromBottomRight)
			{
				distance = DistanceFromBottomLeft;
			}
			else
			{
				distance = DistanceFromBottomRight;
			}

			std::cout << distance << std::endl;
			if (distance <= 4)
			{
				std::cout << distance << std::endl;
				position += sf::Vector2f(0, distance-1);
			}
			else
			{
				
				std::cout << distance << std::endl;
			}
		}
		Velocity = sf::Vector2f();

	};
	void Draw(sf::RenderWindow &renderTarget)
	{
		player.setPosition(position);
		renderTarget.draw(player);
	};
	sf::Vector2f getCornerPosition(int flag)
	{
		switch (flag)
		{
		case 0:
			return position;
			break;
		case 1:
			return position + sf::Vector2f(player.getSize().x, 0);
			break;
		case 2:
			return position + player.getSize();
			break;
		case 3:
			return position + sf::Vector2f(0, player.getSize().y);
			break;

		}

	}

private:
	sf::RectangleShape player;
	sf::Vector2f position;
};

