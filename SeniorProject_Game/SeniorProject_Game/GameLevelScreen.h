#pragma once
#include "Game.h"
#include "Screen.h"
#include "MapEntity_Player.h"
#include "MapEntity_Enemy.h"
class Game;
class GameLevelScreen :
	public Screen
{
public:
	GameLevelScreen();
	GameLevelScreen(Game *pointer);
	~GameLevelScreen();

	void addEnemy();
	void handleInput(sf::Keyboard::Key key, bool IsPressed);
	void Update(sf::Time delta);
	void Render(sf::RenderWindow &RenderTarget);
	sf::Vector2f getCenter()
	{
		return player.getPosition();
	};
	 

private:
	std::vector<MapEntity_Enemy*> enemies;
	Game *gamepointer;
	TileMap tilemap;
	MapEntity_Player player;
	sf::Text text;
	sf::Font font;
};

