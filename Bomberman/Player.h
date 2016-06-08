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
	float speed;
	float lastPlanted;
	float reloadingTime;
	float bombTimer;
	int explosionPower;
	FloatRect physRect;
	Sprite playerSprite;
	float currentFrame;
	FloatRect lastBomb;
	void setPowerUp(Map &map, char mapTile);
	void collision( Map &map, bool enemyDied);
	void bombCollision(Map &map);
public:
	Player(Texture &mighty, int x, int y);
	void setdx(float v);
	void setdy(float v);
	bool isReloaded(float currentTime);
	float getBombTimer();
	int getExPower();
	int getPlayerX();
	int getPlayerY();
	void bombPlanted(Map &map, float timeNow);
	void update(float dt, Map &map, bool enemyDied);
	bool isLose();
	bool isWinner();
	void draw(RenderWindow &window);
	~Player();
};