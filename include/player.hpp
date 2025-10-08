#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Player {
private:
    sf::RectangleShape body;
    float speed = 250.f;

public:
    Player();

    void setPosition(const sf::Vector2f& pos);
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;

    void updatePosition(float dt, const std::vector<sf::RectangleShape>& walls);
    void draw(sf::RenderTarget& target) const;
};
