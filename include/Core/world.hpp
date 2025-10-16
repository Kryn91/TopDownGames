#pragma once
#include "Entities/enemy.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class World
{
public:
	World();
	void update(float dt);
	void render(sf::RenderWindow &window);

	std::vector<Enemy>& getEnemies(void);
private:
	std::vector<Enemy> enemies;
	void spawnEnemiesInitial();
};
