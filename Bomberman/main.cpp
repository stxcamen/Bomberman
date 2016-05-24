#pragma once
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <ctime>
#include "SFML\Graphics.hpp"
#include "Player.h"
#include "Map.h"
#include "Bomb.h"
//#include "Explosion.h"


using namespace sf;
using namespace std;


String mapClassic[H] = {
	"BBBBBBBBBBBBBBBBBBB",
	"B    DDDDDDDDDDD  B",
	"B               B B",
	"BD              DDB",
	"BD              BDB",
	"BD              DDB",
	"BD              DDB",
	"BD              DDB",
	"BD              DDB",
	"BD              BDB",
	"BDDDDDDDDDDDDDDDDDB",
	"B BDBDBDBDBDBDBDB B",
	"B  DDDDDDDDDDDDD  B",
	"BBBBBBBBBBBBBBBBBBB",
};

Event event;

int main() 
{
	RenderWindow window(VideoMode( TILE_SIZE * W, TILE_SIZE * H), "Bomberman");
	Player* firstPlayer = new Player();
	Map* classicMap = new Map( mapClassic );

	vector <Bomb*> bombVector;
	vector <Bomb*> :: iterator bombIt;
	bombVector.clear();
	//vector <Explosion*> exVector;
	//vector <Explosion*> ::iterator exIt;
	//exVector.clear();
	
	clock_t start_time = clock(), now = clock(), was = clock();
	
	while ( window.isOpen() ) 
	{
		while (window.pollEvent(event))
			if (event.type == Event::Closed)
				window.close();
		was = now;
		now = clock();
		float time_now = 1000.0*( now - start_time ) / CLOCKS_PER_SEC;
		float dt = 3000.0*( now - was ) / CLOCKS_PER_SEC;

		(*classicMap).draw(window);

		if ((Keyboard::isKeyPressed(Keyboard::Space) && (*firstPlayer).isReloaded(time_now))  )
			{
				(*firstPlayer).bombPlanted(*classicMap, time_now);
				bombVector.push_back(new Bomb(time_now, (*firstPlayer).getBombDiffTime(), (*firstPlayer).getPlayerX(), (*firstPlayer).getPlayerY()));
			}
		
		if (Keyboard::isKeyPressed(Keyboard::Left))
			(*firstPlayer).set_dx(-0.1);
		else if (Keyboard::isKeyPressed(Keyboard::Right))
			(*firstPlayer).set_dx(0.1);
		else if (Keyboard::isKeyPressed(Keyboard::Up))
			(*firstPlayer).set_dy(-0.1);
		else if (Keyboard::isKeyPressed(Keyboard::Down))
			(*firstPlayer).set_dy(0.1);
	
		(*firstPlayer).update( dt, *classicMap);

		bombIt = bombVector.begin();
		while (bombVector.size() && (*bombIt)->isExplode(time_now))
		{
			(*classicMap).setTile(' ', (*bombIt)->getBombY(), (*bombIt)->getBombX());
			bombIt = bombVector.erase(bombIt);
		}

		for ( bombIt = bombVector.begin(); bombIt != bombVector.end(); bombIt++)
			(*bombIt)->update(time_now);

		for ( bombIt = bombVector.begin(); bombIt != bombVector.end(); bombIt++)
			(*bombIt)->draw(window);
		
		(*firstPlayer).draw( window );

		window.display();
	}
	
	return 0;
}