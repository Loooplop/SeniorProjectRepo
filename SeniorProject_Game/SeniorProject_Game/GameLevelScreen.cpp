#include "GameLevelScreen.h"


GameLevelScreen::GameLevelScreen()
{

}
GameLevelScreen::GameLevelScreen(Game *pointer)
{ 
	gamepointer = pointer;
	tilemap.LoadTileSet(25, "NewTileSet.png", "TileSet1Prop.tl");
	tilemap.LoadMapData("NewMarioFixed1.txt");
	player.setTileMap(&tilemap);

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
	player.Update(sf::Time::Zero);
};
void GameLevelScreen::Render(sf::RenderWindow &RenderTarget)
{
	RenderTarget.clear();
	tilemap.Draw(RenderTarget);
	player.Render(RenderTarget);

	RenderTarget.display();
};