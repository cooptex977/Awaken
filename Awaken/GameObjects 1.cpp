#include "GameObjects.h"

Player::Player(sf::Vector2f position)
{
	sprite.setPosition(position);
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

void Player::update(std::vector<Tile*> tiles, std::vector<Enemy*>)
{
	vel.y += gravity;
	if (vel != sf::Vector2f(0, 0))
		sprite.move(vel);
	for each (Tile* tile in tiles)
		if (tile->sprite.getGlobalBounds().intersects(sprite.getGlobalBounds()))
			sprite.setPosition(sprite.getPosition().x, tile->sprite.getPosition().y - sprite.getOrigin().y);
}