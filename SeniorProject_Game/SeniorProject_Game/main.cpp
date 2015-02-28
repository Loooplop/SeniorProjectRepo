#include <iostream>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
int main(void)
{
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(800, 600), "Mario Replica", sf::Style::Default);

	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
		}
		window.clear(sf::Color::Red);

		window.display();
	}
	return 0;
}