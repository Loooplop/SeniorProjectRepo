#pragma once
#include "Game.h"
#include "Screen.h"

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

	 

private:
	Game *gamepointer;
	//Tilemap tilemap;
};

