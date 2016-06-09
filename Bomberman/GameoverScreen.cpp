#pragma once
#include "GameoverScreen.h"

using namespace sf;

GameoverScreen::GameoverScreen(sf::RenderWindow &window, std::string texturePath, sf::String text) : Menu(texturePath)
{
	MenuPoint point;
	Vector2f textPos;

	point.text.setCharacterSize(81);

	point.text.setString(text);
	point.value = MENU_NULL;
	point.isActive = false;
	point.text.setColor(sf::Color(Color::Red));
	textPos.x = 3 * window.getSize().x / 4;
	textPos.y = window.getSize().y / 2 - 2 * INTERVAL;
	point.pos = textPos;
	menuPoints.push_back(point);

	point.text.setString("Play again");
	point.value = GAME_SCREEN;
	point.isActive = true;
	point.text.setColor(sf::Color(Color::Red));
	textPos.x = 3 * window.getSize().x / 4;
	textPos.y = window.getSize().y / 2 + 4 * INTERVAL;
	point.pos = textPos;
	menuPoints.push_back(point);

	point.text.setString("Exit");
	point.value = MAIN_MENU_SCREEN;
	point.isActive = true;
	point.text.setColor(sf::Color(Color::Red));
	textPos.x = 3 * window.getSize().x / 4;
	textPos.y = window.getSize().y / 2 + 5 * INTERVAL;
	point.pos = textPos;
	menuPoints.push_back(point);
}


int GameoverScreen::run(RenderWindow &window)
{
	return Menu::run(window, menuPoints);
}