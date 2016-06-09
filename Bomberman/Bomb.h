#pragma once
#include "SFML\Graphics.hpp"
#include "Map.h"


class Bomb
{
private:
	float timePlanted;
	float bombTimer;
	int exPower;
	sf::Sprite sprite;
public:
	Bomb(sf::Texture &bomb, int exPower, float timePlanted, float bombTimer, int x, int y);
	void update( float timeNow );
	bool isExplode( float timeNow );
	void explode();
	int getExPower();
	int getBombX();
	int getBombY();
	void draw(sf::RenderWindow &window);
	~Bomb();
};