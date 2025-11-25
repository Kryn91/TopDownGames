#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string.h>

class TextureManager
{
public:
	static TextureManager& get();
	
	bool loadTexture(const std::string& name, const std::string& filename);
	sf::Texture& getTexture(const std::string& name);
	void clearTextures();
private:
	TextureManager() = default;
	std::map<std::string, sf::Texture> textures;
};
