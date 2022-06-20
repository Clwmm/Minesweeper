#pragma once
#include <SFML/Graphics.hpp>
#include "MapGenerator.h"
#include "TextureManager.h"
#include "Box.h"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

enum class GameStatus { logo, mainmenu, game};
enum class MainMenuStatus { play, difficulty, size, highscore, credits, creditsOpen, exit };

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
	int windowsetting = 0;
	sf::Vector2f windowsize;

	bool lose = false;
	bool win = false;

	int highscore[6][3];

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
	void midclear(int i, int j);
	void clearing(int i, int j);
	void drawTextWithShadow(sf::RenderWindow* window, sf::Text& text, std::string string, int offset);

private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive& a, const unsigned version)
	{
		a & windowsetting & highscore;
	}
};