#include <iostream>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>
#include "TileMap.h"
#include "PlayerEntity.h"
int main(void)
{
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(800, 600), "Mario Replica", sf::Style::Default);
	window.setFramerateLimit(60);
	//window.setKeyRepeatEnabled(false);
	TileMap level;
	level.LoadTileData("C:/Users/William/Desktop/MapData.txt");

	PlayerEntity Player(0);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			};
			Player.handleInput(event.key.code);
		}

		Player.Update(sf::Time::Zero, &level);
			window.clear();
			level.Draw(&window);
			Player.Draw(window);
			window.display();
		}
	return 0;
}