#pragma once
#include "MainMenu.h"


using namespace sf;

MainMenu::MainMenu(RenderWindow &window) {
	MenuPoint point;
	Vector2f textPos;

	point.text.setCharacterSize(81);

	point.text.setString("Start game");
	point.value = GAME_SCREEN;
	point.isActive = true;
	point.text.setColor(sf::Color(Color::Red));
	textPos.x = 3 * window.getSize().x / 4;
	textPos.y = window.getSize().y / 2 + 3 * INTERVAL;
	point.pos = textPos;
	menuPoints.push_back(point);

	point.text.setString("Exit");
	point.value = EXIT;
	point.isActive = true;
	point.text.setColor(sf::Color(Color::Red));
	textPos.x = 3 * window.getSize().x / 4;
	textPos.y = window.getSize().y / 2 + 4 * INTERVAL;
	point.pos = textPos;
	menuPoints.push_back(point);
}

int MainMenu::run(sf::RenderWindow &window){
	return Menu::run(window, menuPoints);
}