#include "TileMap.h"


TileMap::TileMap()
{
	TileData = std::vector<sf::Vector3i>();
	TileMapData = sf::Vector3i();
	TileMapTexture = sf::Texture();
	TileMapSprite = sf::Sprite();
}


TileMap::~TileMap()
{
}
void TileMap::LoadTileData(const char *filepath)
{
	std::string str;

	std::ifstream openfile(filepath);
	int size, X, Y;
	if (openfile.is_open())
	{
		std::getline(openfile, str);
		TileMapTexture.loadFromFile(str);
		TileMapSprite.setTexture(TileMapTexture);
		openfile >> size >> X >> Y;
		TileMapData = sf::Vector3i(size, X, Y);
		while (std::getline(openfile, str, ','))
		{
			char *TileInfo = (char*)str.c_str();
			int x = atoi(&TileInfo[0]);
			int y = atoi(&TileInfo[2]);
			int c = atoi(&TileInfo[4]);
			TileData.push_back(sf::Vector3i(x, y, c));
		}

	}
	openfile.close();
};
void TileMap::Draw(sf::RenderWindow *renderTarget)
{
	int TileCounter = 0;
	for (int y = 0; y < TileMapData.z; y++)
	{
		for (int x = 0; x < TileMapData.y; x++)
		{
			TileMapSprite.setTextureRect(sf::IntRect(TileMapData.x*TileData[TileCounter].x, TileMapData.x*TileData[TileCounter].y, TileMapData.x, TileMapData.x));
			TileMapSprite.setPosition(TileMapData.x*x, TileMapData.x*y);
			renderTarget->draw(TileMapSprite);
			TileCounter++;
		}
	}
};
int TileMap::VectorToIndex(sf::Vector2f position)
{
	sf::Vector2i CellIndex = sf::Vector2i((int)position.x / TileMapData.x, (int)position.y / TileMapData.x);
	return CellIndex.y*TileMapData.y + CellIndex.x;
}
void TileMap::ChangeTexture(const char *textureFilePath)
{
	TileMapTexture.loadFromFile(textureFilePath);
	TileMapSprite.setTexture(TileMapTexture);
};
void TileMap::ChangeTileData(std::vector<sf::Vector3i> newData)
{
	TileData = newData;
};
bool TileMap::isTIleSolid(sf::Vector2f positionToCheck)
{
	return TileData[VectorToIndex(positionToCheck)].z == 1;
};
bool TileMap::isTileSolid(int XPosition, int YPosition)
{
	return TileData[VectorToIndex(sf::Vector2f(XPosition,YPosition))].z == 1;
};
sf::Sprite *TileMap::getTileMapSprite()
{
	return &TileMapSprite;
};
sf::Texture *TileMap::getTileMapTexture()
{
	return &TileMapTexture;
};
