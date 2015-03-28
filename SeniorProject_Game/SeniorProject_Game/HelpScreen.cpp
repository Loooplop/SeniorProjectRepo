#include "HelpScreen.h"
#include "Game.h"

HelpScreen::HelpScreen(Game *pointer)
{
	game = pointer;
	helpTexture.loadFromFile("HelpScreen.png");
	helpSprite.setTexture(helpTexture);
}


HelpScreen::~HelpScreen()
{

}
void HelpScreen::handleInput(sf::Keyboard::Key key, bool IsPressed)
{
	if (key == sf::Keyboard::Tab&&IsPressed)
	{
		game->SetScreen(TitleScreen);
	}
};
void HelpScreen::Update(sf::Time delta)
{

};
void HelpScreen::Render(sf::RenderWindow &RenderTarget)
{
	RenderTarget.clear();
	RenderTarget.draw(helpSprite);
	RenderTarget.display();
};
sf::Vector2f HelpScreen::getCenter()
{
	return sf::Vector2f(400, 300);
};
