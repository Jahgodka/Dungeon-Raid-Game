#include "Enemy.h"

Enemy::Enemy() : Entity(), health(15), attack(5), defense(2) {}

Enemy::~Enemy() {}

void Enemy::takeDamage(int dmg) {
    health -= dmg;
    if (health < 0) {
        health = 0;
    }
}

std::string Enemy::getSound() const {
    return "Roar!";
}

int Enemy::getHealth() const { return health; }
int Enemy::getAttack() const { return attack; }
int Enemy::getDefense() const { return defense; }