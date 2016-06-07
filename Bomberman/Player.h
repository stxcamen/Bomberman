#pragma once
#include "SFML\Graphics.hpp"
#include "Map.h"


using namespace sf;

class Player
{
private:
	bool isWon;
	bool isAlive;
	float dx, dy;
	float lastPlanted;
	float diffTime = 5000.0;
	float bombDiffTime = 3000.0;
	int explosionPower = 1;
	FloatRect physRect;
	Sprite playerSprite;
	float currentFrame;
	FloatRect lastBomb;
	void collision( Map &map, bool enemyDied);
	void bombCollision(Map &map);
public:
	Player(Texture &mighty, int x, int y);
	void set_dx(float v);
	void set_dy(float v);
	void setExPower( int exPower);
	bool isReloaded(float currentTime);
	void setDiffTime( float diffTime);
	void setBombDiffTime( float BombDiffTime);
	float getBombDiffTime();
	int getExPower();
	int getPlayerX();
	int getPlayerY();
	void bombPlanted(Map &map, float time_now);
	void update(float dt, Map &map, bool enemyDied);
	bool isLose();
	bool isWinner();
	void draw(RenderWindow &window);
	~Player();
};