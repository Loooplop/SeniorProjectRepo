#include "MapEntity_Player.h"


MapEntity_Player::MapEntity_Player()
{
	position = sf::Vector2f(700, 430);
	rect.setSize(sf::Vector2f(10, 20));
	rect.setFillColor(sf::Color::Black);
	cwidth = 10;
	cheight = 20;
	gravityAcceleration = 8.0f;
	isFalling = true;
	isJumping = false;
	isGrounded = false;
	initialJumpImpulse = -30.0f;
	currentJumpingMovement = 0.0f;
	JumpSlowingSpeed = 1.8f;
	MaximumSpeed = 20.0f;
	MovementSpeed = 5.0f;

}


MapEntity_Player::~MapEntity_Player()
{
}
