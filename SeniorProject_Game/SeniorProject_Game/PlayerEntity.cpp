#include "PlayerEntity.h"


PlayerEntity::PlayerEntity() : Entity(0)
{

}


PlayerEntity::~PlayerEntity()
{
}
void PlayerEntity::handleInput(sf::Keyboard::Key key)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			Velocity = sf::Vector2f(-8, 0);
		}
		else
		{
			Velocity = sf::Vector2f(-5, 0);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			Velocity = sf::Vector2f(8, 0);
		}
		else
		{
			Velocity = sf::Vector2f(5, 0);
		}
    }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (isJumping == false)
			{
				isJumping = true;
				JumpingVelocity = -16.0f;
			}
		};
};

void PlayerEntity::Update(sf::Time deltaTime, void *ExternalData)
{
	if (Velocity.x > 0)
	{
		if (!((TileMap*)ExternalData)->isTIleSolid(getCornerPosition(BottomRight) + Velocity) && !((TileMap*)ExternalData)->isTIleSolid(getCornerPosition(TopRight) + Velocity))
		{
			position += Velocity;

		}
		else
		{
			float distance = 0;
			float DistanceFromBottomRight = abs(((TileMap*)ExternalData)->getTIlePosition(getCornerPosition(BottomRight)).width - getCornerPosition(BottomRight).x);
			float DistanceFromBottomLeft = abs(((TileMap*)ExternalData)->getTIlePosition(getCornerPosition(TopRight)).width - getCornerPosition(TopRight).x);
			if (DistanceFromBottomLeft < DistanceFromBottomRight)
			{
				distance = DistanceFromBottomLeft;
			}
			else
			{
				distance = DistanceFromBottomRight;
			}
			std::cout << "Velocity" << distance << std::endl;
			position += sf::Vector2f(distance - 1, 0);
		}


	}
	else if (Velocity.x < 0)
	{
		if (!((TileMap*)ExternalData)->isTIleSolid(getCornerPosition(BottomLeft) + Velocity) && !((TileMap*)ExternalData)->isTIleSolid(getCornerPosition(TopLeft) + Velocity))
		{
			position += Velocity;

		}
		else
		{
			float distance = 0;
			float DistanceFromBottomRight = abs((((TileMap*)ExternalData)->getTIlePosition(getCornerPosition(BottomLeft)).left - getCornerPosition(BottomLeft).x));
			float DistanceFromBottomLeft = abs((((TileMap*)ExternalData)->getTIlePosition(getCornerPosition(TopLeft)).left - getCornerPosition(TopLeft).x));
			if (DistanceFromBottomLeft > DistanceFromBottomRight)
			{
				distance = DistanceFromBottomLeft;
			}
			else
			{
				distance = DistanceFromBottomRight;
			}
			std::cout << "Distance: " << -distance << std::endl;
			position += sf::Vector2f(-distance + 1, 0);
		}

	}
	if (!isJumping)
	{
		if (!((TileMap*)ExternalData)->isTIleSolid(getCornerPosition(BottomRight) + sf::Vector2f(0, 4)) && !((TileMap*)ExternalData)->isTIleSolid(getCornerPosition(BottomLeft) + sf::Vector2f(0, 4)))
		{
			position += sf::Vector2f(0, 4);

		}
		else
		{
			float distance = 0;
			float DistanceFromBottomRight = abs(getCornerPosition(BottomRight).y - ((TileMap*)ExternalData)->getTIlePosition(getCornerPosition(BottomRight)).height);
			float DistanceFromBottomLeft = abs(getCornerPosition(BottomLeft).y - ((TileMap*)ExternalData)->getTIlePosition(getCornerPosition(BottomLeft)).height);
			if (DistanceFromBottomLeft < DistanceFromBottomRight)
			{
				distance = DistanceFromBottomLeft;
			}
			else
			{
				distance = DistanceFromBottomRight;
			}
			position += sf::Vector2f(0, distance - 1);
		}
	}
	else
	{
		std::cout << "Jumping" << std::endl;
		if (JumpingVelocity >= 0)
		{
			if (!((TileMap*)ExternalData)->isTIleSolid(getCornerPosition(BottomRight) + sf::Vector2f(0, 4)) && !((TileMap*)ExternalData)->isTIleSolid(getCornerPosition(BottomLeft) + sf::Vector2f(0, 4)))
			{
				position += sf::Vector2f(0, 4);

			}
			else
			{
				float distance = 0;
				float DistanceFromBottomRight = abs(getCornerPosition(BottomRight).y - ((TileMap*)ExternalData)->getTIlePosition(getCornerPosition(BottomRight)).height);
				float DistanceFromBottomLeft = abs(getCornerPosition(BottomLeft).y - ((TileMap*)ExternalData)->getTIlePosition(getCornerPosition(BottomLeft)).height);
				if (DistanceFromBottomLeft < DistanceFromBottomRight)
				{
					distance = DistanceFromBottomLeft;
				}
				else
				{
					distance = DistanceFromBottomRight;
				}
				position += sf::Vector2f(0, distance - 1);
				isJumping = false;
				JumpingVelocity = 0;
			}
		}
		else
		{

			position += sf::Vector2f(0, JumpingVelocity);
			JumpingVelocity += 4;
		}
	}

	std::cout << JumpingVelocity << std::endl;
	Velocity = sf::Vector2f();
	if (position.x < 0)
	{
		position.x = 0;
	}
	if (position.y < 0)
	{
		position.y = 0;
	}

};

void PlayerEntity::Draw(sf::RenderWindow &renderTarget)
{
	player.setPosition(position);
	renderTarget.draw(player);
};

sf::Vector2f PlayerEntity::getCornerPosition(int flag)
{
	switch (flag)
	{
	case 0:
		return position;
		break;
	case 1:
		return position + sf::Vector2f(player.getSize().x, 0);
		break;
	case 2:
		return position + player.getSize();
		break;
	case 3:
		return position + sf::Vector2f(0, player.getSize().y);
		break;
	default:
		return position;
	}

};