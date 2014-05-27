#pragma once
#include "Main.h"

class GameObject
{
public:
	sf::Texture texture;
	sf::Sprite sprite;
};

class Tile : public GameObject
{
public:
	Tile(sf::Vector2f pos)
	{
		sprite.setPosition(pos);
		if (texture.loadFromFile("assets/images/tile.png"))
			sprite.setTexture(texture);
		else
			MessageBox(0, L"Error: failed to load asset", L"Error", MB_ABORTRETRYIGNORE);
	}
};

class Enemy : public GameObject
{
public:
	Enemy(sf::Vector2f position)
	{
		initialize();
		sprite.setPosition(position);
	}
	virtual void initialize();
	virtual void update(Player* player);
	int hp;
	float frameCounter = 0, switchFrame = 100, frameSpeed = 500, movespeed;
	sf::Vector2f vel;
};

class Player : public GameObject
{
public:
	sf::Sprite getCurrentSprite();
	void update(std::vector<Tile*>);
	Player(sf::Vector2f position);
	int hp, energy, lastdir = IdleRight;
	sf::Vector2f vel;
	sf::Vector2i source = sf::Vector2i(1, IdleRight);
	sf::Clock clock;
	bool canJump;
	float frameCounter = 0, switchFrame = 100, frameSpeed = 500, movespeed, jumpspeed = -10.0f, gravity = 1;
};

#endif