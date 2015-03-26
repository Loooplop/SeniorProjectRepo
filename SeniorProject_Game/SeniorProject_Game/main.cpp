#include <iostream>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>
#include "Game.h"
// https://www.youtube.com/watch?v=9dzhgsVaiSo


std::vector<int> quickSort(std::vector<int> temp)
{
	int amountOfComparison = 0;
	int currentPosition = temp.size() - 1;
	while (true)
	{
		for (int i = 0; i < temp.size(); i++)
		{
			std::cout << temp[i] << std::endl;
		}
		std::cout << std::endl;

		if (currentPosition==-1)
		{
			std::cout << "Comparisons Needed: " << amountOfComparison << std::endl;
			return temp;
		}
		for (int i = currentPosition; i > 0; i--)
		{
			amountOfComparison++;
			if (temp[currentPosition] < temp[i])
			{
				int Temp = temp[currentPosition];
				temp[currentPosition] = temp[i];
				temp[i] = Temp;
			}
		}
		currentPosition--;
	}
}
int main(void)
{
	quickSort({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 });
	Game game(sf::VideoMode(800,600),"Platformer",sf::Style::Default);
	game.run();
	return 0;
}