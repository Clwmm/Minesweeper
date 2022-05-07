#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "Game.h"

std::unordered_map<std::string, std::shared_ptr<sf::Texture>> TextureManager::texturePointers;

int main()
{
	FreeConsole();
	srand(time(0));
	Game* game = new Game;
	game->start();
	delete game;
	return 0;
}