#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "enemy.hpp"
#include <cmath>
#include <vector>

int main(void)
{
	sf::RenderWindow window(sf::VideoMode({1920,1080}), "GAMES");
	window.setFramerateLimit(60);
//world
	float worldWidth = 3000.f;
	float worldHeight = 2000.f;
//player
	Player player;							
	player.setPosition({960.f,540.f});
	
//enemy
	Enemy enemy;
	enemy.setPosition({1000,800});
//wall

	std::vector<sf::RectangleShape> walls;
	sf::RectangleShape wall1({400.f, 40.f});
	wall1.setPosition({760.f, 1000.f});
	wall1.setFillColor(sf::Color::Blue);
	walls.push_back(wall1);
	
	sf::RectangleShape wall2({200.f, 40.f});
	wall2.setPosition({500.f, 100.f});
	wall2.setFillColor(sf::Color::Blue);
	walls.push_back(wall2);

//camera
	sf::View camera;
	camera.setSize(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
	camera.setCenter(player.getPosition());

//temp en jeux
	sf::Clock clock;

//boucle de jeux
	while (window.isOpen())
	{
		while (const std::optional event= window.pollEvent())
		{
			if(event->is<sf::Event::Closed>())
			window.close();
		}
	float dt = clock.restart().asSeconds();

//player udapte
	player.update(dt, walls);

//melee update

	auto meleeHitbox = player.getMeleeHitbox();
	if (meleeHitbox.has_value() && enemy.isAlive())
	{
		sf::FloatRect hitbox = meleeHitbox.value();
		sf::FloatRect enemyBox = enemy.getBounds();

		bool isColliding =
			hitbox.position.x < enemyBox.position.x + enemyBox.size.x &&
			hitbox.position.x + hitbox.size.x > enemyBox.position.x &&
			hitbox.position.y < enemyBox.position.y + enemyBox.position.y &&
			hitbox.position.y + hitbox.size.y > enemyBox.position.y;
		if (isColliding && !player.getHasHitEnemy())
		{
			enemy.takeDamage(20);
			player.setHasHitEnemy(true);
		}
	}

//camera update
	sf::Vector2f viewSize = camera.getSize();
	sf::Vector2f halfSize = viewSize / 2.f;
	sf::Vector2f center = player.getPosition();

	if (center.x < halfSize.x)
	       	center.x = halfSize.x;
	if (center.y < halfSize.y)
	       	center.y = halfSize.y;
	if (center.x > worldWidth - halfSize.x)
	       	center.x = worldWidth - halfSize.x;
	if (center.y > worldHeight - halfSize.y)
	       	center.y = worldHeight - halfSize.y;

	camera.setCenter(player.getPosition());
	window.setView(camera);
	
//draw
	window.clear(sf::Color::Black);
	for (auto&wall : walls) window.draw(wall);
	player.draw(window);
	enemy.draw(window);
	window.display();
	}
	return(0);
}
