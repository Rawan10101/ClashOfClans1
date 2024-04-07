#ifndef HEALTH_H
#define HEALTH_H

class Health
{
public:
    Health();

    int getHealth() const;
    void reduceHealth();

private:
    int health;
};

#endif // HEALTH_H
