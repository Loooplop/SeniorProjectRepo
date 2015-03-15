#include "GameLevelScreen.h"


GameLevelScreen::GameLevelScreen()
{

}
GameLevelScreen::GameLevelScreen(Game *pointer)
{
	gamepointer = pointer;
};

GameLevelScreen::~GameLevelScreen()
{

}
void GameLevelScreen::handleInput(sf::Keyboard::Key key, bool IsPressed)
{
	if (key == sf::Keyboard::Tab)
	{
		gamepointer->SetScreen(TitleScreen);
	}
};
void GameLevelScreen::Update(sf::Time delta)
{

};
void GameLevelScreen::Render(sf::RenderWindow &RenderTarget)
{
	RenderTarget.clear();
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(10, 10));
	rect.setFillColor(sf::Color::Red);
	rect.setPosition(300, 300);
	RenderTarget.draw(rect);
	RenderTarget.display();
};