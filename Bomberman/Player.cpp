#pragma once
#include "Player.h"


Player::Player()
{
	Mighty.loadFromFile("textures\\Mighty.png");
	sprite.setTexture(Mighty);
	sprite.setTextureRect(IntRect(0, 0, 21, 32));
	rect = FloatRect(TILE_SIZE * 7, TILE_SIZE * 6, 21, 32);
	dx = dy = 0;
	currentFrame = 0;
}

void Player::collision( Map &map)
{
	for (int i = (rect.top + 21) / TILE_SIZE; i < (rect.top + rect.height - 3) / TILE_SIZE; i++)
		for (int j = (rect.left + 3) / TILE_SIZE; j < (rect.left + rect.width - 3) / TILE_SIZE; j++) {
			if ((map.getTile(i, j) == 'D') || (map.getTile(i, j) == 'B')) {
				if (dx > 0) {
					rect.left = j * TILE_SIZE - rect.width + 2;
					return;
				}
				if (dx < 0) {
					rect.left = TILE_SIZE * (j + 1) - 2;
					return;
				}
				if (dy > 0) {
					rect.top = i * TILE_SIZE - rect.height + 2;
					return;
				}
				if (dy < 0) {
					rect.top = TILE_SIZE * (i + 1) - 20;
					return;
				}
			}
		}
}

void Player::update(float time, Map &map)
{
	rect.left += dx * time;

	rect.top += dy * time;

	currentFrame += 0.005 * time;

	if (dx != 0) {
		if (currentFrame > 7) currentFrame -= 7;

		if (dx > 0) sprite.setTextureRect(IntRect(24 + 24 * (int)currentFrame, 32, -24, 30));
		if (dx < 0) sprite.setTextureRect(IntRect(24 * (int)currentFrame, 32, 24, 30));
		collision(map);
		dx = 0;
	}

	if (dy != 0) {
		if (currentFrame > 5)
			currentFrame -= 5;
		if (dy > 0) sprite.setTextureRect(IntRect(21 * (int)currentFrame, 0, 21, 32));
		if (dy < 0) sprite.setTextureRect(IntRect(24 * (int)currentFrame, 63, 24, 31));
		collision(map);
		dy = 0;
	}

	sprite.setPosition(rect.left, rect.top);
}

void Player::set_dx(float v)
{
	dx = v;
}

void Player::set_dy(float v)
{
	dy = v;
}

Sprite Player::getSprite()
{
	return sprite;
}

Player::~Player()
{
}
