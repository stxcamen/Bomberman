#pragma once
#include "Map.h"
#include <vector>
#include <iostream>
#include <iterator>
#include "Bomb.h"


class Explosion
{
private:
	std::vector <sf::Sprite*> spriteVector;
	std::vector <sf::Sprite*>::iterator spriteIt;
	int exPower;
	float startTime;
	const float exTime = 512.0;
	bool fireSpread(sf::Texture &brick, sf::Texture &fire, Map &map, std::vector <Bomb*> &bombVector, int dir, int x, int y, int i);
	char powerUpGenerate();
public:
	Explosion(sf::Texture &brick, sf::Texture &fire, Map &map, std::vector <Bomb*> &bombVector, int exPower, float timeNow, int x, int y);
	void update( float timeNow );
	void draw(sf::RenderWindow &window);
	bool isInactive(Map &map, float timeNow);
	~Explosion();
};