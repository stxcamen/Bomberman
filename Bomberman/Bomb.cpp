#pragma once
#include "Bomb.h"
#include "Map.h"


Bomb::Bomb(float timePlanted, float diffTime, int x, int y)
{
	bomb.loadFromFile("textures\\bomb.png");
	sprite.setTexture(bomb);
	sprite.setTextureRect(IntRect(0, 0, 50, 44));
	rect = FloatRect(TILE_SIZE * x, TILE_SIZE * y, 50, 44);
	diff_time = diffTime;
	time_planted = timePlanted;
}

bool Bomb::isExplode(float time_now)
{
	return (time_now - time_planted) >= diff_time;
}

void Bomb::update(float time_now) 
{
	if ((time_now - time_planted) >= 2.0*diff_time / 3)
		sprite.setTextureRect(IntRect(100, 0, 50, 44));
	else if ((time_now - time_planted) >= diff_time / 3.0)
		sprite.setTextureRect(IntRect(50, 0, 50, 44));

	sprite.setPosition( rect.left, rect.top);
}

int Bomb::getBombX()
{
	return rect.left / TILE_SIZE;
}

int Bomb::getBombY()
{
	return rect.top / TILE_SIZE;
}

void Bomb::draw(RenderWindow &window)
{
	window.draw( sprite );
}

Bomb::~Bomb()
{
}