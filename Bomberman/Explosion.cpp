#include "Explosion.h"
#define PLUS_X 128
#define MINUS_X 0
#define PLUS_Y 384
#define MINUS_Y 256
#define LONG_FIRE IntRect(64 + dir, 0, 64, 64) 
#define FIRE_END IntRect(128 + dir, 0, 64, 64)
#define CROSS_FIRE IntRect(0, 0, 64, 64)
#define FIRE_BRICK IntRect(0, 0, 64, 64)


Explosion::Explosion(Texture &brick, Texture &fire, Map &map, vector <Bomb*> &bombVector, int exPower, float time_now, int x, int y)
{
	this->exPower = exPower;
	startTime = time_now;
	spriteVector.clear();
	spriteVector.push_back(new Sprite(fire, CROSS_FIRE));
	spriteVector.back()->setPosition(x * TILE_SIZE, y * TILE_SIZE);
	map.setTile('E', y, x);
	bool Xp, Yp, Xm, Ym;
	Xp = Yp = Xm = Ym = true;
	for (int i = 1; i <= exPower; i++)  
	{	
		if (Xp)
			Xp = fireSpread(brick, fire, map, bombVector, PLUS_X, x + i, y, i);
		if(Xm)
			Xm = fireSpread(brick, fire, map, bombVector, MINUS_X, x - i, y, i);
		if(Yp)
			Yp = fireSpread(brick, fire, map, bombVector, PLUS_Y, x, y + i, i);
		if(Ym)
			Ym = fireSpread(brick, fire, map, bombVector, MINUS_Y, x, y - i, i);
	}
}

bool Explosion::fireSpread(Texture &brick, Texture &fire, Map &map, vector <Bomb*> &bombVector, int dir, int x, int y, int i)
{

		char ch = map.getTile( y, x );
		if ((ch == ' ') || (ch == 'E'))
		{
			if (i == exPower)
				spriteVector.push_back(new Sprite(fire, FIRE_END));
			else
				spriteVector.push_back(new Sprite(fire, LONG_FIRE));
			spriteVector.back()->setPosition(x * TILE_SIZE, y * TILE_SIZE);
			map.setTile('E', y , x );
			return true;
		}
		else if (ch == 'D')
		{
			spriteVector.push_back(new Sprite(brick, FIRE_BRICK));
			spriteVector.back()->setPosition(x * TILE_SIZE, y * TILE_SIZE);
			map.setTile('F', y, x );
			return false;
		}
		else if (ch == 'Q')
		{
			for (auto bombIt = bombVector.begin(); bombIt != bombVector.end(); bombIt++)
				if (((*bombIt)->getBombX() == x ) && ((*bombIt)->getBombY() == y))
				{
					(*bombIt)->explode();
					return false;
				}
		}
		else if ((ch == 'F') || (ch == 'B'))
			return false;
}

void Explosion::update( float time_now )
{
	IntRect tempRect;
	if((time_now - startTime) >= (3.0 * exTime / 4) )
		for (spriteIt = spriteVector.begin(); spriteIt != spriteVector.end(); spriteIt++)
		{
			tempRect = (*spriteIt)->getTextureRect();
			tempRect.top = 3 * TILE_SIZE;
			(*spriteIt)->setTextureRect( tempRect );
		}
	else if((time_now - startTime) >= (2.0 * exTime / 4))
		for (spriteIt = spriteVector.begin(); spriteIt != spriteVector.end(); spriteIt++)
		{
			tempRect = (*spriteIt)->getTextureRect();
			tempRect.top = 2 * TILE_SIZE;
			(*spriteIt)->setTextureRect( tempRect );
		}
	else if ((time_now - startTime) >= (exTime / 4.0))
		for (spriteIt = spriteVector.begin(); spriteIt != spriteVector.end(); spriteIt++)
		{
			tempRect = (*spriteIt)->getTextureRect();
			tempRect.top = TILE_SIZE;
			(*spriteIt)->setTextureRect(tempRect);
		}
}

void Explosion::draw(RenderWindow &window)
{
	for (spriteIt = spriteVector.begin(); spriteIt != spriteVector.end(); spriteIt++)
		window.draw(**spriteIt);
}

bool Explosion::isInactive(Map &map, float time_now)
{
	if ((time_now - startTime) >= exTime) 
	{
		for (spriteIt = spriteVector.begin(); spriteIt != spriteVector.end(); spriteIt++)
			map.setTile(' ', (*spriteIt)->getPosition().y / TILE_SIZE, (*spriteIt)->getPosition().x / TILE_SIZE);
		return true;
	}
	return false;
}