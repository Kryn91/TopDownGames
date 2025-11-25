#include "Core/texture_manager.h"

bool TextureManager::loadTexture(const std:string& name, const std::string& filename)
{
	sf::Texture texture;

	if (!texture.loadFromFile(filename))
		return (false);

	textures[name] = texture;
	return (true);
}

sf::Texture& TextureManager::getTexture(const std::string& name)
{
	return (texture.at(name));
}

void TextureManager::clearTexture()
{
	textures.clear();
}
