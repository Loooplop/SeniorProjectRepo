#include "MainMenuScreen.h"
#include "Game.h"
#include <assert.h>
#define AmountOfChoices 3
MainMenuScreen::MainMenuScreen(Game* pointer)
{
	gamePointer = pointer;
	gamePointer->getWindow()->setKeyRepeatEnabled(false);

	assert(font.loadFromFile("Blazed.ttf")==true);
	text.setFont(font);
	text.setScale(3, 3);

	MenuTexts = new std::string[AmountOfChoices];
	MenuTexts[0] = "Start";
	MenuTexts[1] = "Controls";
	MenuTexts[2] = "Exit";

	CurrentChoice = 0;
};
MainMenuScreen::MainMenuScreen()
{
	assert(font.loadFromFile("Blazed.ttf") == true);
	text.setFont(font);
	text.setScale(3, 3);

	MenuTexts = new std::string[AmountOfChoices];
	MenuTexts[0] = "Start";
	MenuTexts[1] = "Controls";
	MenuTexts[2] = "Exit";

	CurrentChoice = 0;
};

MainMenuScreen::~MainMenuScreen()
{


};

void MainMenuScreen::handleInput(sf::Keyboard::Key key, bool IsPressed)
{
	if (key == sf::Keyboard::Down&&IsPressed==true)
	{
		CurrentChoice = (CurrentChoice + 1) % AmountOfChoices;
	}
	else if (key == sf::Keyboard::Up&&IsPressed == true)
	{
		if (CurrentChoice == 0)
		{
			CurrentChoice = AmountOfChoices - 1;
		}
		else
		{
			CurrentChoice--;
		}
	}
	else if (key == sf::Keyboard::Space&&IsPressed == true)
	{
		switch (CurrentChoice)
		{
		case 0:
			gamePointer->SetScreen(GameScreen);
			break;
		case 1:
			gamePointer->SetScreen(HelpInfoScreen);
			break;
		case 2:
			gamePointer->getWindow()->close();
			break;

		}
	}

}
void MainMenuScreen::Update(sf::Time delta)
{


}
void MainMenuScreen::Render(sf::RenderWindow &RenderTarget)
{
	RenderTarget.clear();

	text.setScale(3, 3);
	for (int i = 0; i < AmountOfChoices;i++)
	{
		if (i == CurrentChoice)
		{
			text.setColor(sf::Color::Green);
		}
		else
		{
			text.setColor(sf::Color::White);
		}

		text.setString(MenuTexts[i]);
		text.setPosition(-220 + gamePointer->getWindow()->getSize().x / 2, 50+(i * 120));
		RenderTarget.draw(text);

	}
	text.setScale(0.75f, 0.75f);
	text.setColor(sf::Color::White);
	text.setString("Stick Brawl @ William Chantrill Paul");
	text.setPosition(210, 575);
	RenderTarget.draw(text);
	RenderTarget.display();

}