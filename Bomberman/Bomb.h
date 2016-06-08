#pragma once
#include "SFML\Graphics.hpp"


using namespace sf;

class Bomb
{
private:
	float timePlanted;
	float bombTimer;
	int exPower;
	Sprite sprite;
public:
	Bomb(Texture &bomb, int exPower, float timePlanted, float bombTimer, int x, int y);
	void update( float timeNow );
	bool isExplode( float timeNow );
	void explode();
	int getExPower();
	int getBombX();
	int getBombY();
	void draw(RenderWindow &window);
	~Bomb();
};