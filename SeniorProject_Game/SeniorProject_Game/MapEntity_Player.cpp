#include "MapEntity_Player.h"


MapEntity_Player::MapEntity_Player()
{
	position = sf::Vector2f(700, 430);
	gravityAcceleration = 4.0f;
	isFalling = true;
	isJumping = false;
	isGrounded = false;
	isAttacking = false;
	initialJumpImpulse = -18.0f;
	currentJumpingMovement = 0.0f;
	JumpSlowingSpeed = 1.8f;
	MaximumSpeed = 20.0f;
	MovementSpeed = 6.0f;
	maxFireballs = 5;
	fireBallShot = 0;



	aniTextureIdle.loadFromFile("playersprites.png");
	animationIdle.SetTexture(&aniTextureIdle, 36, 45);
	animationIdle.SetDelay(0.5f);

	aniTextureWalking.loadFromFile("playerWalkingAnimation.png");
	animationWalking.SetTexture(&aniTextureWalking, 36, 45);
	animationWalking.SetDelay(0.1f);

	aniTextureAttacking.loadFromFile("playerAttackingAnimation.png");
	animationAttacking.SetTexture(&aniTextureAttacking, 45, 45);
	animationAttacking.SetCollisionManually(36, 45);
	animationAttacking.SetDelay(0.3f);


	currentanimation = &animationIdle;
	cwidth = currentanimation->CollisionX();
	cheight = currentanimation->CollisionY();
	
	JumpSoundData.loadFromFile("Jump.wav");
	JumpSound.setBuffer(JumpSoundData);
	JumpSound.setLoop(false);

	ExplosionSoundData.loadFromFile("Explosion.wav");
	ExplosionSound.setBuffer(ExplosionSoundData);
	ExplosionSound.setLoop(false);

	AttackSoundData.loadFromFile("Attack.ogg");
	AttackSound.setBuffer(AttackSoundData);
	AttackSound.setLoop(false);
}


MapEntity_Player::~MapEntity_Player()
{
}
