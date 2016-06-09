#pragma once
#include "Menu.h"

class GameoverScreen : public Menu {
private:
	std::vector<MenuPoint> menuPoints;
public:
	GameoverScreen(sf::RenderWindow &window, std::string texturePath, sf::String text);
	int run(sf::RenderWindow &window);
};