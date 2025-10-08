#include "player.hpp"
#include <cmath>

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

void Player::updatePosition(float dt, const std::vector<sf::RectangleShape>& walls)
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
    if (len > 0) dir /= len;

    sf::Vector2f movement = dir * speed * dt;

    // Déplacement sur X
    body.move({movement.x, 0.f});
    for (const auto& wall : walls)
    {
        if (getBounds().findIntersection(wall.getGlobalBounds()))
       	{
            body.move({-movement.x, 0.0f});
            break;
        }
    }

    // Déplacement sur Y
    body.move({0.f, movement.y});
    for (const auto& wall : walls)
    {
        if (getBounds().findIntersection(wall.getGlobalBounds()))
       	{
            body.move({0.f, -movement.y});
            break;
        }
    }
}

void Player::draw(sf::RenderTarget& target) const
{
    target.draw(body);
}
