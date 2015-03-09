#include <iostream>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>
#include "TileMap.h"
#include "PlayerEntity.h"
#include "AIEntity.h"
int main(void)
{


	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(800, 600), "Mario Replica", sf::Style::Default);
	window.setFramerateLimit(60);
	TileMap level;
	level.LoadTileData("C:/Users/William/Desktop/MapData.txt");
	sf::View view;
	view.setSize(800, 600);
	PlayerEntity Player(0);
	AIEntity enemy(0);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			};
			
		}
		Player.handleInput(sf::Keyboard::Escape);
		enemy.handleInput(sf::Keyboard::Escape);
		Player.Update(sf::Time::Zero, &level);
		enemy.Update(sf::Time::Zero, &level);

		if (Player.getCornerPosition(0).x >= 400)
		{
			view.setCenter(sf::Vector2f(Player.getCornerPosition(0).x, window.getSize().y / 2.0f));
		}
		else
		{
			view.setCenter(sf::Vector2f(400, window.getSize().y / 2.0f));
		}

		window.setView(view);
			window.clear();
			level.Draw(&window);
			Player.Draw(window);
			enemy.Draw(window);
			window.display();
		}
	return 0;
}