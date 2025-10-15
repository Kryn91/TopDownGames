#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Player
{
public:
    Player();

    void setPosition(const sf::Vector2f& pos);
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    bool getHasHitEnemy()const;
    void setHasHitEnemy(bool value);
    void handleInput(const sf::RenderWindow& window);
    void update(float dt, const std::vector<sf::RectangleShape>& walls);
    std::optional<sf::Rect<float>> getMeleeHitbox() const;
    void draw(sf::RenderTarget& target) const;

private:
    void attack(const sf::Vector2f& targetPos);
    void setRotation(float angle);
private:
    sf::RectangleShape body;
    float speed = 250.f;
    float attackCooldown = 0.8f;
    float attackDuration = 0.25f;
    float attackTimer = 0.f;
    float attackActiveTimer = 0.f;
    float meleeRange = 70.f;
    bool hasHitEnemy = false;
    sf::Vector2f attackDir{1.f, 0.f};
};
