#pragma once
#include "SFML\Graphics.hpp"
#define TILE_SIZE 64
#define H 14
#define WIDTH 25


using namespace sf;

class Map
{
private:
	String  map_arr[H];
	Texture mapTexture;
	Sprite sprite;
public:
	Map(String map_arr[H], Texture &map);
	~Map();
	void draw( RenderWindow &window);
	void drawLeaves( RenderWindow &window);
	void setTile(char ch, int i, int j);
	char getTile(int i, int j);
};