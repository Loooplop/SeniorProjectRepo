#pragma once
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Screen.h"
#define TitleScreen 0
#define GameScreen 1
class Game
{
public:
	Game(sf::VideoMode mode, char* WindowTitle,int style) :gameWindow(mode,WindowTitle,style)
	{
		SetScreen(TitleScreen);
		gameWindow.setFramerateLimit(60);
		view.setSize(gameWindow.getSize().x, gameWindow.getSize().y);
	};
	~Game();
	void run();
	sf::RenderWindow *getWindow();
	void SetScreen(int ScreenType);
private:
	Screen *currentScreen;
	sf::RenderWindow gameWindow;
	sf::View view;
};