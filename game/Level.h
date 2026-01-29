#pragma once
#include <string>
#include <vector>
#include "Enemy.h"
#include "Item.h"

class Level {
private:
    Level(const Level& other);
    Level& operator=(const Level& other);

public:
    Level();
    virtual ~Level();

    static const int GRID_SIZE = 6;
    Entity* grid[GRID_SIZE][GRID_SIZE];

    void initializeGrid();
    Entity* getEntityAtGrid(int x, int y) const;
    Entity* getEntityAtUser(int x, int y) const;

    void collapseGrid();
    bool hasValidMove();
};