#pragma once
#include "Player.h"


Player::Player()
{
	Mighty.loadFromFile("textures\\Mighty.png");
	playerSprite.setTexture(Mighty);
	playerSprite.setTextureRect(IntRect(0, 0, 42, 64));
	playerRect = FloatRect(TILE_SIZE, TILE_SIZE, 48, 64);
	last_planted = -diffTime;
	dx = dy = 0;
	currentFrame = 0;
}

void Player::setPhysRect()
{
	
}

void Player::collision(Map &map)
{
	for (int i = (playerRect.top + 42) / TILE_SIZE; i < (playerRect.top + playerRect.height - 6) / TILE_SIZE; i++)
		for (int j = (playerRect.left + 6) / TILE_SIZE; j < (playerRect.left + playerRect.width - 6) / TILE_SIZE; j++)
			if ((map.getTile(i, j) == 'D') || (map.getTile(i, j) == 'B') || (map.getTile(i, j) == 'Q'))
				if (dx > 0)
					playerRect.left = j * TILE_SIZE - playerRect.width + 4;
				else if (dx < 0)
					playerRect.left = TILE_SIZE * (j + 1) - 4;
				else if (dy > 0)
					playerRect.top = i * TILE_SIZE - playerRect.height + 4;
				else if (dy < 0)
					playerRect.top = TILE_SIZE * (i + 1) - 40;
}

void Player::bombCollision(Map &map)
{
	if ((FloatRect(playerRect.left + 6, playerRect.top + 42, playerRect.width - 6, playerRect.height - 6).intersects(lastBomb) == 0)
		&& (lastBomb.top != 0))
	{
		map.setTile('D', lastBomb.top / TILE_SIZE, lastBomb.left / TILE_SIZE);
		lastBomb = FloatRect(0, 0, 0, 0);
	}
}

void Player::bombPlanted(Map &map, float time_now)
{
	last_planted = time_now;
	lastBomb = FloatRect(getPlayerX() * TILE_SIZE, getPlayerY() * TILE_SIZE, TILE_SIZE, TILE_SIZE);
}

void Player::update(float dt, Map &map)
{
	playerRect.left += dx * dt;
	playerRect.top  += dy * dt;

	currentFrame += 0.005 * dt;
	bombCollision(map);

	if ( dx ) 
	{
		if (currentFrame > 7) 
			currentFrame -= 7;

		if (dx > 0) 
			playerSprite.setTextureRect(IntRect(48 + 48 * (int)currentFrame, 64, -48, 60));
		else 
			playerSprite.setTextureRect(IntRect(48 * (int)currentFrame, 64, 48, 60));
		
		collision(map);
		dx = 0;
	}
	else if (dy > 0)
	{
		if (currentFrame > 5)
			currentFrame -= 5;
		playerSprite.setTextureRect(IntRect(42 * (int)currentFrame, 0, 42, 64));
		collision(map);
		dy = 0;
	} 
	else if( dy < 0)
	{
		if (currentFrame > 6)
			currentFrame -= 6;
		playerSprite.setTextureRect(IntRect(48 * (int)currentFrame, 126, 48, 62));
		collision(map);
		dy = 0;
	}

	playerSprite.setPosition(playerRect.left, playerRect.top);
	
}

void Player::set_dx(float v)
{
	dx = v;
}

void Player::set_dy(float v)
{
	dy = v;
}

void Player::setDiffTime( float diff_time)
{
	diffTime = diff_time;
}

bool Player::isReloaded(float time_now)
{
	return ((time_now - last_planted) >= diffTime) && 
		FloatRect(playerRect.left + 6, playerRect.top + 42, playerRect.width - 6, playerRect.height - 6).intersects(lastBomb) == 0;
	
}

void Player::setBombDiffTime( float bomb_difftime)
{
	bombDiffTime = bomb_difftime;
}

float Player::getBombDiffTime()
{
	return bombDiffTime;
}

int Player::getPlayerX()
{
	return ( playerRect.left + playerRect.width / 2 ) / TILE_SIZE;
}

int Player::getPlayerY()
{
	return ( playerRect.top + 4 * playerRect.height / 5 ) / TILE_SIZE;
}

void Player::draw(RenderWindow &window)
{
	window.draw( playerSprite );
}

Player::~Player()
{
}
