#pragma once
#include "Map.h"
#include <vector>
#include <iostream>
#include <iterator>
#include "Bomb.h"


using namespace sf;
using namespace std;

class Explosion
{
private:
	vector <Sprite*> spriteVector;
	vector <Sprite*>::iterator spriteIt;
	int exPower;
	float startTime;
	const float exTime = 512.0;
	bool fireSpread(Texture &brick, Texture &fire, Map &map, vector <Bomb*> &bombVector, int dir, int x, int y, int i);
public:
	Explosion(Texture &brick, Texture &fire, Map &map, vector <Bomb*> &bombVector, int exPower, float time_now, int x, int y);
	void update( float time_now );
	void draw(RenderWindow &window);
	bool isInactive(Map &map, float time_now);
};