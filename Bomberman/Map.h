#pragma once
#include "SFML\Graphics.hpp"

#define TILE_SIZE 64
#define HEIGHT 14
#define WIDTH 25


class Map
{
private:
	sf::String  mapArray[HEIGHT];
	sf::Texture mapTexture;
	sf::Sprite sprite;
public:
	Map(sf::String mapArray[HEIGHT], sf::Texture &map);
	~Map();
	void draw( sf::RenderWindow &window);
	void drawLeaves( sf::RenderWindow &window);
	void setTile(char ch, int i, int j);
	char getTile(int i, int j);
};