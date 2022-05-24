#pragma once
#include <SFML/Graphics.hpp>
#include "Box.h"

class MapGenerator
{
public:
	MapGenerator(char size, char difficulty, std::vector<std::vector<Box*>>& boxes);
	static int setMapSize(char size);
	static void mapregenerate(char size, char difficulty, std::vector<std::vector<Box*>>& boxes, int i, int j);
private:
	static bool mapregenebool(int a, int b, int c, int d);
};

