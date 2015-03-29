#pragma once
#include "MapEntity_Base.h"
#include "Animation.h"
class MapEntity_Projectile_Base :
	public MapEntity_Base
{
public:
	MapEntity_Projectile_Base(const char *FlyingTextureFilename,const char *HittingFileName,TileMap *tileMap,float SpawnX,float SpawnY,float Speed,float AngleX,float AngleY)
	{

		aniTraveling.loadFromFile("FireballTravel.png");
		Traveling.SetTexture(&aniTraveling,25,25);
		Traveling.SetDelay(0.1f);
		cwidth = Traveling.CollisionX();
		cheight = Traveling.CollisionY();

		aniOnHit.loadFromFile(HittingFileName);
		Hitting.SetTexture(&aniOnHit, 25, 25);
		Hitting.SetDelay(0.3f);
		Hitting.SetCollisionManually(Hitting.CollisionX() / 2, Hitting.CollisionY());

		this->tilemap = tileMap;
		position = sf::Vector2f(SpawnX, SpawnY);
		MovementSpeed = Speed;
		anglex = AngleX;
		angley = AngleY;
		hasHit = false;

		currentanimation = &Traveling;
	};
	~MapEntity_Projectile_Base();
	void handleEventInput(sf::Keyboard::Key key, bool isPressed)
	{

	};
	void handleRealtimeInput()
	{

	};
	void Update(sf::Time delta)
	{
		currentanimation->Update();
		velocity = sf::Vector2f(MovementSpeed*anglex, MovementSpeed*angley);
		CollisionWithTileMap();
		position = temp;

		if (!hasHit)
		{
			if (velocity.x == 0)
			{
				hasHit = true;
				currentanimation = &Hitting;
				currentanimation->Reset();
				cwidth = currentanimation->CollisionX();
				cheight = currentanimation->CollisionY();
			}
		}
		else
		{
			if (currentanimation->hasPlayedOnce())
			{
				tobeRemoved = true;
			}

		}
	};
	void setHit(bool flag)
	{
		hasHit = flag;
	}
    void Render(sf::RenderWindow &RenderTarget)
	{
		currentanimation->DrawFrame(RenderTarget, position);
	};
	bool NeedRemoval()
	{
		return tobeRemoved;
	}
	bool ProjectileHasCollided()
	{
		return hasHit;
	}
private:
	float anglex, angley;
	sf::Texture aniTraveling, aniOnHit;
	Animation Traveling, Hitting;
	Animation *currentanimation;
	bool hasHit;
	bool tobeRemoved;
};

