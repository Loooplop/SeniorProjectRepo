#include <iostream>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>
#include "Game.h"
// https://www.youtube.com/watch?v=9dzhgsVaiSo
int main(void)
{
	Game game(sf::VideoMode(800,600),"Platformer",sf::Style::Titlebar|sf::Style::Close);
	game.run();
	return 0;
}