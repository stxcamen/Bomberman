#pragma once
#include "SFML\Graphics.hpp"
#define TILE_SIZE 64
#define H 14
#define W 19


using namespace sf;

class Map
{
private:
	String  map_arr[H];
	Texture Block;
	Texture Ground;
	Texture Bricks;
	Texture Leaves;
	Sprite tile;
public:
	Map( String map[H] );
	~Map();
	void draw( RenderWindow &window);
	void drawLeaves( RenderWindow &window);
	void setTile(char ch, int i, int j);
	char getTile(int i, int j);
};