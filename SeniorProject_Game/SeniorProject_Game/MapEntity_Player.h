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
		
		velocity = sf::Vector2f(MovementSpeed, gravityConstant);
	};
	void handleRealtimeInput()
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			MovementSpeed = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{

			position.y = 50;
			MovementSpeed = 0;
		}
		else
		{
			MovementSpeed = 0;
		}

		velocity = sf::Vector2f(MovementSpeed, gravityConstant);
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

