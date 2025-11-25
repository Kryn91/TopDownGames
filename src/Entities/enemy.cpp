#include "Entities/enemy.hpp"
#include <iostream>

Enemy::Enemy(const sf::Texture& tex)
       	:sprite(tex),  health(100)
{
	sprite.setTexture(tex);
	sprite.setOrigin({25.f, 25.f});
	sprite.setScale({100.f /tex.getSize().x, 100.f /tex.getSize().y});
}

void	Enemy::draw(sf::RenderTarget& target)const
{
	target.draw(sprite);
}

void	Enemy::setPosition(sf::Vector2f pos)
{
	sprite.setPosition(pos);
}

sf::Vector2f	Enemy::getPosition()const
{
	return	(sprite.getPosition());
}

sf::FloatRect	Enemy::getBounds()const
{
	return (sprite.getGlobalBounds());
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
