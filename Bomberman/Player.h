#pragma once
#include "SFML\Graphics.hpp"
#include "Map.h"


using namespace sf;

class Player
{
private:
	float dx, dy;
	FloatRect rect;
	Sprite sprite;
	float currentFrame;
	Texture Mighty;
	void collision( Map &map);
public:
	Player();
	~Player();
	void set_dx(float v);
	void set_dy(float v);
	void update(float time, Map &map);
	Sprite getSprite();

};