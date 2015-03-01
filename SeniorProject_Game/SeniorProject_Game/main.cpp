#include <iostream>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>




void loadTileMap(const char *filepath, std::vector<sf::Vector3i> &TileInformation,sf::Vector3i &TileMapInfo, sf::Texture *TileMapTexture)
{
	std::string str;

	std::ifstream openfile(filepath);
	int size, X, Y;
	if (openfile.is_open())
	{
		std::getline(openfile, str);
		TileMapTexture->loadFromFile(str);
		openfile >> size >> X >> Y;
		TileMapInfo = sf::Vector3i(size, X, Y);
		while (std::getline(openfile, str,','))
		{
			char *TileInfo = (char*)str.c_str();
			int x = atoi(&TileInfo[0]);
			int y = atoi(&TileInfo[2]);
			int c = atoi(&TileInfo[4]);
			TileInformation.push_back(sf::Vector3i(x, y, c));
		}

	}
	openfile.close();
}

int getCellIndex(sf::Vector2f position, sf::Vector3i TileMapInfo)
{

	sf::Vector2i CellIndex = sf::Vector2i((int)position.x / TileMapInfo.x, (int)position.y / TileMapInfo.x);
	std::cout << CellIndex.x<<" "<<CellIndex.y << std::endl;
	return CellIndex.y*TileMapInfo.y + CellIndex.x;


}
int main(void)
{
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(800, 600), "Mario Replica", sf::Style::Default);
	window.setFramerateLimit(60);
	sf::RectangleShape player;
	player.setFillColor(sf::Color::Red);
	player.setSize(sf::Vector2f(10, 10));


	std::vector<sf::Vector3i> marioTileData;
	sf::Vector3i data;
	sf::Texture Texture;
	loadTileMap("C:/Users/William/Desktop/MapData.txt",marioTileData,data,&Texture);
	sf::Sprite Tile;
	Tile.setTexture(Texture);
	std::cout << data.y << std::endl;
	sf::Vector2f velocity(0,0);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
			else if (event.key.code == sf::Keyboard::Right)
			{
				if (marioTileData[getCellIndex(player.getPosition() + sf::Vector2f(player.getSize().x + 2, 0), data)].z != 1)
				{
					player.move(2, 0);
				}
			}
			else if (event.key.code == sf::Keyboard::Left)
			{
				if (marioTileData[getCellIndex(player.getPosition()-sf::Vector2f(-2,0), data)].z != 1)
				{
					player.move(0, -2);
				};
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				marioTileData[getCellIndex(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y), data)]=sf::Vector3i(1,0,1);
			}

		}
		

		if (marioTileData[getCellIndex(player.getPosition() + player.getSize(), data)].z != 1 && marioTileData[getCellIndex(player.getPosition() + sf::Vector2f(0,player.getSize().y), data)].z != 1)
		{
			player.move(0, 1);
		};






		window.clear();
		int TileCounter = 0;
		for (int y = 0; y < data.z; y++)
		{
			for (int x = 0; x < data.y; x++)
			{
				Tile.setTextureRect(sf::IntRect(data.x*marioTileData[TileCounter].x, data.x*marioTileData[TileCounter].y,data.x,data.x));
				Tile.setPosition(data.x*x, data.x*y);
				window.draw(Tile);
				TileCounter++;
			}
		}
		window.draw(player);
		window.display();
	}
	return 0;
}