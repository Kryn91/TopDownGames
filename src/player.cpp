#include "player.hpp"
#include <cmath>
#include <iostream>

Player::Player()
{
	body.setSize({50.f, 50.f});
	body.setOrigin({25.f, 25.f});
	body.setFillColor(sf::Color::White);
}
//public
void Player::setPosition(const sf::Vector2f& pos)
{
	body.setPosition(pos);
}

sf::Vector2f Player::getPosition() const
{
	return body.getPosition();
}

void Player::setRotation(float angle)
{
	body.setRotation(sf::degrees(angle));
}

sf::FloatRect Player::getBounds() const
{
	return body.getGlobalBounds();
}

bool Player::getHasHitEnemy() const
{
	return(hasHitEnemy);
}

void Player::setHasHitEnemy(bool value)
{
	hasHitEnemy = value;
}
void Player::handleInput(const sf::RenderWindow& window)
{
	sf::Vector2f mouseWorld = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	sf::Vector2f dir = mouseWorld - body.getPosition();
	float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
	if (length != 0.f)
		dir /= length;
	if (dir.x != 0.f || dir.y != 0.f)
	{
		float angle = std::atan2(dir.y, dir.x) * 180.f / 3.14159265f;
		setRotation(angle);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && attackTimer <= 0.f)
	{
		attackTimer = attackCooldown;
		attackActiveTimer = attackDuration;
		hasHitEnemy = false;
		attackActiveTimer = 0.2f;
		attack(mouseWorld);
    	}

}

void Player::update(float dt, const std::vector<sf::RectangleShape>& walls)
{
	sf::Vector2f dir{0.f, 0.f};

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
		dir.y -= 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		dir.y += 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	    	dir.x -= 1;
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	    	dir.x += 1;

    	float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    	if (len > 0) 
		dir /= len;
    	sf::Vector2f movement = dir * speed * dt;

    	// Déplacement et colisions------------------------------------------------
    	body.move({movement.x, 0.f});
    	for (const auto& wall : walls)
    	{
        	if (getBounds().findIntersection(wall.getGlobalBounds()))
       		{
            		body.move({-movement.x, 0.0f});
            		break;
        	}
    	}
    	body.move({0.f, movement.y});
    	for (const auto& wall : walls)
    	{
        	if (getBounds().findIntersection(wall.getGlobalBounds()))
       		{
            		body.move({0.f, -movement.y});
            		break;
        	}
    	}
    	//attaque------------------------------------------------------------------
    	////Timers
	attackTimer -= dt;
	if (attackActiveTimer > 0.f)
	    attackActiveTimer -= dt;
}

std::optional<sf::Rect<float>> Player::getMeleeHitbox() const
{
	if (attackActiveTimer <= 0)
		return(std::nullopt);
	sf::Vector2f playerPos = body.getPosition();
	sf::Vector2f bodySize = body.getSize();

	sf::Vector2f size(meleeRange, bodySize.y * 0.9f);
	sf::Vector2f pos = playerPos;
	pos += attackDir * (meleeRange * 0.5f);
	
	pos.x -= size.x * 0.5f;
	pos.y -= size.y * 0.5f;
	return(sf::Rect<float>(pos, size));
}

void Player::draw(sf::RenderTarget& target) const
{
	target.draw(body);
    	if (attackActiveTimer > 0.f)
	{
		sf::Vector2f size(meleeRange, body.getSize().y * 0.9f);
		sf::Vector2f pos = body.getPosition();

		sf::Vector2f hitBoxCenter = pos + attackDir * (meleeRange * 0.5f);

		sf::RectangleShape hitRect(size);
		hitRect.setOrigin(sf::Vector2f ({size.x * 0.5f, size.y * 0.5f}));
		hitRect.setPosition(hitBoxCenter);

		float angle = std::atan2(attackDir.y, attackDir.x) * 180.f / 3.14159265f;
		hitRect.setRotation(sf::degrees(angle));

		hitRect.setFillColor(sf::Color(255, 0, 0, 120));
		target.draw(hitRect);
	}
}
//private
void Player::attack(const sf::Vector2f& targetPos)
{
	attackDir = targetPos - body.getPosition();
	float length = std::sqrt(attackDir.x * attackDir.x + attackDir.y * attackDir.y);
	if (length != 0.f)
		attackDir /= length;
	attackActiveTimer = attackDuration;
}

