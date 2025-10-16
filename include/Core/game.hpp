#pragma once
#include <SFML/Graphics.hpp>
#include "Entities/player.hpp"
#include "Entities/enemy.hpp"
#include "Core/world.hpp"
#include <vector>


class	Game
{
public:
	Game();
	void run(void);
	void	update(float dt);
	void	render(void);
private:
	sf::RenderWindow window;
	sf::Clock clock;
	sf::View camera;
	World world;

	Player player;
	std::vector<sf::RectangleShape> walls;

	void	handleEvent(void);
};
