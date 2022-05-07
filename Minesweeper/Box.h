#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

enum class Type { normal, bomb };
enum class Stat { normal, pressed, flagged };

class Box
{
public:
	Box(float _x, float _y);
public:
	Type type;
	Stat stat = Stat::normal;
	sf::Sprite behind;
	char nobombs = 0;
	sf::Sprite box;
private:
	sf::Sprite flag;
	float x, y;
	int size = 11;
public:
	void draw(sf::RenderWindow* window);
};