#pragma once
#include "SFML\Graphics.hpp"
#include "Map.h"


using namespace sf;

class Player
{
private:
	float dx, dy;
	float last_planted;
	float diffTime = 100.0;
	float bombDiffTime = 7000.0;
	int explosionPower;
	FloatRect playerRect, physRect;
	Sprite playerSprite;
	float currentFrame;
	Texture Mighty;
	FloatRect lastBomb;
	void collision( Map &map);
	void bombCollision(Map &map);
public:
	Player();
	~Player();
	void setPhysRect();
	void set_dx(float v);
	void set_dy(float v);
	bool isReloaded(float currentTime);
	void setDiffTime( float diffTime);
	void setBombDiffTime( float BombDiffTime);
	float getBombDiffTime();
	int getPlayerX();
	int getPlayerY();
	void bombPlanted(Map &map, float time_now);
	void update(float dt, Map &map);
	void draw(RenderWindow &window);
};