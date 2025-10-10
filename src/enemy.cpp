#include "enemy.hpp"
#include <iostream>

Enemy::Enemy()
{
	body.setSize({50.f,50.f});
	body.setOrigin({25.f, 25.f});
	body.setFillColor(sf::Color::Red);
	hp = 100;
}

void Enemy::draw(sf::RenderTarget& target)const
{
	target.draw(body);
}

void Enemy::setPosition(sf::Vector2f pos)
{
	body.setPosition(pos);
}
