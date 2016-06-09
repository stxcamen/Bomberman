#pragma once
#include <iostream>
#include <vector>
#include <iterator>
#include <ctime>
#include "Player.h"
#include "Map.h"
#include "Bomb.h"
#include "Explosion.h"


using namespace sf;
using namespace std;

/*String mapClassic[H] = {
	"                         ",
	"BBBBBBBBBBBBBBBBBBBBBBBBB",
	"B  DDDDDDDDDDDDDDDDDDD  B",
	"B BDBDBDBDBDBDBDBDBDBDB B",
	"BDDDDDDDDDDDDDDDDDDDDDDDB",
	"BDBDBDBDBDBDBDBDBDBDBDBDB",
	"BDDDDDDDDDDDDDDDDDDDDDDDB",
	"BDBDBDBDBDBDBDBDBDBDBDBDB",
	"BDDDDDDDDDDDDDDDDDDDDDDDB",
	"BDBDBDBDBDBDBDBDBDBDBDBDB",
	"BDDDDDDDDDDDDDDDDDDDDDDDB",
	"B BDBDBDBDBDBDBDBDBDBDB B",
	"B  DDDDDDDDDDDDDDDDDDD  B",
	"BBBBBBBBBBBBBBBBBBBBBBBBB",
};*/

String mapClassic[HEIGHT] = {
	"                         ",
	"BBBBBBBBBBBBBBBBBBBBBBBBB",
	"B  DDDDDDDDDDDDDDDDDDD  B",
	"B           BDBDBDBDBDB B",
	"BD          DDDDDDDDDDDDB",
	"BD          BDBDBDBDBDBDB",
	"BD          DDDDDDDDDDDDB",
	"BDBDBDBD    BDBDBDBDBDBDB",
	"BDDDDDDDD        DDDDDDDB",
	"BDBDBDBDB              DB",
	"BDDDDDDDDDDDDDD        DB",
	"B BDBDBDBDBDBDB         B",
	"B  DDDDDDDDDDDDDDDDDDD  B",
	"BBBBBBBBBBBBBBBBBBBBBBBBB",
};

int main()
{
	Event event;

	RenderWindow window(VideoMode::getDesktopMode(), "Bomberman");

	Texture pinkMighty, yellowMighty, fire, fireBrick, bomb, map;
	pinkMighty.loadFromFile("textures\\Mighty pink.png");
	yellowMighty.loadFromFile("textures\\Mighty yellow.png");
	fire.loadFromFile("textures\\explosion.png");
	fireBrick.loadFromFile("textures\\block boom.png");
	bomb.loadFromFile("textures\\bomb.png");
	map.loadFromFile("textures\\map.png");

	Player* firstPlayer = new Player(pinkMighty, 1, 2);
	Player* secondPlayer = new Player(yellowMighty, 23, 12);
	Map* classicMap = new Map(mapClassic, map);

	std::vector <Bomb*> bombVector;
	std::vector <Bomb*> ::iterator bombIt;
	bombVector.clear();
	std::vector <Explosion*> exVector;
	vector <Explosion*> ::iterator exIt;
	exVector.clear();

	clock_t startTime = clock(), now = clock(), was = clock();
	float timeNow, dt;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
			if (event.type == Event::Closed)
				window.close();

		was = now;
		now = clock();
		timeNow = 1000.0 * (now - startTime) / CLOCKS_PER_SEC;
		dt = 1000.0 * (now - was) / CLOCKS_PER_SEC;

		if (!((*firstPlayer).getPlayerX() == (*secondPlayer).getPlayerX() && (*firstPlayer).getPlayerY() == (*secondPlayer).getPlayerY()))
		{
			if (Keyboard::isKeyPressed(Keyboard::LShift) && (*firstPlayer).isReloaded(timeNow))
			{
				(*firstPlayer).bombPlanted(*classicMap, timeNow);
				bombVector.push_back(new Bomb(bomb, (*firstPlayer).getExPower(), timeNow, (*firstPlayer).getBombTimer(), (*firstPlayer).getPlayerX(), (*firstPlayer).getPlayerY()));
			}

			if (Keyboard::isKeyPressed(Keyboard::RShift) && (*secondPlayer).isReloaded(timeNow))
			{
				(*secondPlayer).bombPlanted(*classicMap, timeNow);
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

		(*firstPlayer).update(dt, *classicMap, *secondPlayer);
		(*secondPlayer).update(dt, *classicMap, *firstPlayer);

		bombIt = bombVector.begin();
		while (bombIt != bombVector.end())
			if ((*bombIt)->isExplode(timeNow))
			{
				exVector.push_back(new Explosion(fireBrick, fire, *classicMap, bombVector, (*bombIt)->getExPower(), timeNow, (*bombIt)->getBombX(), (*bombIt)->getBombY()));
				bombIt = bombVector.erase(bombIt);
			}
			else
				bombIt++;

		for (exIt = exVector.begin(); exIt != exVector.end(); exIt++)
			if ((*exIt)->isInactive(*classicMap, timeNow))
				(*exIt)->~Explosion();

		for (bombIt = bombVector.begin(); bombIt != bombVector.end(); bombIt++)
			(*bombIt)->update(timeNow);

		for (exIt = exVector.begin(); exIt != exVector.end(); exIt++)
			(*exIt)->update(timeNow);

		(*classicMap).draw(window);

		for (bombIt = bombVector.begin(); bombIt != bombVector.end(); bombIt++)
			(*bombIt)->draw(window);

		for (exIt = exVector.begin(); exIt != exVector.end(); exIt++)
			(*exIt)->draw(window);

		(*firstPlayer).draw(window);
		(*secondPlayer).draw(window);

		window.display();

		if ((*firstPlayer).isLose() && (*secondPlayer).isLose())
			return 0;
		if ((*firstPlayer).isWinner())
			return 0;
		if ((*secondPlayer).isWinner())
			return 0;
	}
	
	return 0;
}