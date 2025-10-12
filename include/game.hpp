#pragma once
#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "enemy.hpp"
//#include <cmath>
//#include <vector>

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
	Enemy enemy;
	std::vector<sf::RectangleShape> walls;

	void	handleEvent(void);
	void	update(float dt);
	void	render(void);
};
