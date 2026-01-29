#pragma once
#include "Entity.h"

class Hero : public Entity {
private:
    int health;
    int attack;
    int armor;
    int score;

    Hero(const Hero& other);
    Hero& operator=(const Hero& other);

public:
    Hero();
    virtual ~Hero();

    void takeDamage(int dmg);
    void addArmor(int amount);
    void heal(int hp);     
    void addScore(int value);

    int getHealth() const;
    int getAttack() const;
    int getArmor() const;
    int getScore() const;

    virtual std::string getSound() const override;
};