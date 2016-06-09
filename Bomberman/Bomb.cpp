#pragma once
#include "Bomb.h"

#define FIRST_FRAME IntRect(0, 0, 50, 44)
#define SECOND_FRAME IntRect(50, 0, 50, 44)
#define THIRD_FRAME IntRect(100, 0, 50, 44)


using namespace sf;

Bomb::Bomb(Texture &bomb, int exPower, float timePlanted, float bombTimer, int x, int y)
{
	this->exPower = exPower;
	sprite = Sprite(bomb, FIRST_FRAME);
	sprite.setPosition(TILE_SIZE * x, TILE_SIZE * y);
	this->bombTimer = bombTimer;
	this->timePlanted = timePlanted;
}

bool Bomb::isExplode(float timeNow)
{
	return (timeNow - timePlanted) >= bombTimer;
}

void Bomb::update(float timeNow) 
{
	if ((timeNow - timePlanted) >= 2.0 * bombTimer / 3 )
		sprite.setTextureRect(THIRD_FRAME);
	else if ((timeNow - timePlanted) >= bombTimer / 3.0)
		sprite.setTextureRect(SECOND_FRAME);
}

void Bomb::explode()
{
	timePlanted = -bombTimer;   
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