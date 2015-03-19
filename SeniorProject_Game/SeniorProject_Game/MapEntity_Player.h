#pragma once
#include "MapEntity_Base.h"
class MapEntity_Player :
	public MapEntity_Base
{
public:
	MapEntity_Player();
	~MapEntity_Player();
	void handleInput(sf::Keyboard::Key key, bool isPressed)
	{
		velocity = sf::Vector2f(0, 1);
	};
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

