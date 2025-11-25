#pragma once
#include <SFML/Graphics.hpp>
#include "Entities/enemy.hpp"
#include "Entities/player.hpp"
#include "Core/texture_manager.hpp"
#include "UI/ui.hpp"
#include <vector>

class Game;

class World
{
private:
	Player* player = nullptr;
public:
	World();
	void	init();
	void spawnEnemiesInitial(const sf::Texture& enemyTex);
	void update(float dt);
	void render(sf::RenderWindow &window);
	void checkPlayerAttack(const sf::FloatRect& attackBox);

	std::vector<Enemy>& getEnemies(void);
	void	setPlayer(Player& p) {player = &p;}
private:
	std::vector<Enemy> enemies;
	std::vector<DamagePopup> damagePopups;
	sf::Font font;

};
