#include <iostream>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>
#include "TileMap.h"

int main(void)
{
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(800, 600), "Mario Replica", sf::Style::Default);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
	TileMap level;
	sf::RectangleShape player;
	player.setFillColor(sf::Color::Red);
	player.setSize(sf::Vector2f(10, 10));
	player.setPosition(500, 0);
	level.LoadTileData("C:/Users/William/Desktop/MapData.txt");
	sf::Vector2f Velocity(0, 2);
	sf::Vector2f Hori(0, 0);
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
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			Hori = sf::Vector2f(0.2, 0);
		}
		else
		{
			
		}

		Velocity += Hori;
		if (level.isTIleSolid(player.getPosition() + player.getSize()+(sf::Vector2f(0,Velocity.y))))
		{
			sf::IntRect TilePosition= level.getTIlePosition(player.getPosition() + player.getSize() + Velocity);

			Velocity = sf::Vector2f(0, (TilePosition.top - (player.getPosition() + player.getSize()).y));
		}
		else
		{
			sf::Vector2f();
		}

		player.move(Velocity);
			window.clear();
			level.Draw(&window);
			window.draw(player);
			window.display();
		}
	return 0;
}