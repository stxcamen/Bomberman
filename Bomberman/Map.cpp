#pragma once
#include "Map.h"

#define GROUND IntRect(2 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE)
#define BLOCK IntRect(0, 0, TILE_SIZE, TILE_SIZE)
#define BRICK IntRect(TILE_SIZE, 0, TILE_SIZE, TILE_SIZE)
#define LEAVES IntRect(3 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE)
#define POWER_UP IntRect(((int)mapArray[i][j] - (int)'0' - 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE, TILE_SIZE)


using namespace sf;

Map::Map( String mapArray[HEIGHT], Texture &mapTexture)
{
	for (int i = 0; i < HEIGHT; i++)
		this->mapArray[i] = mapArray[i];
	this->mapTexture = mapTexture;
}

void Map::draw( RenderWindow &window)
{
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++) 
			if (mapArray[i][j] == 'B') 
			{
				sprite = Sprite(mapTexture, BLOCK);
				sprite.setPosition(j * TILE_SIZE, i * TILE_SIZE);
				window.draw(sprite);
			} 
			else if (mapArray[i][j] == 'D') 
			{
				sprite = Sprite(mapTexture, BRICK);
				sprite.setPosition(j * TILE_SIZE, i * TILE_SIZE);
				window.draw(sprite);
			} 
			else if ((mapArray[i][j] == ' ') || (mapArray[i][j] == 'Q') || (mapArray[i][j] == 'E') || (mapArray[i][j] == 'F') || (mapArray[i][j] == 'L'))
			{
				sprite = Sprite(mapTexture, GROUND);
				sprite.setPosition(j * TILE_SIZE, i * TILE_SIZE);
				window.draw(sprite);
			}
			else if (mapArray[i][j] >= '1' && mapArray[i][j] <= '6')
			{
				sprite = Sprite(mapTexture, POWER_UP);
				sprite.setPosition(j * TILE_SIZE, i * TILE_SIZE);
				window.draw(sprite);
			}

			
}

void Map::drawLeaves(RenderWindow &window)
{
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
			if (mapArray[i][j] == 'L') 
			{
				sprite = Sprite(mapTexture, LEAVES);
				sprite.setPosition(j * TILE_SIZE, i * TILE_SIZE);
				window.draw(sprite);
			}
}

char Map::getTile(int i, int j)
{
	return mapArray[i][j];
}

void Map::setTile(char ch, int i, int j)
{
	mapArray[i][j] = ch;
}

Map::~Map()
{
}