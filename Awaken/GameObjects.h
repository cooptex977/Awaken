#pragma once
#include "Main.h"

class GameObject
{
public:
	sf::Texture texture;
	sf::Sprite getSprite();
	void setSprite(sf::Sprite newsprite);
	virtual void move(int x, int y);
	virtual void move(sf::Vector2f offset);
	sf::FloatRect getGlobalBounds();
	void setTexture(const sf::Texture &texture);
protected:
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

class Player : public GameObject
{
public:
	sf::Sprite getCurrentSprite();
	sf::Vector2f getPosition();
	void Player::move(sf::Vector2f& newpos);
	void setPosition(sf::Vector2f newpos);
	void setPosition(int x, int y);
	Player(sf::Vector2f position);
	int hp, energy, lastdir = IdleRight;
	sf::Vector2f vel;
	sf::Vector2i source = sf::Vector2i(1, IdleRight);
	sf::Clock clock;
	int prevx;
	int prevy;
	bool isTouchingGround;
	float frameCounter = 0.0f, switchFrame = 100.0f, frameSpeed = 500.0f;
	const int gravity = 10;
private:
	sf::Vector2f pos;
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