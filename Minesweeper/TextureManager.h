#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <unordered_map>

class TextureManager
{
public:
	static std::shared_ptr<sf::Texture> AcquireTexture(const std::string& name);
private:
	static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> texturePointers;
};