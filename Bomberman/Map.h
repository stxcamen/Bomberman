#pragma once
#define TILE_SIZE 32
#define H 13
#define W 15
#define K 2

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

//enum TileType { BLOCK, GROUND, BRICKS, LEAVES };