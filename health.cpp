#include "health.h"

Health::Health(){}

int Health::getHealth() const
{
    return health;
}

int Health::getMaxHealth()
{
    return maxHealth;
}
void Health::setHealth(int number)
{
    health = number;
}

void Health::setMaxHealth(int number)
{
    maxHealth = number;
}

void Health::decrementHealth()
{
    health--;
}

void Health::incrementHealth()
{
    health++;
}
