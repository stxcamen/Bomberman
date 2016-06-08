#pragma once
#include "SFML\Graphics.hpp"
#define TILE_SIZE 64
#define HEIGHT 14
#define WIDTH 25


using namespace sf;

class Map
{
private:
	String  mapArray[HEIGHT];
	Texture mapTexture;
	Sprite sprite;
public:
	Map(String mapArray[HEIGHT], Texture &map);
	~Map();
	void draw( RenderWindow &window);
	void drawLeaves( RenderWindow &window);
	void setTile(char ch, int i, int j);
	char getTile(int i, int j);
};