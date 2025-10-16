#include "Core/world.hpp"
#include <algorithm>

World::World()
{
	spawnEnemiesInitial();
}
void	World::spawnEnemiesInitial()
{
	enemies.push_back(Enemy());
	enemies.push_back(Enemy());
	enemies.push_back(Enemy());

	enemies[0].setPosition({1000.f, 800.f});
	enemies[1].setPosition({1200.f, 600.f});
	enemies[2].setPosition({1400.f, 400.f});
}

void	World::update(float dt)
{
	enemies.erase(
		std::remove_if(enemies.begin(), enemies.end(),
			[](const Enemy& e) { return e.readyToRemove();}),
		enemies.end()
	);
}

void	World::render(sf::RenderWindow &window)
{
	for (Enemy &e :enemies)
	{
		if(e.isAlive())
			e.draw(window);
	}
}

std::vector<Enemy>&	World::getEnemies(void)
{
	return (enemies);
}
