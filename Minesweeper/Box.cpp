#include "Box.h"

Box::Box(float _x, float _y)
{
	x = _x;
	y = _y;
	type = Type::normal;

	box.setTexture(*TextureManager::AcquireTexture("res/box.png"));
	flag.setTexture(*TextureManager::AcquireTexture("res/flag.png"));
	
}

void Box::draw(sf::RenderWindow* window)
{
	box.setPosition(x, y);
	flag.setPosition(x, y);
	behind.setPosition(x, y);

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