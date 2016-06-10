#pragma once
#include "Player.h"

#define INIT_EX_POWER 1
#define INIT_SPEED 1.5
#define INIT_BOMB_TIMER 3000.0
#define INIT_RELOADING_TIME 3500.0
#define RELOADING_TIME_LIMIT 500.0
#define BOMB_TIMER_LIMIT 1000.0
#define TIME_UP 500.0
#define ANIMATION_SPEED 0.005
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


using namespace sf;

Player::Player(Texture &mighty, int x, int y)
{
	isWon = false;
	isAlive = true;
	speed = INIT_SPEED;
	explosionPower = INIT_EX_POWER;
	reloadingTime = INIT_RELOADING_TIME;
	bombTimer = INIT_BOMB_TIMER;
	lastPlanted = -reloadingTime;
	lastBomb = FloatRect(0, 0, 0, 0);
	dx = dy = 0.0;
	currentFrame = 0.0;
	playerSprite = Sprite(mighty, GO_DOWN);
	physRect = FloatRect(x * TILE_SIZE + 14, y * TILE_SIZE + 42, 20, 16);
}

void Player::setPowerUp(char mapTile)
{
	if(mapTile == '6')
	{
		explosionPower = INIT_EX_POWER;
		speed = INIT_SPEED;
		bombTimer = INIT_BOMB_TIMER;
		reloadingTime = INIT_RELOADING_TIME;
	}
	else if (mapTile == '5')
		speed /= 2;
	else if (mapTile == '4')
		speed += INIT_SPEED / 2;
	else if (mapTile == '3')
		explosionPower += 1;
	else if (mapTile = '2')
	{
		if (reloadingTime > RELOADING_TIME_LIMIT)
			reloadingTime -= 3 * TIME_UP;
	}
	else if (mapTile == '1')
	{
		if (bombTimer > BOMB_TIMER_LIMIT)
			bombTimer -= TIME_UP;
	}
}

void Player::bombCollision(Map &map, Player &enemy)
{
	if (!physRect.intersects(lastBomb) && (lastBomb.top != 0))
	{
		if (lastBomb.intersects(FloatRect(enemy.getPlayerX() * TILE_SIZE, enemy.getPlayerY() * TILE_SIZE, TILE_SIZE, TILE_SIZE)))
			enemy.setLastBomb(lastBomb);
		else
			map.setTile('Q', lastBomb.top / TILE_SIZE, lastBomb.left / TILE_SIZE);
		lastBomb = FloatRect(0, 0, 0, 0);
	}
}

void Player::collision(Map &map, Player &enemy)
{
	char mapTile;

	if(enemy.isLose())
	{
		isWon = true;
		currentFrame = 0;
		speed = INIT_SPEED;
	}
	else for (int i = physRect.top / TILE_SIZE; i < (physRect.top + physRect.height) / TILE_SIZE; i++)
		for (int j = physRect.left / TILE_SIZE; j < (physRect.left + physRect.width) / TILE_SIZE; j++)
		{
			mapTile = map.getTile(i, j);

			if ((mapTile == 'D') || (mapTile == 'B') || (mapTile == 'Q'))
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
			else if (mapTile >= '1' && mapTile <= '6')
			{
				map.setTile(' ', i, j);
				setPowerUp(mapTile);
			}
			else if ((mapTile == 'F') || (mapTile == 'E'))
			{
				isAlive = false;
				currentFrame = 0;
				speed = INIT_SPEED;
			}
		}
	bombCollision(map, enemy);
}

void Player::update(float dt, Map &map, Player &enemy)
{
	currentFrame += ANIMATION_SPEED * speed * dt;

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
		physRect.left += dx * speed * dt;

		if (currentFrame > RL_FRAMES)
			currentFrame -= RL_FRAMES;

		if (dx > 0)
			playerSprite.setTextureRect(GO_RIGHT);
		else
			playerSprite.setTextureRect(GO_LEFT);
	}
	else if (dy > 0)
	{
		physRect.top += dy * speed * dt;
		if (currentFrame > DOWN_FRAMES)
			currentFrame -= DOWN_FRAMES;
		playerSprite.setTextureRect(GO_DOWN);
	}
	else if (dy < 0)
	{
		physRect.top += dy * speed * dt;
		if (currentFrame > UP_FRAMES)
			currentFrame -= UP_FRAMES;
		playerSprite.setTextureRect(GO_UP);
	}

	if( isAlive && !isWon)
		collision(map, enemy);
	
	playerSprite.setPosition(physRect.left - 14, physRect.top - 42);
	dx = dy = 0;
}

void Player::setLastBomb(FloatRect lastBomb)
{
	this->lastBomb = lastBomb;
}

void Player::bombPlanted(Map &map, float timeNow)
{
	lastPlanted = timeNow;
	lastBomb = FloatRect(getPlayerX() * TILE_SIZE, getPlayerY() * TILE_SIZE, TILE_SIZE, TILE_SIZE);
}

void Player::setdx(float v)
{
	dx = v;
}

void Player::setdy(float v)
{
	dy = v;
}

bool Player::isReloaded(float timeNow)
{
	return ((timeNow - lastPlanted) >= reloadingTime) &&  !physRect.intersects(lastBomb) && isAlive;
}

float Player::getBombTimer()
{
	return bombTimer;
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