#include "Level.h"
#include <iostream>
#include <cstdlib>

Level::Level() {
    for (int y = 0; y < Level::GRID_SIZE; ++y)
        for (int x = 0; x < Level::GRID_SIZE; ++x)
            grid[y][x] = nullptr;
}

Level::~Level() {}

Entity* Level::getEntityAtGrid(int x, int y) const {
    if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) {
        return grid[y][x];
    }
    return nullptr;
}

Entity* Level::getEntityAtUser(int x, int y) const {
    // User input is 1-based, array is 0-based
    return getEntityAtGrid(x - 1, y - 1);
}

void Level::initializeGrid() {
    for (int y = 0; y < GRID_SIZE; ++y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            Entity* e = nullptr;
            int randVal = rand() % 5;
            switch (randVal) {
            case 0: e = new Enemy(); break;
            case 1: {
                Item* item = new Item();
                item->setType(ItemType::Coin);
                e = item; break;
            }
            case 2: {
                Item* item = new Item();
                item->setType(ItemType::Potion);
                e = item; break;
            }
            case 3: {
                Item* item = new Item();
                item->setType(ItemType::Sword);
                e = item; break;
            }
            case 4: {
                Item* item = new Item();
                item->setType(ItemType::Armor);
                e = item; break;
            }
            }
            if (e) {
                e->setPos(x, y);
            }
            grid[y][x] = e;
        }
    }
    // std::cout << "Grid initialized\n"; // Debug info removed for cleaner UI
}

void Level::collapseGrid() {
    for (int x = 0; x < GRID_SIZE; ++x) {
        int writeY = GRID_SIZE - 1;
        for (int y = GRID_SIZE - 1; y >= 0; --y) {
            if (grid[y][x]) {
                if (y != writeY) {
                    grid[writeY][x] = grid[y][x];
                    grid[writeY][x]->setPos(x, writeY);
                    grid[y][x] = nullptr;
                }
                writeY--;
            }
        }

        for (int y = writeY; y >= 0; --y) {
            Entity* e = nullptr;
            int randVal = rand() % 5;
            switch (randVal) {
            case 0: e = new Enemy(); break;
            case 1: {
                Item* item = new Item();
                item->setType(ItemType::Coin);
                e = item; break;
            }
            case 2: {
                Item* item = new Item();
                item->setType(ItemType::Potion);
                e = item; break;
            }
            case 3: {
                Item* item = new Item();
                item->setType(ItemType::Sword);
                e = item; break;
            }
            case 4: {
                Item* item = new Item();
                item->setType(ItemType::Armor);
                e = item; break;
            }
            }
            if (e) {
                e->setPos(x, y);
                grid[y][x] = e;
            }
        }
    }
}

bool Level::hasValidMove() {
    for (int y = 0; y < GRID_SIZE; ++y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            Entity* current = grid[y][x];
            if (!current) continue;

            const int dirs[8][2] = {
                {1, 0}, {-1, 0}, {0, 1}, {0, -1},
                {1, 1}, {-1, -1}, {1, -1}, {-1, 1}
            };

            for (int d = 0; d < 8; ++d) {
                int nx1 = x + dirs[d][0];
                int ny1 = y + dirs[d][1];
                int nx2 = x + 2 * dirs[d][0];
                int ny2 = y + 2 * dirs[d][1];

                if (nx1 >= 0 && ny1 >= 0 && nx1 < GRID_SIZE && ny1 < GRID_SIZE &&
                    nx2 >= 0 && ny2 >= 0 && nx2 < GRID_SIZE && ny2 < GRID_SIZE) {

                    Entity* e1 = grid[ny1][nx1];
                    Entity* e2 = grid[ny2][nx2];

                    if (e1 && e2 &&
                        typeid(*e1) == typeid(*current) &&
                        typeid(*e2) == typeid(*current)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}