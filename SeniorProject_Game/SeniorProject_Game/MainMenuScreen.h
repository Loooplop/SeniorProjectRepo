#pragma once
#include "Screen.h"
#include <string>

class Game;
class MainMenuScreen :
	public Screen
{
public:
	MainMenuScreen(Game* pointer);
	MainMenuScreen();
	~MainMenuScreen();

	void handleInput(sf::Keyboard::Key key, bool IsPressed);
	void Update(sf::Time delta);
	void Render(sf::RenderWindow &RenderTarget);
private:
	Game *gamePointer;
	sf::Font font;
	sf::Text text;
	std::string *MenuTexts;
	int CurrentChoice;
};

