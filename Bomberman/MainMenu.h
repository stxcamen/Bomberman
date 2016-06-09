#pragma once
#include "Menu.h"


class MainMenu : public Menu {
private:
	std::vector<MenuPoint> menuPoints;
public:
	MainMenu(sf::RenderWindow &window);
	int run(sf::RenderWindow &window);
};


