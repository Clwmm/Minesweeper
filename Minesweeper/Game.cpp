#include "Game.h"

Game::Game()
{
	if (!pointingcursor.loadFromSystem(sf::Cursor::Arrow))
		close = true;
	if (!handcursor.loadFromSystem(sf::Cursor::Hand))
		close = true;
	if (!font->loadFromFile("res/notalot35.ttf"))
		close = true;
	if (!icon.loadFromFile("res/icon.png"))
		close = true;
}

void Game::start()
{
	while (!close)
	{
		switch (status)
		{
		case GameStatus::logo:
			logoLoading();
			break;
		case GameStatus::mainmenu:
			mainmenu();
			break;
		case GameStatus::game:
			game();
			break;
		}
	}
}

void Game::logoLoading()
{
	window = new sf::RenderWindow(sf::VideoMode(670, 200), "Minesweeper", sf::Style::None);
	float a = 0;
	float fadecolor = 255;
	sf::Sprite logo;
	logo.setTexture(*TextureManager::AcquireTexture("res/logo.png"));
	logo.setOrigin(sf::Vector2f(logo.getTexture()->getSize().x / 2, logo.getTexture()->getSize().y / 2));
	logo.setPosition(window->getSize().x / 2, window->getSize().y / 2);

	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	window->setFramerateLimit(30);
	window->display();

	sf::Event evnt;

	float deltatime = 0;

	clock.restart().asSeconds();

	while (window->isOpen())
	{
		deltatime = clock.restart().asSeconds();
		while (window->pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				close = true;
				window->close();
				delete window;
				return;
			case sf::Event::KeyPressed:
				if (evnt.key.code == sf::Keyboard::Escape)
				{
					close = true;
					window->close();
					delete window;
					return;
				}
				else
				{
					status = GameStatus::mainmenu;
					window->close();
					delete window;
					return;
				}
				break;
			}
		}

		a += deltatime;

		if (a > 0.3)
		{
			if (a > 3)
				fadecolor *= 1 + (deltatime * 8);
			else
				fadecolor *= 1 - (deltatime * 2);
		}
		if (fadecolor >= 255)
			fadecolor = 255;
		if (fadecolor <= 1)
			fadecolor = 1;
		logo.setColor(sf::Color(255, 255, 255, -fadecolor));

		window->clear();
		window->draw(logo);
		window->display();

		if (a >= 3.8)
		{
			status = GameStatus::mainmenu;
			window->close();
			delete window;
			return;
		}
	}
}

void Game::mainmenu()
{
	if (first)
	{
		window = new sf::RenderWindow(sf::VideoMode(500, 740), "Minesweeper", sf::Style::Close || sf::Style::None);
		window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
		window->setFramerateLimit(15);
		window->display();
		first = false;
	}
	else
		window->setSize(sf::Vector2u(500, 740));
	
	sf::View view(sf::Vector2f(0, 0), sf::Vector2f(window->getSize()));
	window->setView(view);

	int xoffset = -80;
	int yoffset = -259;
	int ydistance = 105;

	sf::Text text[3];
	for (int i = 0; i < 3; i++)
	{
		text[i].setCharacterSize(102);
		text[i].setFont(*font);
		text[i].setFillColor(sf::Color(30, 133, 159));
		text[i].setPosition(view.getCenter().x + xoffset, view.getCenter().y + (i * 3 * 105) - 259);
	}
	text[0].setString("Play");
	text[1].setString("Credits");
	text[2].setString("Exit");
	text[2].setPosition(view.getCenter().x + xoffset, view.getCenter().y + 4*105 - 259);

	sf::Text difficultyText[3];
	for (int i = 0; i < 3; i++)
	{
		difficultyText[i].setFillColor(sf::Color(30, 133, 159));
		difficultyText[i].setFont(*font);
	}
		
	difficultyText[0].setString("Easy");
	difficultyText[1].setString("Medium");
	difficultyText[2].setString("Hard");
	sf::Text sizeText[6];
	for (int i = 0; i < 6; i++)
	{
		sizeText[i].setFillColor(sf::Color(30, 133, 159));
		sizeText[i].setFont(*font);
	}
	sizeText[0].setString("10x10");
	sizeText[1].setString("16x16");
	sizeText[2].setString("20x20");
	sizeText[3].setString("26x26");
	sizeText[4].setString("30x30");
	sizeText[5].setString("40x40");

	sf::Text creditsText;
	creditsText.setCharacterSize(80);
	creditsText.setFont(*font);
	creditsText.setFillColor(sf::Color(30, 133, 159));
	creditsText.setPosition(view.getCenter().x - 230, view.getCenter().y - 80);
	creditsText.setString("Klw_M Project\ngithub.com/Clwmm");

	sf::Event evnt;

	while (window->isOpen())
	{
		while (window->pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				close = true;
				return;
			case sf::Event::KeyPressed:
				switch (evnt.key.code)
				{
				case sf::Keyboard::Num6:
					size = 6;
					break;
				case sf::Keyboard::Escape:
					if (mmstatus == MainMenuStatus::creditsOpen)
					{
						mmstatus = MainMenuStatus::credits;
						break;
					}
					else
					{
						close = true;
						window->close();
						delete window;
						return;
					}
				case sf::Keyboard::Enter:
					switch (mmstatus)
					{
					case MainMenuStatus::play:
						status = GameStatus::game;
						return;
					case MainMenuStatus::credits:
						mmstatus = MainMenuStatus::creditsOpen;
						break;
					case MainMenuStatus::creditsOpen:
						mmstatus = MainMenuStatus::credits;
						break;
					case MainMenuStatus::exit:
						close = true;
						window->close();
						delete window;
						return;
					default:
						break;
					}
					break;
				case sf::Keyboard::Space:
					switch (mmstatus)
					{
					case MainMenuStatus::play:
						status = GameStatus::game;
						return;
					case MainMenuStatus::credits:
						mmstatus = MainMenuStatus::creditsOpen;
						break;
					case MainMenuStatus::creditsOpen:
						mmstatus = MainMenuStatus::credits;
						break;
					case MainMenuStatus::exit:
						close = true;
						window->close();
						delete window;
						return;
					default:
						break;
					}
					break;
				case sf::Keyboard::Down:
					switch (mmstatus)
					{
					case MainMenuStatus::play:
						mmstatus = MainMenuStatus::difficulty;
						break;
					case MainMenuStatus::difficulty:
						mmstatus = MainMenuStatus::size;
						break;
					case MainMenuStatus::size:
						mmstatus = MainMenuStatus::credits;
						break;
					case MainMenuStatus::credits:
						mmstatus = MainMenuStatus::exit;
						break;
					default:
						break;
					}
					break;
				case sf::Keyboard::Up:
					switch (mmstatus)
					{
					case MainMenuStatus::difficulty:
						mmstatus = MainMenuStatus::play;
						break;
					case MainMenuStatus::size:
						mmstatus = MainMenuStatus::difficulty;
						break;
					case MainMenuStatus::credits:
						mmstatus = MainMenuStatus::size;
						break;
					case MainMenuStatus::exit:
						mmstatus = MainMenuStatus::credits;
						break;
					default:
						break;
					}
					break;
				case sf::Keyboard::Right:
					switch (mmstatus)
					{
					case MainMenuStatus::difficulty:
						if (difficulty < 2)
							difficulty++;
						break;
					case MainMenuStatus::size:
						if (size < 5)
							size++;
						break;
					default:
						break;
					}
					break;
				case sf::Keyboard::Left:
					switch (mmstatus)
					{
					case MainMenuStatus::difficulty:
						if (difficulty > 0)
							difficulty--;
						break;
					case MainMenuStatus::size:
						if (size > 0)
							size--;
						break;
					default:
						break;
					}
					break;
				default:
					if (mmstatus == MainMenuStatus::creditsOpen)
						mmstatus = MainMenuStatus::credits;
					break;
				}
			default:
				break;
			}
		}

		switch (mmstatus)
		{
		case MainMenuStatus::creditsOpen:

			window->clear();
			window->draw(creditsText);
			window->display();

			break;
		default:

			for (int i = 0; i < 3; i++)
			{
				if (i == difficulty)
				{
					difficultyText[i].setCharacterSize(102);
					difficultyText[i].setPosition(view.getCenter().x + xoffset, view.getCenter().y - 154);
				}
				else if (i < difficulty)
				{
					difficultyText[i].setCharacterSize(51);
					difficultyText[i].setPosition(view.getCenter().x + (2*xoffset), view.getCenter().y - 65);
				}
				else if (i > difficulty)
				{
					difficultyText[i].setCharacterSize(51);
					difficultyText[i].setPosition(view.getCenter().x - xoffset, view.getCenter().y - 65);
				}
			}

			for (int i = 0; i < 6; i++)
			{
				if (i == size)
				{
					sizeText[i].setCharacterSize(102);
					sizeText[i].setPosition(view.getCenter().x + xoffset, view.getCenter().y - 49);
				}
				else if (i < size)
				{
					sizeText[i].setCharacterSize(51);
					sizeText[i].setPosition(view.getCenter().x + (2*xoffset), view.getCenter().y + 50);
				}
				else if (i > size)
				{
					sizeText[i].setCharacterSize(51);
					sizeText[i].setPosition(view.getCenter().x - xoffset, view.getCenter().y + 50);
				}
			}

			for (int i = 0; i < 6; i++)
			{
				if (i < 3)
					difficultyText[i].setFillColor(sf::Color(0, 45, 69));
				if (i < 3)
					text[i].setFillColor(sf::Color(0, 45, 69));
				sizeText[i].setFillColor(sf::Color(0, 45, 69));
			}

			switch (mmstatus)
			{
			case MainMenuStatus::play:
				text[0].setFillColor(sf::Color(30, 133, 159));
				break;
			case MainMenuStatus::difficulty:
				difficultyText[difficulty].setFillColor(sf::Color(30, 133, 159));
				break;
			case MainMenuStatus::size:
				sizeText[size].setFillColor(sf::Color(30, 133, 159));
				break;
			case MainMenuStatus::credits:
				text[1].setFillColor(sf::Color(30, 133, 159));
				break;
			case MainMenuStatus::exit:
				text[2].setFillColor(sf::Color(30, 133, 159));
				break;
			}

			window->clear();
			for (int i = 0; i < 3; i++)	window->draw(text[i]);
			for (int i = 0; i < 3; i++)
				if (abs(difficulty - i) <= 1)
					window->draw(difficultyText[i]);
			for (int i = 0; i < 6; i++)
				if (abs(size - i) <= 1)
					window->draw(sizeText[i]);
			window->display();

			break;
		}
	}
}

void Game::game()
{
	switch (size)
	{
	case 0:
		window->setSize(sf::Vector2u(220, 254));
		windowsize = sf::Vector2f(220, 254);
		break;
	case 1:
		window->setSize(sf::Vector2u(352, 386));
		windowsize = sf::Vector2f(352, 386);
		break;
	case 2:
		window->setSize(sf::Vector2u(440, 474));
		windowsize = sf::Vector2f(440, 474);
		break;
	case 3:
		window->setSize(sf::Vector2u(572, 606));
		windowsize = sf::Vector2f(572, 606);
		break;
	case 4:
		window->setSize(sf::Vector2u(660, 694));
		windowsize = sf::Vector2f(660, 694);
		break;
	case 5:
		window->setSize(sf::Vector2u(880, 914));
		windowsize = sf::Vector2f(880, 914);
		break;
	case 6:
		window->setSize(sf::Vector2u(880, 914));
		windowsize = sf::Vector2f(880, 914);
		break;
	}

	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	window->setFramerateLimit(30);
	window->display();
	
	MapGenerator map(size, difficulty, boxes);

	sf::View view(sf::Vector2f(0, 0), sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
	window->setView(view);

	window->setSize(sf::Vector2u(windowsize.x + (windowsetting * 25), windowsize.y + (windowsetting * 25)));

	sf::Text text;
	text.setCharacterSize(16);
	text.setFont(*font);
	text.setFillColor(sf::Color(30, 133, 159));
	text.setPosition(view.getCenter().x - view.getSize().x / 2 + 4, view.getCenter().y - view.getSize().y / 2 - 4);

	sf::Text wintext;
	wintext.setCharacterSize(18);
	wintext.setFont(*font);
	wintext.setFillColor(sf::Color(255, 255, 204));
	wintext.setPosition(view.getCenter().x - (view.getSize().x / 2) + 8, view.getCenter().y - 20);

	int countCursor = 0;
	bool leftMouse = false;
	bool rightMouse = false;
	bool middleMouse = false;
	bool hsbool = false;

	bool firsttouch = true;

	bool fl = true;

	int bombs = 0;
	int boxs = 0;
	float time = 0;
	lose = false;
	win = false;

	mapsize = MapGenerator::setMapSize(size);

	sf::Event evnt;

	clock.restart().asSeconds();

	while (window->isOpen())
	{
		if (lose)
		{
			if (fl)
			{
				bombs = 0;
				for (auto i : boxes)
					for (auto j : i)
					{
						if (j->stat == Stat::flagged && j->type != Type::bomb)
						{
							j->behind.setTexture(*TextureManager::AcquireTexture("res/wrongbomb.png"));
							j->stat = Stat::pressed;
							j->nobombs = 9;
						}
						if (j->type == Type::bomb && j->stat != Stat::flagged)
						{
							j->stat = Stat::pressed;
							bombs++;
						}
					}
				fl = false;
			}
		}
		if (win)
		{
			for (auto i : boxes)
				for (auto j : i)
					if (j->type == Type::bomb)
						j->stat = Stat::flagged;
			if (time < highscore[size][difficulty] || highscore[size][difficulty] == 0)
				highscore[size][difficulty] = time;
		}
			

		if (!win && !lose)
			time += clock.restart().asSeconds();
		leftMouse = false;
		rightMouse = false;
		middleMouse = false;
		boxs = 0;
		while (window->pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window->close();
				delete window;
				close = true;
				return;
			case sf::Event::MouseButtonPressed:
				switch (evnt.mouseButton.button)
				{
				case sf::Mouse::Button::Left:
					leftMouse = true;
					break;
				case sf::Mouse::Button::Right:
					rightMouse = true;
					break;
				case sf::Mouse::Button::Middle:
					middleMouse = true;
					break;
				}
			case sf::Event::KeyPressed:
				switch (evnt.key.code)
				{
				case sf::Keyboard::Up:
					if (windowsetting < 25)
						windowsetting++;
					window->setSize(sf::Vector2u(windowsize.x + (windowsetting*25), windowsize.y + (windowsetting * 25)));
					break;
				case sf::Keyboard::Down:
					if (windowsetting > 0)
						windowsetting--;
					window->setSize(sf::Vector2u(windowsize.x + (windowsetting * 25), windowsize.y + (windowsetting * 25)));
					break;
				case sf::Keyboard::H:
					hsbool = !hsbool;
					break;
				case sf::Keyboard::Enter:
					status = GameStatus::mainmenu;
					for (auto i : boxes)
					{
						for (auto j = i.begin(); j != i.end();)
						{
							Box* e = *j;
							j = i.erase(j);
							delete e;
						}
						i.clear();
					}
					boxes.clear();
					return;
				case sf::Keyboard::Space:
					status = GameStatus::mainmenu;
					for (auto i : boxes)
					{
						for (auto j = i.begin(); j != i.end();)
						{
							Box* e = *j;
							j = i.erase(j);
							delete e;
						}
						i.clear();
					}
					boxes.clear();
					return;
				case sf::Keyboard::Escape:
					status = GameStatus::mainmenu;
					for (auto i : boxes)
					{
						for (auto j = i.begin(); j != i.end();)
						{
							Box* e = *j;
							j = i.erase(j);
							delete e;
						}
						i.clear();
					}
					boxes.clear();
					return;
				
				}
			}
		}

		sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
		countCursor = 0;

		if (!win && !lose)
		{
			bombs = 0;
			for (auto j : boxes)
				for (auto i : j)
				{
					switch (i->type)
					{
					case Type::bomb:
						bombs++;
						break;
					case Type::normal:
						if (i->stat != Stat::pressed)
							boxs++;
						break;
					}

					if (i->stat == Stat::flagged)
						bombs--;

					sf::FloatRect boundingBox = i->box.getGlobalBounds();
					sf::Vector2f point = window->mapPixelToCoords(pixelPos);
					if (boundingBox.contains(point))
					{
						switch (i->stat)
						{
						case Stat::normal:
							countCursor++;
							if (leftMouse)
							{
								if (firsttouch && size != 6)
								{
									if (i->type == Type::bomb)
									{
										MapGenerator::mapregenerate(size, difficulty, boxes, i->i, i->j);
										clearing(i->i, i->j);
									}
									else
									{
										if (i->nobombs == 0)
											clearing(i->i, i->j);
										else
										{
											MapGenerator::mapregenerate(size, difficulty, boxes, i->i, i->j);
											clearing(i->i, i->j);
										}
									}

									firsttouch = false;
								}
								else
								{
									if (i->type == Type::bomb)
									{
										i->behind.setTexture(*TextureManager::AcquireTexture("res/redbomb.png"));
										lose = true;
									}
									else
									{
										if (i->nobombs == 0)
											clearing(i->i, i->j);
										else
											i->stat = Stat::pressed;
									}
								}
							}
							if (rightMouse)
								i->stat = Stat::flagged;
							break;

						case Stat::flagged:
							if (rightMouse)
								i->stat = Stat::normal;
							break;

						case Stat::pressed:
							if (middleMouse || leftMouse)
								midclear(i->i, i->j);
							break;

						}
					}
				}
		}

		if (boxs <= 0 && !lose)
			win = true;
		
		if (countCursor > 0)
			window->setMouseCursor(handcursor);
		else
			window->setMouseCursor(pointingcursor);

		if (win)
			text.setFillColor(sf::Color(100, 184, 100));
		if (lose)
			text.setFillColor(sf::Color(173, 50, 58));

		window->clear(sf::Color(191, 191, 191));
		for (auto i : boxes)
			for (auto j : i)
				j->draw(window, hsbool);
		if(!hsbool)
			drawTextWithShadow(window, text, "Bombs: " + std::to_string(bombs) + "  Time: " + std::to_string(static_cast<int>(time)), 1);
		else
		{
			if (highscore[size][difficulty] == 0)
				drawTextWithShadow(window, text, "Bombs: " + std::to_string(bombs) + "  HS: ---", 1);
			else
				drawTextWithShadow(window, text, "Bombs: " + std::to_string(bombs) + "  HS: " + std::to_string(static_cast<int>(highscore[size][difficulty])), 1);
		}
		if (win)
			drawTextWithShadow(window, wintext, "Time: " + std::to_string(static_cast<int>(time)) + "\nHighScore : " + std::to_string(static_cast<int>(highscore[size][difficulty])), 1);
		window->display();
	}
}

void Game::clearing(int  i, int j)
{
	boxes[i][j]->stat = Stat::pressed;

	std::vector<Box*> temp;

	if (i - 1 >= 0 && j - 1 >= 0)
		temp.push_back(boxes[i - 1][j - 1]);
	if (i + 1 < mapsize && j + 1 < mapsize)
		temp.push_back(boxes[i + 1][j + 1]);
	if (i + 1 < mapsize && j - 1 >= 0)
		temp.push_back(boxes[i + 1][j - 1]);
	if (i - 1 >= 0 && j + 1 < mapsize)
		temp.push_back(boxes[i - 1][j + 1]);
	if (j + 1 < mapsize)
		temp.push_back(boxes[i][j + 1]);
	if (j - 1 >= 0)
		temp.push_back(boxes[i][j - 1]);
	if (i + 1 < mapsize)
		temp.push_back(boxes[i + 1][j]);
	if (i - 1 >= 0)
		temp.push_back(boxes[i - 1][j]);

	for (auto k : temp)
		if (k->stat != Stat::pressed)
		{
			k->stat = Stat::pressed;
			if (k->nobombs == 0)
				clearing(k->i, k->j);
		}
}

void Game::midclear(int i, int j)
{
	bool losed = false;
	int a = boxes[i][j]->nobombs;
	int b = 0;
	std::vector<Box*> temp;

	if (i - 1 >= 0 && j - 1 >= 0)
		temp.push_back(boxes[i - 1][j - 1]);
	if (i + 1 < mapsize && j + 1 < mapsize)
		temp.push_back(boxes[i + 1][j + 1]);
	if (i + 1 < mapsize && j - 1 >= 0)
		temp.push_back(boxes[i + 1][j - 1]);
	if (i - 1 >= 0 && j + 1 < mapsize)
		temp.push_back(boxes[i - 1][j + 1]);
	if (j + 1 < mapsize)
		temp.push_back(boxes[i][j + 1]);
	if (j - 1 >= 0)
		temp.push_back(boxes[i][j - 1]);
	if (i + 1 < mapsize)
		temp.push_back(boxes[i + 1][j]);
	if (i - 1 >= 0)
		temp.push_back(boxes[i - 1][j]);

	for (auto i : temp)
		if (i->stat == Stat::flagged)
			b++;

	if (a == b)
	{
		for (auto i : temp)
		{
			if (i->type == Type::bomb && i->stat != Stat::flagged)
			{
				losed = true;
				i->behind.setTexture(*TextureManager::AcquireTexture("res/redbomb.png"));
			}
			if (i->stat == Stat::flagged && i->type != Type::bomb)
			{
				losed = true;
			}
		}
		if (losed)
		{
			lose = true;
			return;
		}
		for (auto i : temp)
		{
			if (i->type == Type::normal && i->nobombs == 0)
				clearing(i->i, i->j);
			else if (i->type == Type::normal)
				i->stat = Stat::pressed;
		}
	}
}

void Game::drawTextWithShadow(sf::RenderWindow* window, sf::Text& text, std::string string, int offset)
{
	text.setString(string);
	text.setPosition(sf::Vector2f(text.getPosition().x + offset, text.getPosition().y + offset));
	sf::Color color = text.getFillColor();
	text.setFillColor(sf::Color::Black);
	window->draw(text);
	text.setPosition(sf::Vector2f(text.getPosition().x - offset, text.getPosition().y - offset));
	text.setFillColor(color);
	window->draw(text);
}
