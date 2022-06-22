#include "Box.h"

Box::Box(float _x, float _y, int _i, int _j)
{
	x = _x;
	y = _y;
	i = _i;
	j = _j;
	type = Type::normal;

	box.setTexture(*TextureManager::AcquireTexture("res/box.png"));
	flag.setTexture(*TextureManager::AcquireTexture("res/flag.png"));
}

void Box::draw(sf::RenderWindow* window, bool tr)
{
	box.setPosition(x, y);
	flag.setPosition(x, y);
	behind.setPosition(x, y);

	
	if (nobombs > 0 || type == Type::bomb)
		window->draw(behind);

	switch (stat)
	{
	case Stat::normal:
		window->draw(box);
		break;
	case Stat::flagged:
		window->draw(box);
		window->draw(flag);
		break;
	}
}