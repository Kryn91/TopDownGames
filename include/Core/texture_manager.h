#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>

class TextureManager
{
public:
	static TextureManager& get();

	bool loadtexture(const std::string& name, const std::string& filename);
	sf::Texture& getTexture(const std::string& name);
	void clearTextures();
private:
	TextureManager() = default;
	std::map<std::string, sf::Texture> textures;
};
