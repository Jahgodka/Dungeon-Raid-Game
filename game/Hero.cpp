#include "Hero.h"

Hero::Hero() : Entity(), health(100), attack(10), armor(10), score(0) {}

Hero::~Hero() {}

void Hero::takeDamage(int dmg) {
    if (armor >= dmg) {
        armor -= dmg;
    }
    else {
        dmg -= armor;
        armor = 0;
        health -= dmg;
        if (health < 0) health = 0;
    }
}

void Hero::addArmor(int amount) {
    armor += amount;
    if (armor > 10) armor = 10;
}

void Hero::heal(int hp) {
    health += hp;
    if (health > 100) health = 100;
}

void Hero::addScore(int value) {
    score += value;
}

int Hero::getHealth() const { return health; }
int Hero::getAttack() const { return attack; }
int Hero::getArmor() const { return armor; }
int Hero::getScore() const { return score; }

std::string Hero::getSound() const {
    return "Hero ready!";
}