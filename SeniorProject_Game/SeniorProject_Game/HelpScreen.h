#pragma once
#include "Screen.h"
class Game;
class HelpScreen :
	public Screen
{
public:
	HelpScreen(Game *pointer);
	~HelpScreen();
	void handleInput(sf::Keyboard::Key key, bool IsPressed);
	void Update(sf::Time delta);
	void Render(sf::RenderWindow &RenderTarget);
	sf::Vector2f getCenter();

private:
	sf::Texture helpTexture;
	sf::Sprite helpSprite;
	Game *game;
};

