#pragma once
#include "Map.h"
#define GROUND IntRect(128, 0, 64, 64)
#define BLOCK IntRect(0, 0, 64, 64)
#define BRICK IntRect(64, 0, 64, 64)
#define LEAVES IntRect(192, 0, 64, 64)


Map::Map( String map_arr[H], Texture &mapTexture)
{
	for (int i = 0; i < H; i++)
		this->map_arr[i] = map_arr[i];
	this->mapTexture = mapTexture;
}

void Map::draw( RenderWindow &window)
{
	for (int i = 0; i < H; i++)
		for (int j = 0; j < WIDTH; j++) 
			if (map_arr[i][j] == 'B') 
			{
				sprite = Sprite(mapTexture, BLOCK);
				sprite.setPosition(j * TILE_SIZE, i * TILE_SIZE);
				window.draw(sprite);
			} 
			else if (map_arr[i][j] == 'D') 
			{
				sprite = Sprite(mapTexture, BRICK);
				sprite.setPosition(j * TILE_SIZE, i * TILE_SIZE);
				window.draw(sprite);
			} 
			else if ((map_arr[i][j] == ' ') || (map_arr[i][j] == 'Q') || (map_arr[i][j] == 'E') || (map_arr[i][j] == 'F'))
			{
				sprite = Sprite(mapTexture, GROUND);
				sprite.setPosition(j * TILE_SIZE, i * TILE_SIZE);
				window.draw(sprite);
			}
}

void Map::drawLeaves(RenderWindow &window)
{
	for (int i = 0; i < H; i++)
		for (int j = 0; j < WIDTH; j++)
			if (map_arr[i][j] == '*') 
			{
				sprite = Sprite(mapTexture, LEAVES);
				sprite.setPosition(j * TILE_SIZE, i * TILE_SIZE);
				window.draw(sprite);
			}
}

char Map::getTile(int i, int j)
{
	return map_arr[i][j];
}

void Map::setTile(char ch, int i, int j)
{
	map_arr[i][j] = ch;
}

Map::~Map()
{
}