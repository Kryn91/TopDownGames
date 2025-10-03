#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

//player
struct player
{
	sf::RectangleShape body;
	float speed = 250.f;
	
	player()
       	{
		body.setSize({50,50});
		body.setOrigin({25.f, 25.f});
		body.setFillColor(sf::Color::White);
	}
	void setPosition(const sf::Vector2f& pos)
	{
		body.setPosition(pos);
	}
	sf::Vector2f getPosition(void) const
	{
		return(body.getPosition());
	}
	sf::FloatRect getBounds() const
	{
		return (body.getGlobalBounds());
	}
	void updatePosition(float dt, const std::vector<sf::RectangleShape>& walls)
	{
	//mouvements
		sf::Vector2f dir{0.f,0.f};

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
       			dir.y -= 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	       		dir.y += 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	       		dir.x -= 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
       			dir.x += 1;
	//normlisation(vitesse constante)
		float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
		if (len > 0)
			dir /= len;
		sf::Vector2f movement = dir * speed * dt;

	//deplacement sur X
		body.move({movement.x, 0.f});
		for (const auto& wall : walls)
		{
			if (getBounds().findIntersection(wall.getGlobalBounds()))
			{
				body.move({-movement.x, 0.0f});
				break;
			}
		}
	//deplacement sur Y
		body.move({0.f, movement.y});
		for (const auto &wall : walls)
		{
			if(getBounds().findIntersection(wall.getGlobalBounds()))
			{
				body.move({0.f, -movement.y});
			break;
			}
		}
	}

	void draw(sf::RenderTarget& target)
	{
		target.draw(body);
	}
};

int main(void)
{
	sf::RenderWindow window(sf::VideoMode({1920,1080}), "GAMES");
	window.setFramerateLimit(60);
//world
	float worldWidth = 3000.f;
	float worldHeight = 2000.f;
//player
	player player;							
	player.setPosition({960.f,540.f});
	
	std::vector<sf::RectangleShape> walls;
//wall
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
	player.updatePosition(dt, walls);

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

	//limite de camera a implementer
	camera.setCenter(player.getPosition());
	window.setView(camera);
	
//draw
	window.clear(sf::Color::Black);
	for (auto&wall : walls) window.draw(wall);
	player.draw(window);
	window.display();
	}
	return(0);
}
