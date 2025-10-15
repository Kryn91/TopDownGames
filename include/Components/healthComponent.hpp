#pragma once

class HealthComponent 
{
private:
	int health;
	bool alive;
public:
	HealthComponent(int intialHealth);

	void takeDamage(int amount);
	bool isAlive()const;
	int getHealth()const;
};
