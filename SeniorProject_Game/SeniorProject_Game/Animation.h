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
		widthOfFrame = CollisionWidth= width;
		heightOfFrame = CollisionHeight=height;
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
	bool FlipFlag()
	{
		return isFlipped;
	}
	int getMaxFrames()
	{
		return MaxFrames;
	}
	int FrameWidth(){ return widthOfFrame; };
	int FrameHeight(){ return heightOfFrame; };
	float CollisionX()
	{
		return CollisionWidth;
	}
	float CollisionY()
	{
		return CollisionHeight;
	}
	bool hasPlayedOnce()
	{
		return PlayedOnce;
	}
	void Reset()
	{
		currentFrame = 0;
		clock.restart();
		PlayedOnce = false;
	}
	void SetCollisionManually(float CWidth, float CHeight)
	{
		this->CollisionWidth = CWidth;
		this->CollisionHeight = CHeight;
	}
private:
	sf::Texture *texture;
	sf::Sprite frame;
	sf::Clock clock;
	int MaxFrames;
	int currentFrame;
	int widthOfFrame;
	int heightOfFrame;
	float CollisionWidth;
	float CollisionHeight;
	float delayinMilliSecond;
	bool PlayedOnce;
	bool isFlipped;
};

