#include "MapEntity_Enemy.h"


MapEntity_Enemy::MapEntity_Enemy()
{
	position = sf::Vector2f(800, 430);
	tex.loadFromFile("EnemyAnimation.png");
	animation.SetTexture(&tex, 30, 40);
	animation.SetDelay(0.05f);
	cwidth = animation.FrameWidth();
	cheight = animation.FrameHeight();
	isJumping = false;
	isGrounded = false;
	initialJumpImpulse = -30.0f;
	currentJumpingMovement = 0.0f;
	JumpSlowingSpeed = 1.8f;
	MaximumSpeed = 20.0f;
	MovementSpeed = 3.0f;
	gravityAcceleration = 4.0f;
	velocity.x = MovementSpeed;
	MovingRight = true;
}


MapEntity_Enemy::~MapEntity_Enemy()
{
}
