#pragma once
#include "GameScreen.h"
#include "GameoverScreen.h"


using namespace sf;
using namespace std;

GameScreen::GameScreen() { };

GameScreen::GameScreen(String mapClassic[HEIGHT]) {
	pinkMighty.loadFromFile("textures\\Mighty pink.png");
	yellowMighty.loadFromFile("textures\\Mighty yellow.png");
	fire.loadFromFile("textures\\explosion.png");
	fireBrick.loadFromFile("textures\\block boom.png");
	bomb.loadFromFile("textures\\bomb.png");
	map.loadFromFile("textures\\map.png");
	
	for (int i = 0; i < HEIGHT; i++) {
		mapString[i] = mapClassic[i];
	}
	
	initGame();

	startTime = clock();
	now = clock();
	was = clock();
	timeNow = 0;
	dt = 0;
}

void GameScreen::initGame() {
	firstPlayer = new Player(pinkMighty, 1, 1);
	secondPlayer = new Player(yellowMighty, 23, 12);
	gameMap = new Map(mapString, map);
}


int GameScreen::run(sf::RenderWindow &window) {
	was = now;
	now = clock();
	timeNow = 1000.0 * (now - startTime) / CLOCKS_PER_SEC;
	dt = 1000.0 * (now - was) / CLOCKS_PER_SEC;

	while (window.pollEvent(event))
		if (event.type == Event::Closed)
			return EXIT;

	if (!((*firstPlayer).getPlayerX() == (*secondPlayer).getPlayerX() && (*firstPlayer).getPlayerY() == (*secondPlayer).getPlayerY()))
	{
		if (Keyboard::isKeyPressed(Keyboard::Space) && (*firstPlayer).isReloaded(timeNow))
		{
			(*firstPlayer).bombPlanted(*gameMap, timeNow);
			bombVector.push_back(new Bomb(bomb, (*firstPlayer).getExPower(), timeNow, (*firstPlayer).getBombTimer(), (*firstPlayer).getPlayerX(), (*firstPlayer).getPlayerY()));
		}

		if (Keyboard::isKeyPressed(Keyboard::RControl) && (*secondPlayer).isReloaded(timeNow))
		{
			(*secondPlayer).bombPlanted(*gameMap, timeNow);
			bombVector.push_back(new Bomb(bomb, (*secondPlayer).getExPower(), timeNow, (*secondPlayer).getBombTimer(), (*secondPlayer).getPlayerX(), (*secondPlayer).getPlayerY()));
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::A))
		(*firstPlayer).setdx(-0.1);
	else if (Keyboard::isKeyPressed(Keyboard::D))
		(*firstPlayer).setdx(0.1);
	else if (Keyboard::isKeyPressed(Keyboard::W))
		(*firstPlayer).setdy(-0.1);
	else if (Keyboard::isKeyPressed(Keyboard::S))
		(*firstPlayer).setdy(0.1);

	if (Keyboard::isKeyPressed(Keyboard::Left))
		(*secondPlayer).setdx(-0.1);
	else if (Keyboard::isKeyPressed(Keyboard::Right))
		(*secondPlayer).setdx(0.1);
	else if (Keyboard::isKeyPressed(Keyboard::Up))
		(*secondPlayer).setdy(-0.1);
	else if (Keyboard::isKeyPressed(Keyboard::Down))
		(*secondPlayer).setdy(0.1);

	(*firstPlayer).update(dt, *gameMap, *secondPlayer);
	(*secondPlayer).update(dt, *gameMap, *firstPlayer);

	bombIt = bombVector.begin();
	while (bombIt != bombVector.end())
		if ((*bombIt)->isExplode(timeNow))
		{
			exVector.push_back(new Explosion(fireBrick, fire, *gameMap, bombVector, (*bombIt)->getExPower(), timeNow, (*bombIt)->getBombX(), (*bombIt)->getBombY()));
			bombIt = bombVector.erase(bombIt);
		}
		else
			bombIt++;

	for (exIt = exVector.begin(); exIt != exVector.end(); exIt++)
		if ((*exIt)->isInactive(*gameMap, timeNow))
			(*exIt)->~Explosion();

	for (bombIt = bombVector.begin(); bombIt != bombVector.end(); bombIt++)
		(*bombIt)->update(timeNow);

	for (exIt = exVector.begin(); exIt != exVector.end(); exIt++)
		(*exIt)->update(timeNow);

	(*gameMap).draw(window);

	for (bombIt = bombVector.begin(); bombIt != bombVector.end(); bombIt++)
		(*bombIt)->draw(window);

	for (exIt = exVector.begin(); exIt != exVector.end(); exIt++)
		(*exIt)->draw(window);

	(*firstPlayer).draw(window);
	(*secondPlayer).draw(window);

	(*gameMap).drawLeaves(window);

	window.display();

	bool gameover = false;
	String text;
	std::string texturePath;

	if ((*firstPlayer).isLose() && (*secondPlayer).isLose()) {
		text = "";
		texturePath = "images\\draw.png";
		gameover = true;
	}
		
	if ((*firstPlayer).isWinner()) {
		text = "First player win!";
		texturePath = "images\\win.png";
		gameover = true;
	}
		
	if ((*secondPlayer).isWinner()) {
		text = "Second player win!";
		texturePath = "images\\win.png";
		gameover = true;
	}
		
	if (!gameover) {
		return GAME_SCREEN;
	}
	else {
		int gameResult = 0;
		GameoverScreen* gameoverScreen = new GameoverScreen(window, texturePath, text);
		gameResult = gameoverScreen->run(window);
		if (gameResult == GAME_SCREEN) {
			initGame();
		}
		return gameResult;
	}	
}