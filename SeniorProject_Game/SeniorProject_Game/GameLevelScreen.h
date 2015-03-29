#pragma once
#include "Game.h"
#include "Screen.h"
#include "MapEntity_Player.h"
#include "MapEntity_Enemy.h"
#include "MapEntity_Projectile_Base.h"
class Game;
class GameLevelScreen :
	public Screen
{
public:
	GameLevelScreen();
	GameLevelScreen(Game *pointer);
	~GameLevelScreen();

	void addEnemy();
	void addFireBall();
	void handleInput(sf::Keyboard::Key key, bool IsPressed);
	void Update(sf::Time delta);
	void Render(sf::RenderWindow &RenderTarget);
	sf::Vector2f getCenter()
	{
		return player.getPosition();
	};
	 

private:
	MapEntity_Projectile_Base *fireball;
	std::vector<MapEntity_Projectile_Base*> proj;
	std::vector<MapEntity_Enemy*> enemies;
	Game *gamepointer;
	TileMap tilemap;
	MapEntity_Player player;
	sf::Text text;
	sf::Font font;
};

