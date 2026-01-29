#pragma once
#include <string>

class Entity {
private:
    Entity(const Entity& other);
    Entity& operator=(const Entity& other);

protected:
    int posX;
    int posY;

public:
    Entity();
    virtual ~Entity();

    void setPos(int x, int y);
    int getPosX() const;
    int getPosY() const;

    // Renamed from 'odglos' to 'getSound'
    virtual std::string getSound() const = 0;
};