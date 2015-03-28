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
	addEnemy();
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
	if (key == sf::Keyboard::I&&!IsPressed)
	{
		addEnemy();
	}
	player.handleEventInput(key, IsPressed);
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->handleEventInput(key, IsPressed);
	}
};
void GameLevelScreen::Update(sf::Time delta)
{
	player.handleRealtimeInput();
	player.Update(delta);
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->handleRealtimeInput();
		enemies[i]->Update(delta);
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		if (player.IntersectsAnotherMapEntity(enemies[i]))
		{
			enemies[i]->SetRemovalFlag(true);
		}
	}


	if (enemies.size() != 0)
	{
		for (int i = enemies.size() - 1; i >= 0; i--)
		{
			if (enemies[i]->NeedRemoval() == true)
			{
				enemies.erase(enemies.begin() + i);
			}
		}
	}
	
};
void GameLevelScreen::Render(sf::RenderWindow &RenderTarget)
{
	RenderTarget.clear();
	tilemap.Draw(RenderTarget);
	player.Render(RenderTarget);
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Render(RenderTarget);
	}
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
void GameLevelScreen::addEnemy()
{
	enemies.push_back(new MapEntity_Enemy("EnemyAnimation.png",&tilemap,25+rand()%800,0));

}