#pragma once
#include <SFML\Graphics.hpp>
class Entity
{
public:
	Entity(int EntityID);
	~Entity();
	virtual void handleInput(sf::Keyboard::Key key)=0;
	virtual void Update(sf::Time deltaTime, void *ExternalData)=0;
	virtual void Draw(sf::RenderWindow &renderTarget)=0;

protected:
	sf::Vector2f Velocity;
	int ID;
};

