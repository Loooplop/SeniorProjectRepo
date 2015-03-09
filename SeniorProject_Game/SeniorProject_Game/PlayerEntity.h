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
		isJumping = false;
		JumpingVelocity = 0;
	};
	PlayerEntity();
	~PlayerEntity();

	void handleInput(sf::Keyboard::Key key);
	void Update(sf::Time deltaTime, void *ExternalData);
	void Draw(sf::RenderWindow &renderTarget);
	sf::Vector2f getCornerPosition(int flag);

private:
	float JumpingVelocity;
	bool isJumping;
	sf::RectangleShape player;
	sf::Vector2f position;
};


