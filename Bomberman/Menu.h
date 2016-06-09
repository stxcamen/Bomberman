#ifndef MENU_H
#define MENU_H 
#include "cScreen.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iterator>

#define MENU_NULL -2
#define MENU_POINT_SIZE 36
#define INTERVAL 70
#define MAIN_FONT "fonts\\Boomboom.ttf"


struct MenuPoint
{
	sf::Text text;
	int value;
	sf::Vector2f pos;
	bool isActive;
};

struct RecordItem
{
	std::wstring name;
	std::wstring tankName;
	int record;
};

class Menu :
	public cScreen
{
private:
	int alpha_max;
	int alpha_div;
	bool playing;
	std::vector<MenuPoint> menuPoints;
	std::string backgroundPath;
public:
	Menu();
	Menu(std::string backgroundPath);
	int run(sf::RenderWindow &window, std::vector<MenuPoint> menuPoints);
	static void align(MenuPoint &point);
};

#endif // !MENU_H