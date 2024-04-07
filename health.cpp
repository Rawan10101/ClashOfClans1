#include "health.h"

Health::Health()
    : health(100)
{
}

int Health::getHealth() const
{
    return health;
}

void Health::reduceHealth()
{
    health -= 10;
    if (health < 0)
    {
        health = 0;
    }
}
