#pragma once
#include <SFML/Graphics.hpp>
#include "Entities/player.hpp"
#include "Entities/enemy.hpp"
#include <vector>


class	Game
{
public:
	Game();
	void run(void);
private:
	sf::RenderWindow window;
	sf::Clock clock;
	sf::View camera;

	Player player;
	std::vector<Enemy> enemies;
	std::vector<sf::RectangleShape> walls;

	void	handleEvent(void);
	void 	spawnEnemy(float x, float y);
	void	update(float dt);
	void	render(void);
};
