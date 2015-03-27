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

	void handleInput(sf::Keyboard::Key key, bool IsPressed);
	void Update(sf::Time delta);
	void Render(sf::RenderWindow &RenderTarget);
	sf::Vector2f getCenter()
	{
		return player.getPosition();
	};
	 

private:
	Game *gamepointer;
	TileMap tilemap;
	MapEntity_Player player;
	MapEntity_Enemy enemy;
	sf::Text text;
	sf::Font font;
};

