#include "Menu.h"
#include <iostream>


using namespace sf;

Menu::Menu()
{
	alpha_max = 3 * 255;
	alpha_div = 3;
	playing = false;
	backgroundPath = "images\\MenuBackground.jpg";
}

Menu::Menu(std::string backgroundPath)
{
	alpha_max = 3 * 255;
	alpha_div = 3;
	playing = false;
	this->backgroundPath = backgroundPath;
}

int Menu::run(RenderWindow &window, std::vector<MenuPoint> menuPoints)
{
	int alpha = 0;

	Event event;
	bool running = true;

	Texture background;
	background.loadFromFile(backgroundPath);

	Sprite sprite;
	sprite.setTexture(background);
	sprite.setColor(Color(255, 255, 255, alpha));
	Vector2f menuPos;
	sprite.setPosition(menuPos);

	Font font;
	font.loadFromFile(MAIN_FONT);

	int choise = MENU_NULL;

	Vector2u windowSize;
	windowSize = window.getSize();

	for (std::vector<MenuPoint>::iterator it = menuPoints.begin(); it != menuPoints.end(); it++) {
		(*it).text.setFont(font);
		(*it).text.setPosition((*it).pos.x + menuPos.x, (*it).pos.y + menuPos.y);
		align(*it);
	}

	if (playing) {
		alpha = alpha_max;
	}
	bool wasPlayed = false;
	while (running) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				return (-1);
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			return EXIT;
		}

		if (event.type == Event::MouseButtonPressed &&
			event.key.code == Mouse::Left) {
			if (choise != MENU_NULL) {
				return choise;
			}
		}

		for (std::vector<MenuPoint>::iterator it = menuPoints.begin();
		it != menuPoints.end(); it++) {
			(*it).text.setColor(Color(255, 255, 0, 255));
			choise = MENU_NULL;
			if ((*it).text.getGlobalBounds().contains(Vector2f(Mouse::getPosition().x,
				Mouse::getPosition().y)) && (*it).isActive) {

				choise = (*it).value;
				(*it).text.setColor(Color(255, 0, 0, 255));

				if (wasPlayed == false) {
					wasPlayed = true;
				}

				break;
			}
		}

		if (choise == MENU_NULL) {
			wasPlayed = false;
		}

		if (alpha < alpha_max) {
			alpha = alpha + 5;
		}
		sprite.setColor(Color(255, 255, 255, alpha / alpha_div));

		window.clear();
		window.draw(sprite);

		for (std::vector<MenuPoint>::iterator it = menuPoints.begin();
		it != menuPoints.end(); it++) {
			window.draw((*it).text);
		}

		window.display();
	}

	return (-1);
}

void Menu::align(MenuPoint &point)
{
	FloatRect textRect = point.text.getLocalBounds();
	point.text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
}