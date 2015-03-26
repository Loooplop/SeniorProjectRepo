#pragma once
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
class Screen
{
public:
	Screen();
	~Screen();
	virtual void handleInput(sf::Keyboard::Key key, bool IsPressed)=0;
	virtual void Update(sf::Time delta)=0;
	virtual void Render(sf::RenderWindow &RenderTarget)=0;
	virtual sf::Vector2f getCenter()=0;
};

