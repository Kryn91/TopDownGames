#pragma once
#include <SFML/Graphics.hpp>

class DamagePopup
{
private:
	sf::Text text;
	sf::Vector2f velocity;
	float lifeTime = 1.f;

public:
	DamagePopup(const sf::Font& font, const std::string& str, sf::Vector2f position);

	void	update(float dt);
	void	draw(sf::RenderWindow& window);
	bool	isAlive() const;
};
