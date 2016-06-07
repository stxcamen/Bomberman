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

String mapClassic[H] = {
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

	RenderWindow window(VideoMode::getDesktopMode(), "Bomberman", Style::Fullscreen);

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

	vector <Bomb*> bombVector;
	vector <Bomb*> ::iterator bombIt;
	bombVector.clear();
	vector <Explosion*> exVector;
	vector <Explosion*> ::iterator exIt;
	exVector.clear();

	clock_t start_time = clock(), now = clock(), was = clock();

	while (window.isOpen())
	{
		while (window.pollEvent(event))
			if (event.type == Event::Closed)
				window.close();
		was = now;
		now = clock();
		float time_now = 1000.0 * (now - start_time) / CLOCKS_PER_SEC;
		float dt = 3000.0 * (now - was) / CLOCKS_PER_SEC;


		if ((Keyboard::isKeyPressed(Keyboard::LShift) && (*firstPlayer).isReloaded(time_now))
			&& !((*firstPlayer).getPlayerX() == (*secondPlayer).getPlayerX() && (*firstPlayer).getPlayerY() == (*secondPlayer).getPlayerY()))
		{
			(*firstPlayer).bombPlanted(*classicMap, time_now);
			bombVector.push_back(new Bomb(bomb, (*firstPlayer).getExPower(), time_now, (*firstPlayer).getBombDiffTime(), (*firstPlayer).getPlayerX(), (*firstPlayer).getPlayerY()));
		}

		if (Keyboard::isKeyPressed(Keyboard::RShift) && (*secondPlayer).isReloaded(time_now)
			&& !((*firstPlayer).getPlayerX() == (*secondPlayer).getPlayerX() && (*firstPlayer).getPlayerY() == (*secondPlayer).getPlayerY()))
		{
			(*secondPlayer).bombPlanted(*classicMap, time_now);
			bombVector.push_back(new Bomb(bomb, (*secondPlayer).getExPower(), time_now, (*secondPlayer).getBombDiffTime(), (*secondPlayer).getPlayerX(), (*secondPlayer).getPlayerY()));
		}

		if (Keyboard::isKeyPressed(Keyboard::A))
			(*firstPlayer).set_dx(-0.1);
		else if (Keyboard::isKeyPressed(Keyboard::D))
			(*firstPlayer).set_dx(0.1);
		else if (Keyboard::isKeyPressed(Keyboard::W))
			(*firstPlayer).set_dy(-0.1);
		else if (Keyboard::isKeyPressed(Keyboard::S))
			(*firstPlayer).set_dy(0.1);

		if (Keyboard::isKeyPressed(Keyboard::Left))
			(*secondPlayer).set_dx(-0.1);
		else if (Keyboard::isKeyPressed(Keyboard::Right))
			(*secondPlayer).set_dx(0.1);
		else if (Keyboard::isKeyPressed(Keyboard::Up))
			(*secondPlayer).set_dy(-0.1);
		else if (Keyboard::isKeyPressed(Keyboard::Down))
			(*secondPlayer).set_dy(0.1);

		(*firstPlayer).update(dt, *classicMap, (*secondPlayer).isLose());
		(*secondPlayer).update(dt, *classicMap, (*firstPlayer).isLose());

		bombIt = bombVector.begin();
		while (bombIt != bombVector.end())
			if ((*bombIt)->isExplode(time_now))
			{
				exVector.push_back(new Explosion(fireBrick, fire, *classicMap, bombVector, (*bombIt)->getExPower(), time_now, (*bombIt)->getBombX(), (*bombIt)->getBombY()));
				bombIt = bombVector.erase(bombIt);
			}
			else
				bombIt++;

		for (exIt = exVector.begin(); exIt != exVector.end(); exIt++)
			if ((*exIt)->isInactive(*classicMap, time_now))
				(*exIt)->~Explosion();

		for (bombIt = bombVector.begin(); bombIt != bombVector.end(); bombIt++)
			(*bombIt)->update(time_now);

		for (exIt = exVector.begin(); exIt != exVector.end(); exIt++)
			(*exIt)->update(time_now);

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