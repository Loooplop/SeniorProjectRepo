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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			MovementSpeed = 5;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			MovementSpeed = -5;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{

			position.y = 50;
			MovementSpeed = 0;
			isFalling = true;
		}
		else
		{
			MovementSpeed = 0;
		}

		if (isFalling)
		{
			PANICNUMBER(2)
			velocity = sf::Vector2f(MovementSpeed, gravityConstant);
		}
		else
		{
			PANICNUMBER(1)
			velocity = sf::Vector2f(MovementSpeed, 0);
		};
		position.x += 0.5f;
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

