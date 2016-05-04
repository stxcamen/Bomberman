#pragma once
#include "SFML\Graphics.hpp"
#include "Player.h"
#include "Map.h"


using namespace sf;

String mapClassic[H] = {
	"BBBBBBBBBBBBBBB",
	"B  DDDDDDDDD  B",
	"B BDBDBDBDBDB B",
	"BDDDDDDDDDDDDDB",
	"BDBDBDBDBDBDBDB",
	"BDDDDDD DDDDDDB",
	"BDBDBD   DBDBDB",
	"BDDDDDD DDDDDDB",
	"BDBDBDBDBDBDBDB",
	"BDDDDDDDDDDDDDB",
	"B BDBDBDBDBDB B",
	"B  DDDDDDDDD  B",
	"BBBBBBBBBBBBBBB",
};

int main() {
	RenderWindow window(VideoMode( TILE_SIZE * W, TILE_SIZE * H), "Bomberman.");
	

	Clock clock;

	Player* first_player = new Player();
	Map* classicMap = new Map( mapClassic );

	while (window.isOpen()) {
		
		int keyIsPressed;

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time *= 0.00075;

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		keyIsPressed = 0;

		if (Keyboard::isKeyPressed(Keyboard::Left) && (keyIsPressed == 0)) {
			(*first_player).set_dx( -0.1 );
			keyIsPressed = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right) && (keyIsPressed == 0)) {
			(*first_player).set_dx( 0.1 );
			keyIsPressed = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up) && (keyIsPressed == 0)) {
			(*first_player).set_dy( -0.1 );
			keyIsPressed = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down) && (keyIsPressed == 0)) {
			(*first_player).set_dy( 0.1 );
			keyIsPressed = 1;
		}

		(*first_player).update(time, *classicMap);

		(*classicMap).draw( window );

		window.draw((*first_player).getSprite());
		window.display();
	}
	return 0;
}