#include "Core/texture_manager.hpp"

TextureManager& TextureManager::get()
{
	static TextureManager instance;
	return (instance);
}

bool TextureManager::loadTexture(const std::string& name, const std::string& filename)
{
	sf::Texture texture;

	if (!texture.loadFromFile(filename))
		return (false);

	textures[name] = texture;
	return (true);
}

sf::Texture& TextureManager::getTexture(const std::string& name)
{
	return (textures.at(name));
}

void TextureManager::clearTextures()
{
	textures.clear();
}
