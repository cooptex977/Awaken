#include "GameObjects.h"

sf::Sprite GameObject::getSprite()
{
	return sprite;
}

void GameObject::setSprite(sf::Sprite newsprite)
{
	sprite = newsprite;
}

void GameObject::move(int x, int y)
{
	sprite.move(x, y);
}

void GameObject::move(sf::Vector2f offset)
{
	sprite.move(offset);
}

sf::FloatRect GameObject::getGlobalBounds()
{
	return sprite.getGlobalBounds();
}

void GameObject::setTexture(const sf::Texture &texture)
{
	sprite.setTexture(texture);
}

Player::Player(sf::Vector2f position)
{
	pos = position;
	sprite.setPosition(pos);
}

void Player::move(sf::Vector2f& newpos)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		//move up
		if (isTouchingGround)
		{
			vel.y = gravity;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			//move right
			source.y = Right;
			vel.x = gravity;
			lastdir = IdleRight;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			//move left
			source.y = Left;
			vel.x = -gravity;
			lastdir = IdleLeft;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		//move left
		source.y = Left;
		vel.x = -gravity;
		lastdir = IdleLeft;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		//move right
		source.y = Right;
		vel.x = gravity;
		lastdir = IdleRight;
	}
	else
	{
		source.y = lastdir;
		vel.x = 0;
	}
}

sf::Sprite Player::getCurrentSprite()
{
	frameCounter += frameSpeed * clock.restart().asSeconds();
	if (frameCounter >= switchFrame)
	{
		frameCounter = 0;
		source.x++;
		if (source.x * 32 >= texture.getSize().x)
			source.x = 0;
	}
	sprite.setTextureRect(sf::IntRect(source.x * 32, source.y * 32, 32, 32));

	return sprite;
}

sf::Vector2f Player::getPosition()
{
	return sprite.getPosition();
}

void Player::setPosition(sf::Vector2f newpos)
{
	prevx = sprite.getPosition().x;
	prevy = sprite.getPosition().y;
	sprite.setPosition(newpos);
}

void Player::setPosition(int x, int y)
{
	prevx = sprite.getPosition().x;
	prevy = sprite.getPosition().y;
	sprite.setPosition(x, y);
}