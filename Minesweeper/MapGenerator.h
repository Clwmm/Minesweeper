#pragma once
#include <SFML/Graphics.hpp>
#include "Box.h"

class MapGenerator
{
public:
	MapGenerator(char size, char difficulty, std::vector<std::vector<Box*>>& boxes);
	static int setMapSize(char size);
};

