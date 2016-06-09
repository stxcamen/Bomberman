#pragma once
#include "Map.h"

#define GAME_SCREEN 1
#define MAIN_MENU_SCREEN 0
#define SELECTMAP_SCREEN 2
#define PAUSE_SCREEN 3
#define GAMEOVER_SCREEN 4
#define EXIT -1


class cScreen
{
public:
	cScreen();
	virtual int run(sf::RenderWindow &App) = 0;
	~cScreen();
};

