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


	for (auto i : boxes)
		for (auto j : i)
		{
			if (j->type != Type::bomb)
			{
				std::vector<Box*> temp;

				if (j->i - 1 >= 0 && j->j - 1 >= 0)
					temp.push_back(boxes[j->i - 1][j->j - 1]);
				if (j->i + 1 < mapsize && j->j + 1 < mapsize)
					temp.push_back(boxes[j->i + 1][j->j + 1]);
				if (j->i + 1 < mapsize && j->j - 1 >= 0)
					temp.push_back(boxes[j->i + 1][j->j - 1]);
				if (j->i - 1 >= 0 && j->j + 1 < mapsize)
					temp.push_back(boxes[j->i - 1][j->j + 1]);
				if (j->j + 1 < mapsize)
					temp.push_back(boxes[j->i][j->j + 1]);
				if (j->j - 1 >= 0)
					temp.push_back(boxes[j->i][j->j - 1]);
				if (j->i + 1 < mapsize)
					temp.push_back(boxes[j->i + 1][j->j]);
				if (j->i - 1 >= 0)
					temp.push_back(boxes[j->i - 1][j->j]);

				int a = 0;

				for (auto k : temp)
				{
					if (k->type == Type::bomb)
						a++;
				}
				if (a != 0)
					j->behind.setTexture(*TextureManager::AcquireTexture("res/" + std::to_string(a) + ".png"));
				j->nobombs = a;
			}
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

		if (mapregenebool(a, b, i_b, j_b) && boxes[a][b]->type == Type::normal)
		{
			boxes[a][b]->type = Type::bomb;
			boxes[a][b]->behind.setTexture(*TextureManager::AcquireTexture("res/bomb.png"));
		}
		else
			i--;
	}

	for (auto i : boxes)
		for (auto j : i)
		{
			if (j->type != Type::bomb)
			{
				std::vector<Box*> temp;

				if (j->i - 1 >= 0 && j->j - 1 >= 0)
					temp.push_back(boxes[j->i - 1][j->j - 1]);
				if (j->i + 1 < mapsize && j->j + 1 < mapsize)
					temp.push_back(boxes[j->i + 1][j->j + 1]);
				if (j->i + 1 < mapsize && j->j - 1 >= 0)
					temp.push_back(boxes[j->i + 1][j->j - 1]);
				if (j->i - 1 >= 0 && j->j + 1 < mapsize)
					temp.push_back(boxes[j->i - 1][j->j + 1]);
				if (j->j + 1 < mapsize)
					temp.push_back(boxes[j->i][j->j + 1]);
				if (j->j - 1 >= 0)
					temp.push_back(boxes[j->i][j->j - 1]);
				if (j->i + 1 < mapsize)
					temp.push_back(boxes[j->i + 1][j->j]);
				if (j->i - 1 >= 0)
					temp.push_back(boxes[j->i - 1][j->j]);

				int a = 0;

				for (auto k : temp)
					if (k->type == Type::bomb)
						a++;

				if (a != 0)
					j->behind.setTexture(*TextureManager::AcquireTexture("res/" + std::to_string(a) + ".png"));

				j->nobombs = a;
			}
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
