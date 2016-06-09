#pragma once
#include "Map.h"


class cScreen
{
public:
	cScreen();
	virtual int Run(sf::RenderWindow &App) = 0;
	~cScreen();
};

