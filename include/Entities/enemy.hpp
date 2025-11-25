#pragma once
#include <SFML/Graphics.hpp>
#include "Components/healthComponent.hpp"
#include "Core/texture_manager.hpp"

class Enemy
{
private:
	sf::RectangleShape body;
	sf::Sprite sprite;
	sf::Texture texture;
	//int hp;
	HealthComponent	health;
public:
	Enemy(const sf::Texture& tex);

	void	setPosition(const sf::Vector2f pos);
	sf::Vector2f	getPosition()const;
	sf::FloatRect	getBounds()const;
	void	draw(sf::RenderTarget& target)const;
	void	takeDamage(int amount);
	bool	isAlive()const;
	bool	readyToRemove()const;
};
