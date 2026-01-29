#pragma once
#include "Entity.h"
#include <string>

class Enemy : public Entity {
private:
    int health;
    int attack;
    int defense;

    Enemy(const Enemy& other);
    Enemy& operator=(const Enemy& other);

public:
    Enemy();
    virtual ~Enemy();

    void takeDamage(int dmg);

    int getHealth() const;
    int getAttack() const;
    int getDefense() const;

    virtual std::string getSound() const override;
};