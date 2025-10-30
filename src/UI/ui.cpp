#include "UI/ui.hpp"

DamagePopup::DamagePopup(const sf::Font& font, const std::string& str, sf::Vector2f position)
	: text (font, str, 24)
{
	text.setFillColor(sf::Color::White);
	text.setPosition(position);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(2);

	velocity = {0.f, -50.f};
}

void	DamagePopup::update(float dt)
{

	text.move(velocity * dt);
	
	lifeTime -= dt;

	sf::Color color = text.getFillColor();
	if (lifeTime < 0.5f && color.a > 5)
		color.a -= static_cast<uint8_t>(200 * dt);
	text.setFillColor(color);
}

void	DamagePopup::draw(sf::RenderWindow& window)
{
		window.draw(text);
}

bool	DamagePopup::isAlive() const
{
	return (lifeTime > 0.f);
}
