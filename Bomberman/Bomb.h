#pragma once
#include "SFML\Graphics.hpp"


using namespace sf;

class Bomb
{
private:
	float time_planted;
	float diff_time;
	Texture bomb;
	Sprite sprite;
	FloatRect rect;
public:
	Bomb( float timePlanted, float diffTime, int x, int y);
	void update( float dt);
	bool isExplode( float time_now );
	int getBombX();
	int getBombY();
	void draw(RenderWindow &window);
	~Bomb();
};

