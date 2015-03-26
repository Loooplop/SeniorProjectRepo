#include "GameLevelScreen.h"
#include <assert.h>

GameLevelScreen::GameLevelScreen()
{

}
GameLevelScreen::GameLevelScreen(Game *pointer)
{ 
	gamepointer = pointer;
	tilemap.LoadTileSet(50, "NewTileSet.png", "TileSet1Prop.tl");
	tilemap.LoadMapData("NewMarioFixed1.txt");
	player.setTileMap(&tilemap);
	assert(font.loadFromFile("Blazed.ttf") == true);
	text.setFont(font);
	text.setScale(0.1,0.1);
	text.setColor(sf::Color::Black);
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
	player.handleEventInput(key, IsPressed);
};
void GameLevelScreen::Update(sf::Time delta)
{
	player.handleRealtimeInput();
	player.Update(delta);
};
void GameLevelScreen::Render(sf::RenderWindow &RenderTarget)
{
	RenderTarget.clear();
	tilemap.Draw(RenderTarget);
	player.Render(RenderTarget);
	text.setPosition(player.getPosition()+sf::Vector2f(0,-10));
	text.setString(std::to_string(((int)player.getPosition().x)/tilemap.getTileSize()));
	RenderTarget.draw(text);


	text.setString(std::string("Player is Grounded: ")+std::to_string(player.Grounded()));
	text.setPosition(player.getPosition() + sf::Vector2f(0, -50));
	RenderTarget.draw(text);

	text.setString(std::string("Player is Falling: ") + std::to_string(player.Falling()));
	text.setPosition(player.getPosition() + sf::Vector2f(0, -60));
	RenderTarget.draw(text);
	text.setString(std::string("Player is Jumping: ") + std::to_string(player.Jummping()));
	text.setPosition(player.getPosition() + sf::Vector2f(0, -70));
	RenderTarget.draw(text);

	RenderTarget.display();
};