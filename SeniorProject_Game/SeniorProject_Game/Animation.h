#pragma once
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>
class Animation
{
public:
	Animation();
	~Animation();
	void SetTexture(sf::Texture *tex, int width, int height)
	{
		texture = tex;
		MaxFrames=-1+texture->getSize().x / width;
		std::cout << MaxFrames << "Max FRAMES" << std::endl;
		widthOfFrame = width;
		heightOfFrame = height;
		frame.setTexture(*texture);
	}
	void SetDelay(float delay)
	{
		delayinMilliSecond = delay;
		clock.restart();
	}
	void Update()
	{
		if (clock.getElapsedTime().asSeconds() >= delayinMilliSecond)
		{
			if (currentFrame < MaxFrames)
			{
				currentFrame++;
				PlayedOnce = true;
			}
			else
			{
				currentFrame = 0;
				
			}
			clock.restart();
		}
	}
	void DrawFrame(sf::RenderWindow &RenderTarget, sf::Vector2f position)
	{
		if (!isFlipped)
		{
		frame.setTextureRect(sf::IntRect(currentFrame*widthOfFrame, 0, widthOfFrame, heightOfFrame));
		}
		else
		{
			frame.setTextureRect(sf::IntRect((currentFrame+1)*widthOfFrame, 0, -widthOfFrame, heightOfFrame));
		}
		frame.setPosition(position);
		RenderTarget.draw(frame);
	}
	void SetFlip(bool flipped)
	{
		isFlipped = flipped;
	}
	int FrameWidth(){ return widthOfFrame; };
	int FrameHeight(){ return heightOfFrame; };
private:
	sf::Texture *texture;
	sf::Sprite frame;
	sf::Clock clock;
	int MaxFrames;
	int currentFrame;
	int widthOfFrame;
	int heightOfFrame;
	float delayinMilliSecond;
	bool PlayedOnce;
	bool isFlipped;
};

