#include "MapEntity_Player.h"


MapEntity_Player::MapEntity_Player()
{
	position = sf::Vector2f(50, 50);
	rect.setSize(sf::Vector2f(10, 10));
	rect.setFillColor(sf::Color::Red);
	cwidth = 10;
	cheight = 10;
	gravityConstant = 4;
}


MapEntity_Player::~MapEntity_Player()
{
}
