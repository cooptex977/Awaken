#include "GameObjects.h"

Player::Player(sf::Vector2f position)
{
	sprite.setPosition(position);
	jumpspeed = -10.0f;
	gravity = .75f;
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