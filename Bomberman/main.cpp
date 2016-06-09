#pragma once
#include <iostream>
#include <vector>
#include "GameScreen.h"
#include "MainMenu.h"


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