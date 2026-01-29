#include "Entity.h"

Entity::Entity() : posX(0), posY(0) {}

Entity::~Entity() {}

void Entity::setPos(int x, int y) {
    posX = x;
    posY = y;
}

int Entity::getPosX() const {
    return posX;
}

int Entity::getPosY() const {
    return posY;
}