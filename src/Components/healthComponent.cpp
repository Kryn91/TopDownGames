#include "Components/healthComponent.hpp"

	HealthComponent::HealthComponent(int initialHealth)
	: health(initialHealth), alive(true) {}

void HealthComponent::takeDamage(int damage)
{
	health -= damage;
	if (health <= 0)
	{
		health = 0;
		alive = false;
	}
}

bool HealthComponent::isAlive()const
{
	return(alive);
}

int HealthComponent::getHealth()const
{
	return(health);
}
