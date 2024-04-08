#ifndef HEALTH_H
#define HEALTH_H

class Health
{
public:
    Health();

    int getHealth() const;
    int getMaxHealth();
    void setHealth(int);
    void setMaxHealth(int);
    void decrementHealth();
    void incrementHealth();

private:
    int health;
    int maxHealth;
};

#endif // HEALTH_H
