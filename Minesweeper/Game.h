#pragma once
#include <SFML/Graphics.hpp>
#include "MapGenerator.h"
#include "TextureManager.h"
#include "Box.h"

enum class GameStatus { logo, mainmenu, game};
enum class MainMenuStatus { play, difficulty, size, credits, creditsOpen, exit };

class Game
{
private:
	sf::RenderWindow* window = nullptr;
	sf::Image icon;
	GameStatus status = GameStatus::logo;
	MainMenuStatus mmstatus = MainMenuStatus::play;

	std::vector<std::vector<Box*>> boxes;

	sf::Font* font = new sf::Font;

	char size = 0;
	char difficulty = 0;
	int mapsize = 0;

	bool first = true;

	sf::Clock clock;

private:
	sf::Cursor pointingcursor;
	sf::Cursor handcursor;
public:
	bool close = false;
	Game();
	void start();
private:
	void logoLoading();
	void mainmenu();
	void game();
private:
	void clearing(int i, int j);
	void drawTextWithShadow(sf::RenderWindow* window, sf::Text& text, std::string string, int offset);
};

