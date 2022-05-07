#include "TextureManager.h"

std::shared_ptr<sf::Texture> TextureManager::AcquireTexture(const std::string& name)
{
	const auto i = texturePointers.find(name);
	if (i != texturePointers.end())
	{
		return i->second;
	}
	else
	{
		auto pTex = std::make_shared<sf::Texture>();
		pTex->loadFromFile(name);
		texturePointers.insert({ name, pTex });
		return pTex;
	}
}
