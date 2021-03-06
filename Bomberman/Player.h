#pragma once
#include "SFML\Graphics.hpp"
#include "Map.h"


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
	sf::FloatRect physRect;
	sf::Sprite playerSprite;
	float currentFrame;
	sf::FloatRect lastBomb;
	void setPowerUp(char mapTile);
	void collision( Map &map, Player &enemy);
	void bombCollision(Map &map, Player &enemy);
public:
	Player(sf::Texture &mighty, int x, int y);
	void setdx(float v);
	void setdy(float v);
	void setLastBomb(sf::FloatRect lastBomb);
	bool isReloaded(float currentTime);
	float getBombTimer();
	int getExPower();
	int getPlayerX();
	int getPlayerY();
	void bombPlanted(Map &map, float timeNow);
	void update(float dt, Map &map, Player &enemy);
	bool isLose();
	bool isWinner();
	void draw(sf::RenderWindow &window);
	~Player();
};