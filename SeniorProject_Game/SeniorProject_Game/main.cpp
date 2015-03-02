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

	level.LoadTileData("C:/Users/William/Desktop/MapData.txt");
	sf::Vector2f gravity(0, 1);
	sf::Vector2f JunpVelocity(0, 0);
	sf::Vector2f HorVelocity;
	bool isJumping = false;
	sf::Vector2f FinalVelocity(0, 0);

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				};

				if (event.key.code == sf::Keyboard::Space)
				{
					if (isJumping == false)
					{
						JunpVelocity = sf::Vector2f(0, -14);
						isJumping = true;
					}
				}
			}
			HorVelocity = sf::Vector2f();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (!level.isTIleSolid(player.getPosition() + sf::Vector2f(-1, 0)) && !level.isTIleSolid(player.getPosition() + sf::Vector2f(-1, player.getSize().y-1)))
				{
					HorVelocity = sf::Vector2f(-1, 0);
				};
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (!level.isTIleSolid(player.getPosition() + sf::Vector2f(player.getSize().x + 1, 0)) && !level.isTIleSolid(player.getPosition() + sf::Vector2f(player.getSize().x + 1, player.getSize().y-1)))
				{
					HorVelocity = sf::Vector2f(1, 0);
				}
			}


			if (!level.isTIleSolid(player.getPosition() + player.getSize()) && !level.isTIleSolid(player.getPosition() + sf::Vector2f(0,player.getSize().y-1)))
			{
				gravity = sf::Vector2f(0,2);
			}
			else
			{
				gravity = sf::Vector2f(0,0);
			}


			if (isJumping)
			{
				JunpVelocity += gravity;
				if (JunpVelocity.y >0)
				{
					isJumping = false;
				}
			}
			else
			{
				JunpVelocity = sf::Vector2f();
			}
			std::cout << isJumping << std::endl;
			FinalVelocity = gravity+JunpVelocity+HorVelocity;
			player.move(FinalVelocity);
			window.clear();
			level.Draw(&window);
			window.draw(player);
			window.display();
		}
	return 0;
}