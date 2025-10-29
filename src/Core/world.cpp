#include "Core/world.hpp"
#include <algorithm>
#include <iostream>

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
void	World::checkPlayerAttack(const sf::FloatRect& attackBox)
{
//melee Colision
	auto meleeHitbox = player->getMeleeHitbox();
	if (meleeHitbox.has_value())
	{
		for (Enemy & e: getEnemies())
		{
			sf::FloatRect hitbox = meleeHitbox.value();
			sf::FloatRect enemyBox = e.getBounds();
			bool isColliding =
			hitbox.position.x < enemyBox.position.x + enemyBox.size.x &&
			hitbox.position.x + hitbox.size.x > enemyBox.position.x &&
			hitbox.position.y < enemyBox.position.y + enemyBox.position.y &&
			hitbox.position.y + hitbox.size.y > enemyBox.position.y;
			if (e.isAlive() && isColliding && !player->getHasHitEnemy())
			{
				e.takeDamage(20);
				player->setHasHitEnemy(true);
			}
		}
	}
}

void	World::update(float dt)
{
	if (!player)
		return;

	auto attackBox = player->getMeleeHitbox();
	if (attackBox.has_value())
		checkPlayerAttack(attackBox.value());
	else
		player->setHasHitEnemy(false);
	enemies.erase(
		std::remove_if(enemies.begin(), enemies.end(),
			[](const Enemy& e) { return e.readyToRemove();}),
		enemies.end()
	);
	damagePopups.erase(
		std::remove_if(damagePopups.begin(), damagePopups.end(),
			[](const DamagePopup& p) {return !p.isAlive();}),
		damagePopups.end()
	);
}

void	World::render(sf::RenderWindow &window)
{
	for (Enemy &e :enemies)
	{
		if(e.isAlive())
			e.draw(window);
	}
	//draw popup
}

std::vector<Enemy>&	World::getEnemies(void)
{
	return (enemies);
}
