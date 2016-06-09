#pragma once
#include <iostream>
#include <vector>
#include "GameScreen.h"
#include "MainMenu.h"


using namespace sf;
using namespace std;

String mapClassic[HEIGHT] = {
	"BBBBBBBBBBBBBBBBBBBBBBBBB",
	"B  DDDDDDDDDDDDDDDDDDD  B",
	"B    BBBBBDDDDDBBBDDDBDLB",
	"BLLLLLLL   BBDDDDDDDD LLB",
	"BLLLLLLLLLLLBDD LLLDDBBBB",
	"BDBDDDDBLLLLBDD BB  DDDDB",
	"BDDBBDDDLLLLLLLLLB  DDD B",
	"BDDDDDDBLLLLLLLLL   BBDDB",
	"BLL B  BBDDLDLLLLLDDDDD B",
	"BDDBDBDDDDDLBLLLLLLLLLLLB",
	"B DDDDDLLLLLBBBBBLLLLLLLB",
	"B BDDBBBDLLLDBBDDDDBBDD B",
	"B  DDDDDDLLLDDDDDDDDDD  B",
	"BBBBBBBBBBBBBBBBBBBBBBBBB",
};

int main()
{
	RenderWindow window(VideoMode::getDesktopMode(), "Bomberman", Style::Fullscreen);

	std::vector<cScreen*> screens;
	int screen = MAIN_MENU_SCREEN;
	
	MainMenu* mainMenu = new MainMenu(window);
	screens.push_back(mainMenu);

	GameScreen* gameScreen = new GameScreen(mapClassic);
	screens.push_back(gameScreen);

	while (screen >= 0)
	{
		screen = screens[screen]->run(window);
	}

	return 0;
}