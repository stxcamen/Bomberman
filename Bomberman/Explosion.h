#pragma once
#include "Map.h"
#include "SFML\Graphics.hpp"
#include <vector>
#include "Bomb.h"


using namespace sf;

class Explosion
{
private:
	Texture tileSet;
	FloatRect rect;
public:
	Explosion(Map &map, int x, int y);
	~Explosion();
};

