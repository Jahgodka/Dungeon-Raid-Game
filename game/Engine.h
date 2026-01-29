#pragma once
#include "Level.h"
#include "Hero.h"

class Engine {
private:
    Level* currentLevel;
    Hero* hero;

    Engine(const Engine& other);
    Engine& operator=(const Engine& other);

public:
    Engine();
    virtual ~Engine();

    void start();
    bool updateGame();
    void printGrid();
    bool handleSelection();
    void processEnemyAttacks();

};
