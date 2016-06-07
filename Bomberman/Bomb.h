#pragma once
#include "SFML\Graphics.hpp"


using namespace sf;

class Bomb
{
private:
	float time_planted;
	float diff_time;
	int exPower;
	Sprite sprite;
public:
	Bomb(Texture &bomb, int exPower, float timePlanted, float diffTime, int x, int y);
	void update( float time_now );
	bool isExplode( float time_now );
	void explode();
	int getExPower();
	int getBombX();
	int getBombY();
	void draw(RenderWindow &window);
	~Bomb();
};