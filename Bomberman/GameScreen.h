#pragma once
#include "cScreen.h"
#include "Bomb.h"
#include "Player.h"
#include "Explosion.h"
#include <ctime>


class GameScreen : public cScreen {
private:
	sf::Texture pinkMighty;
	sf::Texture yellowMighty;
	sf::Texture fire;
	sf::Texture fireBrick;
	sf::Texture bomb;
	sf::Texture map;
	Player* firstPlayer;
	Player* secondPlayer;
	Map* gameMap;
	sf::String mapString[HEIGHT];

	std::vector <Bomb*> bombVector;
	std::vector <Bomb*> ::iterator bombIt;
	std::vector <Explosion*> exVector;
	std::vector <Explosion*> ::iterator exIt;

	clock_t startTime, now, was;
	float timeNow, dt;

	sf::Event event;

	void initGame();

public:
	GameScreen();
	GameScreen(sf::String mapClassic[HEIGHT]);
	int run(sf::RenderWindow &window);
};