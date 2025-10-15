#pragma once
#include <SFML/Graphics.hpp>
#include "Entities/player.hpp"
#include "Entities/enemy.hpp"

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
