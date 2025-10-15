#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
private:
	sf::RectangleShape body;
	int hp;
public:
	Enemy();

	void setPosition(const sf::Vector2f pos);
	sf::FloatRect getBounds()const;
	void draw(sf::RenderTarget& target)const;
	void takeDamage(int amount);
	bool isAlive()const;
};
