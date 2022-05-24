#include "MapGenerator.h"

MapGenerator::MapGenerator(char size, char difficulty, std::vector<std::vector<Box*>>& boxes)
{
	int mapsize = 0;
	std::vector<int> nobombs;

	switch (size)
	{
	case 0:
		mapsize = 10;
		nobombs.push_back(10);
		nobombs.push_back(nobombs[0] * 2);
		nobombs.push_back(nobombs[0] * 2.5);
		break;
	case 1:
		mapsize = 16;
		nobombs.push_back(26);
		nobombs.push_back(nobombs[0] * 2);
		nobombs.push_back(nobombs[0] * 2.5);
		break;
	case 2:
		mapsize = 20;
		nobombs.push_back(40);
		nobombs.push_back(nobombs[0] * 2);
		nobombs.push_back(nobombs[0] * 2.5);
		break;
	case 3:
		mapsize = 26;
		nobombs.push_back(68);
		nobombs.push_back(nobombs[0] * 2);
		nobombs.push_back(nobombs[0] * 2.5);
		break;
	case 4:
		mapsize = 30;
		nobombs.push_back(90);
		nobombs.push_back(nobombs[0] * 2);
		nobombs.push_back(nobombs[0] * 2.5);
		break;
	case 5:
		mapsize = 40;
		nobombs.push_back(190);
		nobombs.push_back(240);
		nobombs.push_back(340);
		break;
	case 6:
		mapsize = 40;

		for (int i = 0; i < mapsize; i++)
		{
			std::vector<Box*> a;
			for (int j = 0; j < mapsize; j++)
			{
				Box* e = new Box(i * 11 - (mapsize / 2 * 11), j * 11 - (mapsize / 2 * 11) + 8, i, j);
				//a.insert(a.begin(), e);
				a.push_back(e);
			}
			//boxes.insert(boxes.begin(), a);
			boxes.push_back(a);
		}

		std::vector<std::string> R;
		R.push_back("........................................");
		R.push_back("........................................");
		R.push_back("........................................");
		R.push_back("........................................");
		R.push_back("........................................");
		R.push_back("........................................");
		R.push_back("........................................");
		R.push_back("........................................");
		R.push_back("........................................");
		R.push_back("........................................");

		R.push_back("........................................");
		R.push_back("........................................");
		R.push_back("........................................");
		R.push_back("........................................");
		R.push_back("........................................");

		R.push_back("........................................");
		R.push_back(".XX.XX..XX......................XX...XX.");
		R.push_back(".XX.XX..XX......................XXX.XXX.");
		R.push_back(".XXXX...XX..XX...XX.............XXXXXXX.");
		R.push_back(".XXXX...XX..XX.X.XX.............XX.X.XX.");
		R.push_back(".XX.XX..XX..XX.X.XX.............XX...XX.");
		R.push_back(".XX.XX..XX..XXXXXX...XXXXXXXXX..XX...XX.");
		R.push_back(".XX.XX..XX...XX.XX...XXXXXXXXX..XX...XX.");
		R.push_back("........................................");

		R.push_back("........................................");
		R.push_back("........................................");
		R.push_back("........................................");
		R.push_back("........................................");
		R.push_back("........................................");
		R.push_back("........................................");

		R.push_back("........................................");
		R.push_back("........................................");
		R.push_back("........................................");
		R.push_back("........................................");
		R.push_back("........................................");
		R.push_back("........................................");
		R.push_back("........................................");
		R.push_back("........................................");
		R.push_back("........................................");
		R.push_back("........................................");

		for (int i = 0; i < R.size(); i++)
			for (int j = 0; j < R[i].length(); j++)
			{
				if (R[i][j] == *"X")
				{
					boxes[j][i]->type = Type::bomb;
					boxes[j][i]->behind.setTexture(*TextureManager::AcquireTexture("res/bomb.png"));
				}
			}

		break;
	}

	if (size != 6)
	{
		for (int i = 0; i < mapsize; i++)
		{
			std::vector<Box*> a;
			for (int j = 0; j < mapsize; j++)
			{
				Box* e = new Box(i * 11 - (mapsize / 2 * 11), j * 11 - (mapsize / 2 * 11) + 8, i, j);
				a.push_back(e);
			}
			boxes.push_back(a);
		}

		for (int i = 0; i < nobombs[difficulty]; i++)
		{
			int a = rand() % mapsize;
			int b = rand() % mapsize;
			if (boxes[a][b]->type == Type::normal)
			{
				boxes[a][b]->type = Type::bomb;
				boxes[a][b]->behind.setTexture(*TextureManager::AcquireTexture("res/bomb.png"));
			}
			else
				i--;
		}
	}
	


	for (int i = 1; i < mapsize - 1; i++)
	{
		for (int j = 1; j < mapsize - 1; j++)
		{
			int a = 0;
			if (boxes[i][j]->type == Type::normal)
			{
				if (boxes[i - 1][j - 1]->type == Type::bomb)
					a++;
				if (boxes[i][j - 1]->type == Type::bomb)
					a++;
				if (boxes[i + 1][j - 1]->type == Type::bomb)
					a++;
				if (boxes[i - 1][j]->type == Type::bomb)
					a++;
				if (boxes[i + 1][j]->type == Type::bomb)
					a++;
				if (boxes[i - 1][j + 1]->type == Type::bomb)
					a++;
				if (boxes[i][j + 1]->type == Type::bomb)
					a++;
				if (boxes[i + 1][j + 1]->type == Type::bomb)
					a++;

				if (a != 0)
					boxes[i][j]->behind.setTexture(*TextureManager::AcquireTexture("res/" + std::to_string(a) + ".png"));
				boxes[i][j]->nobombs = a;
			}
		}
	}

	for (int i = 1; i < mapsize - 1; i++)
	{
		int a = 0;
		if (boxes[0][i]->type == Type::normal)
		{
			if (boxes[0][i-1]->type == Type::bomb)
				a++;
			if (boxes[1][i-1]->type == Type::bomb)
				a++;
			if (boxes[1][i]->type == Type::bomb)
				a++;
			if (boxes[1][i+1]->type == Type::bomb)
				a++;
			if (boxes[0][i+1]->type == Type::bomb)
				a++;

			if (a != 0)
				boxes[0][i]->behind.setTexture(*TextureManager::AcquireTexture("res/" + std::to_string(a) + ".png"));
			boxes[0][i]->nobombs = a;
		}
	}

	for (int i = 1; i < mapsize - 1; i++)
	{
		int a = 0;
		if (boxes[mapsize - 1][i]->type == Type::normal)
		{
			if (boxes[mapsize - 1][i - 1]->type == Type::bomb)
				a++;
			if (boxes[mapsize - 2][i - 1]->type == Type::bomb)
				a++;
			if (boxes[mapsize - 2][i]->type == Type::bomb)
				a++;
			if (boxes[mapsize - 2][i + 1]->type == Type::bomb)
				a++;
			if (boxes[mapsize - 1][i + 1]->type == Type::bomb)
				a++;

			if (a != 0)
				boxes[mapsize - 1][i]->behind.setTexture(*TextureManager::AcquireTexture("res/" + std::to_string(a) + ".png"));
			boxes[mapsize - 1][i]->nobombs = a;
		}
	}

	for (int i = 1; i < mapsize - 1; i++)
	{
		int a = 0;
		if (boxes[i][0]->type == Type::normal)
		{
			if (boxes[i - 1][0]->type == Type::bomb)
				a++;
			if (boxes[i - 1][1]->type == Type::bomb)
				a++;
			if (boxes[i][1]->type == Type::bomb)
				a++;
			if (boxes[i + 1][1]->type == Type::bomb)
				a++;
			if (boxes[i + 1][0]->type == Type::bomb)
				a++;

			if (a != 0)
				boxes[i][0]->behind.setTexture(*TextureManager::AcquireTexture("res/" + std::to_string(a) + ".png"));
			boxes[i][0]->nobombs = a;
		}
	}

	for (int i = 1; i < mapsize - 1; i++)
	{
		int a = 0;
		if (boxes[i][mapsize - 1]->type == Type::normal)
		{
			if (boxes[i - 1][mapsize - 1]->type == Type::bomb)
				a++;
			if (boxes[i - 1][mapsize - 2]->type == Type::bomb)
				a++;
			if (boxes[i][mapsize - 2]->type == Type::bomb)
				a++;
			if (boxes[i + 1][mapsize - 2]->type == Type::bomb)
				a++;
			if (boxes[i + 1][mapsize - 1]->type == Type::bomb)
				a++;

			if (a != 0)
				boxes[i][mapsize - 1]->behind.setTexture(*TextureManager::AcquireTexture("res/" + std::to_string(a) + ".png"));
			boxes[i][mapsize - 1]->nobombs = a;
		}
	}

	if (boxes[0][0]->type == Type::normal)
	{
		int a = 0;
		if (boxes[1][0]->type == Type::bomb)
			a++;
		if (boxes[1][1]->type == Type::bomb)
			a++;
		if (boxes[0][1]->type == Type::bomb)
			a++;
		if (a != 0)
			boxes[0][0]->behind.setTexture(*TextureManager::AcquireTexture("res/" + std::to_string(a) + ".png"));
		boxes[0][0]->nobombs = a;
	}

	if (boxes[mapsize - 1][mapsize - 1]->type == Type::normal)
	{
		int a = 0;
		if (boxes[mapsize - 2][mapsize - 1]->type == Type::bomb)
			a++;
		if (boxes[mapsize - 2][mapsize - 2]->type == Type::bomb)
			a++;
		if (boxes[mapsize - 1][mapsize - 2]->type == Type::bomb)
			a++;
		if (a != 0)
			boxes[mapsize - 1][mapsize - 1]->behind.setTexture(*TextureManager::AcquireTexture("res/" + std::to_string(a) + ".png"));
		boxes[mapsize - 1][mapsize - 1]->nobombs = a;
	}

	if (boxes[mapsize - 1][0]->type == Type::normal)
	{
		int a = 0;
		if (boxes[mapsize - 2][0]->type == Type::bomb)
			a++;
		if (boxes[mapsize - 2][1]->type == Type::bomb)
			a++;
		if (boxes[mapsize - 1][1]->type == Type::bomb)
			a++;
		if (a != 0)
			boxes[mapsize - 1][0]->behind.setTexture(*TextureManager::AcquireTexture("res/" + std::to_string(a) + ".png"));
		boxes[mapsize - 1][0]->nobombs = a;
	}

	if (boxes[0][mapsize - 1]->type == Type::normal)
	{
		int a = 0;
		if (boxes[1][mapsize - 1]->type == Type::bomb)
			a++;
		if (boxes[1][mapsize - 2]->type == Type::bomb)
			a++;
		if (boxes[0][mapsize - 2]->type == Type::bomb)
			a++;
		if (a != 0)
			boxes[0][mapsize - 1]->behind.setTexture(*TextureManager::AcquireTexture("res/" + std::to_string(a) + ".png"));
		boxes[0][mapsize - 1]->nobombs = a;
	}
}

int MapGenerator::setMapSize(char size)
{
	switch (size)
	{
	case 0:
		return 10;
	case 1:
		return 16;
	case 2:
		return 20;
	case 3:
		return 26;
	case 4:
		return 30;
	case 5:
		return 40;
	case 6:
		return 40;
	}
}

void MapGenerator::mapregenerate(char size, char difficulty, std::vector<std::vector<Box*>>& boxes, int i_b, int j_b)
{
	int mapsize = 0;
	std::vector<int> nobombs;

	switch (size)
	{
	case 0:
		mapsize = 10;
		nobombs.push_back(10);
		nobombs.push_back(nobombs[0] * 2);
		nobombs.push_back(nobombs[0] * 2.5);
		break;
	case 1:
		mapsize = 16;
		nobombs.push_back(26);
		nobombs.push_back(nobombs[0] * 2);
		nobombs.push_back(nobombs[0] * 2.5);
		break;
	case 2:
		mapsize = 20;
		nobombs.push_back(40);
		nobombs.push_back(nobombs[0] * 2);
		nobombs.push_back(nobombs[0] * 2.5);
		break;
	case 3:
		mapsize = 26;
		nobombs.push_back(68);
		nobombs.push_back(nobombs[0] * 2);
		nobombs.push_back(nobombs[0] * 2.5);
		break;
	case 4:
		mapsize = 30;
		nobombs.push_back(90);
		nobombs.push_back(nobombs[0] * 2);
		nobombs.push_back(nobombs[0] * 2.5);
		break;
	case 5:
		mapsize = 40;
		nobombs.push_back(190);
		nobombs.push_back(240);
		nobombs.push_back(340);
		break;
	}

	for (auto i : boxes)
		for (auto j : i)
		{
			j->type = Type::normal;
			j->nobombs = 0;
			j->stat = Stat::normal;
		}

	for (int i = 0; i < nobombs[difficulty]; i++)
	{
		int a = rand() % mapsize;
		int b = rand() % mapsize;

		if (mapregenebool(a, b, i_b, j_b))
		{
			if (boxes[a][b]->type == Type::normal)
			{
				boxes[a][b]->type = Type::bomb;
				boxes[a][b]->behind.setTexture(*TextureManager::AcquireTexture("res/bomb.png"));
			}
			else
				i--;
		}
		else
			i--;
	}


	for (int i = 1; i < mapsize - 1; i++)
	{
		for (int j = 1; j < mapsize - 1; j++)
		{
			int a = 0;
			if (boxes[i][j]->type == Type::normal)
			{
				if (boxes[i - 1][j - 1]->type == Type::bomb)
					a++;
				if (boxes[i][j - 1]->type == Type::bomb)
					a++;
				if (boxes[i + 1][j - 1]->type == Type::bomb)
					a++;
				if (boxes[i - 1][j]->type == Type::bomb)
					a++;
				if (boxes[i + 1][j]->type == Type::bomb)
					a++;
				if (boxes[i - 1][j + 1]->type == Type::bomb)
					a++;
				if (boxes[i][j + 1]->type == Type::bomb)
					a++;
				if (boxes[i + 1][j + 1]->type == Type::bomb)
					a++;

				if (a != 0)
					boxes[i][j]->behind.setTexture(*TextureManager::AcquireTexture("res/" + std::to_string(a) + ".png"));
				boxes[i][j]->nobombs = a;
			}
		}
	}

	for (int i = 1; i < mapsize - 1; i++)
	{
		int a = 0;
		if (boxes[0][i]->type == Type::normal)
		{
			if (boxes[0][i - 1]->type == Type::bomb)
				a++;
			if (boxes[1][i - 1]->type == Type::bomb)
				a++;
			if (boxes[1][i]->type == Type::bomb)
				a++;
			if (boxes[1][i + 1]->type == Type::bomb)
				a++;
			if (boxes[0][i + 1]->type == Type::bomb)
				a++;

			if (a != 0)
				boxes[0][i]->behind.setTexture(*TextureManager::AcquireTexture("res/" + std::to_string(a) + ".png"));
			boxes[0][i]->nobombs = a;
		}
	}

	for (int i = 1; i < mapsize - 1; i++)
	{
		int a = 0;
		if (boxes[mapsize - 1][i]->type == Type::normal)
		{
			if (boxes[mapsize - 1][i - 1]->type == Type::bomb)
				a++;
			if (boxes[mapsize - 2][i - 1]->type == Type::bomb)
				a++;
			if (boxes[mapsize - 2][i]->type == Type::bomb)
				a++;
			if (boxes[mapsize - 2][i + 1]->type == Type::bomb)
				a++;
			if (boxes[mapsize - 1][i + 1]->type == Type::bomb)
				a++;

			if (a != 0)
				boxes[mapsize - 1][i]->behind.setTexture(*TextureManager::AcquireTexture("res/" + std::to_string(a) + ".png"));
			boxes[mapsize - 1][i]->nobombs = a;
		}
	}

	for (int i = 1; i < mapsize - 1; i++)
	{
		int a = 0;
		if (boxes[i][0]->type == Type::normal)
		{
			if (boxes[i - 1][0]->type == Type::bomb)
				a++;
			if (boxes[i - 1][1]->type == Type::bomb)
				a++;
			if (boxes[i][1]->type == Type::bomb)
				a++;
			if (boxes[i + 1][1]->type == Type::bomb)
				a++;
			if (boxes[i + 1][0]->type == Type::bomb)
				a++;

			if (a != 0)
				boxes[i][0]->behind.setTexture(*TextureManager::AcquireTexture("res/" + std::to_string(a) + ".png"));
			boxes[i][0]->nobombs = a;
		}
	}

	for (int i = 1; i < mapsize - 1; i++)
	{
		int a = 0;
		if (boxes[i][mapsize - 1]->type == Type::normal)
		{
			if (boxes[i - 1][mapsize - 1]->type == Type::bomb)
				a++;
			if (boxes[i - 1][mapsize - 2]->type == Type::bomb)
				a++;
			if (boxes[i][mapsize - 2]->type == Type::bomb)
				a++;
			if (boxes[i + 1][mapsize - 2]->type == Type::bomb)
				a++;
			if (boxes[i + 1][mapsize - 1]->type == Type::bomb)
				a++;

			if (a != 0)
				boxes[i][mapsize - 1]->behind.setTexture(*TextureManager::AcquireTexture("res/" + std::to_string(a) + ".png"));
			boxes[i][mapsize - 1]->nobombs = a;
		}
	}

	if (boxes[0][0]->type == Type::normal)
	{
		int a = 0;
		if (boxes[1][0]->type == Type::bomb)
			a++;
		if (boxes[1][1]->type == Type::bomb)
			a++;
		if (boxes[0][1]->type == Type::bomb)
			a++;
		if (a != 0)
			boxes[0][0]->behind.setTexture(*TextureManager::AcquireTexture("res/" + std::to_string(a) + ".png"));
		boxes[0][0]->nobombs = a;
	}

	if (boxes[mapsize - 1][mapsize - 1]->type == Type::normal)
	{
		int a = 0;
		if (boxes[mapsize - 2][mapsize - 1]->type == Type::bomb)
			a++;
		if (boxes[mapsize - 2][mapsize - 2]->type == Type::bomb)
			a++;
		if (boxes[mapsize - 1][mapsize - 2]->type == Type::bomb)
			a++;
		if (a != 0)
			boxes[mapsize - 1][mapsize - 1]->behind.setTexture(*TextureManager::AcquireTexture("res/" + std::to_string(a) + ".png"));
		boxes[mapsize - 1][mapsize - 1]->nobombs = a;
	}

	if (boxes[mapsize - 1][0]->type == Type::normal)
	{
		int a = 0;
		if (boxes[mapsize - 2][0]->type == Type::bomb)
			a++;
		if (boxes[mapsize - 2][1]->type == Type::bomb)
			a++;
		if (boxes[mapsize - 1][1]->type == Type::bomb)
			a++;
		if (a != 0)
			boxes[mapsize - 1][0]->behind.setTexture(*TextureManager::AcquireTexture("res/" + std::to_string(a) + ".png"));
		boxes[mapsize - 1][0]->nobombs = a;
	}

	if (boxes[0][mapsize - 1]->type == Type::normal)
	{
		int a = 0;
		if (boxes[1][mapsize - 1]->type == Type::bomb)
			a++;
		if (boxes[1][mapsize - 2]->type == Type::bomb)
			a++;
		if (boxes[0][mapsize - 2]->type == Type::bomb)
			a++;
		if (a != 0)
			boxes[0][mapsize - 1]->behind.setTexture(*TextureManager::AcquireTexture("res/" + std::to_string(a) + ".png"));
		boxes[0][mapsize - 1]->nobombs = a;
	}

}

bool MapGenerator::mapregenebool(int a, int b, int c, int d)
{
	if (a == c && b == d)
		return false;
	else if (a == c - 1 && b == d - 1)
		return false;
	else if (a == c && b == d - 1)
		return false;
	else if (a == c + 1 && b == d - 1)
		return false;
	else if (a == c - 1 && b == d)
		return false;
	else if (a == c + 1 && b == d)
		return false;
	else if (a == c - 1 && b == d + 1)
		return false;
	else if (a == c && b == d + 1)
		return false;
	else if (a == c + 1 && b == d + 1)
		return false;
	else
		return true;
}
