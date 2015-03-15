#include "Game.h"
#include "MainMenuScreen.h"
#include "GameLevelScreen.h"

Game::~Game()
{
}
void Game::run()
{
	sf::Clock clock;
	sf::Time delta = sf::Time::Zero;
	while (gameWindow.isOpen())
	{
		delta = clock.restart();
		sf::Event event;
		while (gameWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				gameWindow.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					gameWindow.close();

				currentScreen->handleInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Escape)
					gameWindow.close();

				currentScreen->handleInput(event.key.code, false);
				break;


			}

		}
		currentScreen->Update(delta);
		currentScreen->Render(gameWindow);
	}
};
	sf::RenderWindow *Game::getWindow()
	{
		return &gameWindow;
	}
	void Game::SetScreen(int ScreenType)
	{
		switch (ScreenType)
		{
		case TitleScreen:
			currentScreen = new MainMenuScreen(this);
			break;
		case GameScreen:
			currentScreen = new GameLevelScreen(this);
			break;
		}
	};