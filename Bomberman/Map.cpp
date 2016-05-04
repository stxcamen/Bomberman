#pragma once
#include "SFML\Graphics.hpp"
#include "Map.h"


Map::Map( String map[H] )
{
	for (int i = 0; i < H; i++)
		map_arr[i] = map[i];
	Block.loadFromFile("textures\\block.png");
	Bricks.loadFromFile("textures\\bricks.png");
	Ground.loadFromFile("textures\\ground.png");
	Leaves.loadFromFile("textures\\leaves.png");
}

void Map::draw( RenderWindow &window)
{
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++) {
			if (map_arr[i][j] == 'B') {
				tile.setTexture(Block);
				tile.setPosition(j * TILE_SIZE, i * TILE_SIZE);
				window.draw(tile);
			}

			if (map_arr[i][j] == 'D') {
				tile.setTexture(Bricks);
				tile.setPosition(j * TILE_SIZE, i * TILE_SIZE);
				window.draw(tile);
			}

			if (map_arr[i][j] == ' ') {
				tile.setTexture(Ground);
				tile.setPosition(j * TILE_SIZE, i * TILE_SIZE);
				window.draw(tile);
			}
		}
}

void Map::drawLeaves(RenderWindow &window)
{
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
			if (map_arr[i][j] == 'L') {
				tile.setTexture(Leaves);
				tile.setPosition(j * TILE_SIZE * K, i * TILE_SIZE * K);
				window.draw(tile);
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
