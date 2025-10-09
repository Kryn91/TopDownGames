#include "player.hpp"
#include <cmath>
#include <iostream>

Player::Player()
{
    body.setSize({50.f, 50.f});
    body.setOrigin({25.f, 25.f});
    body.setFillColor(sf::Color::White);
}

void Player::setPosition(const sf::Vector2f& pos)
{
    body.setPosition(pos);
}

sf::Vector2f Player::getPosition() const
{
    return body.getPosition();
}

sf::FloatRect Player::getBounds() const
{
    return body.getGlobalBounds();
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

    // Déplacement et colisions
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
    //Timers
    attackTimer -= dt;
    if (attackActiveTimer > 0.f)
	    attackActiveTimer -= dt;

    //mélée
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && attackTimer <= 0.f)
    {
	attackTimer = attackCooldown;
	attackActiveTimer = attackDuration;
	std::cout << "coup de mélée declancher !\n";
    }
}

std::optional<sf::Rect<float>> Player::getMeleeHitbox() const
{
	if (attackActiveTimer <= 0)
		return(std::nullopt);
	sf::Vector2f c = body.getPosition();
	sf::Vector2f size(meleeRange, body.getSize().y * 0.9f);
	sf::Rect<float> rect(sf::Vector2f(c.x + 30.f, c.y - size.y / 2.f),size);
	return(rect);
}

void Player::draw(sf::RenderTarget& target) const
{
    target.draw(body);
    if (auto hitbox = getMeleeHitbox())
	   {
		   sf::RectangleShape hitRect;
		   hitRect.setPosition(hitbox->position);
		   hitRect.setSize(hitbox->size);
		   hitRect.setFillColor(sf::Color(255, 0, 0, 120));
		   target.draw(hitRect);
	   }
}
