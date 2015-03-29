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
	if (key == sf::Keyboard::Y&&!IsPressed)
	{
		addFireBall();
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
	for (int i = 0; i < proj.size(); i++)
	{
		proj[i]->handleRealtimeInput();
		proj[i]->Update(delta);
	}

	for (int i = 0; i < proj.size(); i++)
	{
		if (!proj[i]->ProjectileHasCollided())
		{
			for (int j = 0; j < enemies.size(); j++)
			{
				if (!enemies[j]->NeedRemoval())
					if (proj[i]->IntersectsAnotherMapEntity(enemies[j]))
					{

						enemies[j]->SetRemovalFlag(true);
						proj[i]->setHit(true);
					}

			}
		}
	}



	for (int i = 0; i < enemies.size(); i++)
	{
		if (player.IntersectsAnotherMapEntity(enemies[i]))
		{
			if (player.AttackingFlag() == true)
			{
				enemies[i]->SetRemovalFlag(true);
			};
		}
	}

	if (proj.size() != 0)
	{
		for (int i = proj.size() - 1; i >= 0; i--)
		{
			if (proj[i]->NeedRemoval() == true)
			{
				proj.erase(proj.begin() + i);
			}
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
	for (int i = 0; i < proj.size(); i++)
	{
		proj[i]->Render(RenderTarget);
	}
	RenderTarget.display();


};
void GameLevelScreen::addEnemy()
{
	enemies.push_back(new MapEntity_Enemy("EnemyAnimation.png",&tilemap,25+rand()%900,0));

}
void GameLevelScreen::addFireBall()
{
	proj.push_back(new MapEntity_Projectile_Base("FireballTravel.png", "FireballHit.png", &tilemap, player.getPosition().x, player.getPosition().y, 5.0f, 1, 0.0f));

}