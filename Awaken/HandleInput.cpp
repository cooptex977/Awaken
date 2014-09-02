#include "Main.h"
#include "GameObjects.h"
void khandle(Player* player)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		exit(0);
	}
	player->movespeed = 3.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		//move up
		if (player->isTouchingGround)
		{
			player->vel.y = player->jumpspeed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			//move right
			player->source.y = Right;
			player->vel.x = player->movespeed;
			player->lastdir = IdleRight;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			//move left
			player->source.y = Left;
			player->vel.x = player->movespeed * -1;
			player->lastdir = IdleLeft;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		//move left
		player->source.y = Left;
		player->vel.x = player->movespeed * -1;
		player->lastdir = IdleLeft;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		//move right
		player->source.y = Right;
		player->vel.x = player->movespeed;
		player->lastdir = IdleRight;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		//pause
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		//ability 1
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		//ability 2
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		//ability 3
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		//ability 4
	}
	else
	{
		player->source.y = player->lastdir;
		player->vel.x = 0;
	}
}
