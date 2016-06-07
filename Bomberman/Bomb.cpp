#pragma once
#include "Bomb.h"
#include "Map.h"
#define FIRST_FRAME IntRect(0, 0, 50, 44)
#define SECOND_FRAME IntRect(50, 0, 50, 44)
#define THIRD_FRAME IntRect(100, 0, 50, 44)


Bomb::Bomb(Texture &bomb, int exPower, float timePlanted, float diffTime, int x, int y)
{
	this->exPower = exPower;
	sprite = Sprite(bomb, FIRST_FRAME);
	sprite.setPosition(TILE_SIZE * x, TILE_SIZE * y);
	diff_time = diffTime;
	time_planted = timePlanted;
}

bool Bomb::isExplode(float time_now)
{
	return (time_now - time_planted) >= diff_time;
}

void Bomb::update(float time_now) 
{
	if ((time_now - time_planted) >= 2.0 * diff_time / 3 )
		sprite.setTextureRect(THIRD_FRAME);
	else if ((time_now - time_planted) >= diff_time / 3.0)
		sprite.setTextureRect(SECOND_FRAME);
}

void Bomb::explode()
{
	time_planted = -diff_time;   
}

int Bomb::getExPower()
{
	return exPower;
}

int Bomb::getBombX()
{
	return sprite.getPosition().x / TILE_SIZE;
}

int Bomb::getBombY()
{
	return sprite.getPosition().y / TILE_SIZE;
}

void Bomb::draw(RenderWindow &window)
{
	window.draw( sprite );
}

Bomb::~Bomb()
{
}