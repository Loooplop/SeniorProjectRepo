#include "MapEntity_Player.h"


MapEntity_Player::MapEntity_Player()
{
	position = sf::Vector2f(50, 50);
	rect.setSize(sf::Vector2f(10, 10));
	rect.setFillColor(sf::Color::Red);
	cwidth = 10;
	cheight = 10;
	gravityAcceleration = 4.0f;
	isFalling = true;
	isJumping = false;
	initialJumpImpulse = -16.0f;
	currentJumpingMovement = 0.0f;
	JumpSlowingSpeed = 2.0f;
	MaximumSpeed = 20.0f;

}


MapEntity_Player::~MapEntity_Player()
{
}
