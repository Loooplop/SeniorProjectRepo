#include "MapEntity_Player.h"


MapEntity_Player::MapEntity_Player()
{
	position = sf::Vector2f(700, 430);
	aniTexture.loadFromFile("playersprites.png");
	animation.SetTexture(&aniTexture,36,45);
	cwidth = animation.FrameWidth();
	PANICNUMBER(cwidth)
	cheight = animation.FrameHeight();
	animation.SetDelay(0.5f);
	gravityAcceleration = 4.0f;
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
