#include "Entities/enemy.hpp"
#include <iostream>

Enemy::Enemy() : health(100)
{
	body.setSize({50.f,50.f});
	body.setOrigin({25.f, 25.f});
	body.setFillColor(sf::Color::Red);
}

void	Enemy::draw(sf::RenderTarget& target)const
{
	target.draw(body);
}

void	Enemy::setPosition(sf::Vector2f pos)
{
	body.setPosition(pos);
}

sf::Vector2f	Enemy::getPosition()const
{
	return	(body.getPosition());
}

sf::FloatRect	Enemy::getBounds()const
{
	return (body.getGlobalBounds());
}

void	Enemy::takeDamage(int amount)
{
	health.takeDamage(amount);
       std::cout << "L'enemmi a subi " << amount << "degats ! HP restant : "<< health.getHealth() << std::endl;
}

bool	Enemy::isAlive()const
{
	return(health.isAlive());
}

bool	Enemy::readyToRemove()const
{
	return(health.getHealth() <= 0);
}
