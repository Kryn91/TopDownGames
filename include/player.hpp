#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Player
{
private:
    sf::RectangleShape body;
    float speed = 250.f;
    float attackCooldown = 0.8f;
    float attackDuration = 0.25f;
    float attackTimer = 0.f;
    float attackActiveTimer = 0.f;
    float meleeRange = 70.f;

public:
    Player();

    void setPosition(const sf::Vector2f& pos);
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;

    void update(float dt, const std::vector<sf::RectangleShape>& walls);
    void draw(sf::RenderTarget& target) const;
    std::optional<sf::Rect<float>> getMeleeHitbox() const;
};
