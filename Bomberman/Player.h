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
	void setPowerUp(char mapTile);
	void collision( Map &map, Player &enemy);
	void bombCollision(Map &map, Player &enemy);
public:
	Player(Texture &mighty, int x, int y);
	void setdx(float v);
	void setdy(float v);
	void setLastBomb(FloatRect lastBomb);
	bool isReloaded(float currentTime);
	float getBombTimer();
	int getExPower();
	int getPlayerX();
	int getPlayerY();
	void bombPlanted(Map &map, float timeNow);
	void update(float dt, Map &map, Player &enemy);
	bool isLose();
	bool isWinner();
	void draw(RenderWindow &window);
	~Player();
};