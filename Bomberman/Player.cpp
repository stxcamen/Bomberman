#pragma once
#include "Player.h"
#define GO_LEFT IntRect(48 * (int)currentFrame, 64, 48, 60)
#define GO_RIGHT IntRect(48 + 48 * (int)currentFrame, 64, -48, 60)
#define GO_UP IntRect(48 * (int)currentFrame, 126, 48, 62)
#define GO_DOWN IntRect(42 * (int)currentFrame, 0, 42, 64)
#define VICTORY IntRect(45 * (int)currentFrame, 188, 45, 60)
#define DEATH IntRect(TILE_SIZE * (int)currentFrame, 249, 64, 64)
#define VICTORY_FRAMES 5
#define DEATH_FRAMES 10
#define RL_FRAMES 7 
#define DOWN_FRAMES 5
#define UP_FRAMES 6


Player::Player(Texture &mighty, int x, int y)
{
	isWon = false;
	isAlive = true;
	lastPlanted = -diffTime;
	dx = dy = 0;
	currentFrame = 0;
	playerSprite = Sprite( mighty, GO_DOWN );
	physRect = FloatRect(x * TILE_SIZE + 14, y * TILE_SIZE + 42, 20, 16);
}

void Player::bombCollision(Map &map)
{
	if (!physRect.intersects(lastBomb) && (lastBomb.top != 0))
	{
		map.setTile('Q', lastBomb.top / TILE_SIZE, lastBomb.left / TILE_SIZE);
		lastBomb = FloatRect(0, 0, 0, 0);
	}
}

void Player::collision(Map &map, bool enemyLose)
{
	if (enemyLose)
	{
		isWon = true;
		currentFrame = 0;
	}
	else for (int i = physRect.top / TILE_SIZE; i < (physRect.top + physRect.height) / TILE_SIZE; i++)
		for (int j = physRect.left / TILE_SIZE; j < (physRect.left + physRect.width) / TILE_SIZE; j++)
			if ((map.getTile(i, j) == 'D') || (map.getTile(i, j) == 'B') || (map.getTile(i, j) == 'Q'))
			{
				if (dx > 0)
					physRect.left = j * TILE_SIZE - physRect.width;
				else if (dx < 0)
					physRect.left = TILE_SIZE * (j + 1);
				else if (dy > 0)
					physRect.top = i * TILE_SIZE - physRect.height;
				else if (dy < 0)
					physRect.top = TILE_SIZE * (i + 1);
			}
			else if ((map.getTile(i, j) == 'F') || (map.getTile(i, j) == 'E'))
			{
				isAlive = false;
				currentFrame = 0;
			}
	
	bombCollision(map);
}

void Player::update(float dt, Map &map, bool enemyLose)
{
	currentFrame += 0.005 * dt;

	if (isWon)
	{
		if (currentFrame < VICTORY_FRAMES)
			playerSprite.setTextureRect(VICTORY);
	}
	else if (!isAlive) 
	{
		if (currentFrame < DEATH_FRAMES)
			playerSprite.setTextureRect(DEATH);
	}
	else if (dx)
	{
		physRect.left += dx * dt;

		if (currentFrame > RL_FRAMES)
			currentFrame -= RL_FRAMES;

		if (dx > 0)
			playerSprite.setTextureRect(GO_RIGHT);
		else
			playerSprite.setTextureRect(GO_LEFT);
	}
	else if (dy > 0)
	{
		physRect.top += dy * dt;
		if (currentFrame > DOWN_FRAMES)
			currentFrame -= DOWN_FRAMES;
		playerSprite.setTextureRect(GO_DOWN);
	}
	else if (dy < 0)
	{
		physRect.top += dy * dt;
		if (currentFrame > UP_FRAMES)
			currentFrame -= UP_FRAMES;
		playerSprite.setTextureRect(GO_UP);
	}

	if( isAlive && !isWon)
		collision(map, enemyLose);
	
	playerSprite.setPosition(physRect.left - 14, physRect.top - 42);
	dx = dy = 0;
}

void Player::bombPlanted(Map &map, float time_now)
{
	lastPlanted = time_now;
	lastBomb = FloatRect(getPlayerX() * TILE_SIZE, getPlayerY() * TILE_SIZE, TILE_SIZE, TILE_SIZE);
}

void Player::set_dx(float v)
{
	dx = v;
}

void Player::set_dy(float v)
{
	dy = v;
}

void Player::setExPower(int exPower)
{
	explosionPower = exPower;
}

void Player::setDiffTime( float diff_time)
{
	diffTime = diff_time;
}

bool Player::isReloaded(float time_now)
{
	return ((time_now - lastPlanted) >= diffTime) &&  !physRect.intersects(lastBomb) && isAlive;
}

void Player::setBombDiffTime( float bomb_difftime)
{
	bombDiffTime = bomb_difftime;
}

float Player::getBombDiffTime()
{
	return bombDiffTime;
}

int Player::getExPower()
{
	return explosionPower;
}

int Player::getPlayerX()
{
	return ( physRect.left + physRect.width / 2 ) / TILE_SIZE;
}

int Player::getPlayerY()
{
	return ( physRect.top + physRect.height / 2 ) / TILE_SIZE;
}

bool Player::isLose()
{
	return !isAlive && (currentFrame > DEATH_FRAMES);
}

bool Player::isWinner()
{
	return isWon && (currentFrame > 3 * VICTORY_FRAMES);
}

void Player::draw(RenderWindow &window)
{
	window.draw( playerSprite );
}

Player::~Player()
{
}