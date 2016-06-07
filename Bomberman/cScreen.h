#pragma once
#include "Bomb.h"


using namespace sf;

class cScreen
{
public:
	cScreen();
	virtual int Run(RenderWindow &App) = 0;
	~cScreen();
};

