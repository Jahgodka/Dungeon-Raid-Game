#include "Engine.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <vector>

Engine::Engine() {
    srand(static_cast<unsigned>(time(0)));
    hero = new Hero();
    currentLevel = new Level();

    do {
        currentLevel->initializeGrid();
    } while (!currentLevel->hasValidMove());
}

Engine::~Engine() {
    delete hero;
    delete currentLevel;
}

void Engine::start() {
    const int maxTurns = 10;
    int turn = 0;

    std::cout << "Welcome to Dungeon Raid Console Edition!\n";
    std::cout << "Match 3 items to survive. Format: Col,Row (e.g., 2,3 2,4 2,5)\n";

    while (turn < maxTurns && hero->getHealth() > 0) {
        std::cout << "\n--- Turn " << (turn + 1) << " / " << maxTurns << " ---\n";
        printGrid();
        std::cout << "Hero HP: " << hero->getHealth() 
                  << " | Armor: " << hero->getArmor() 
                  << " | Score: " << hero->getScore() << "\n";

        if (updateGame()) {
            turn++;
        }
        else {
            std::cout << "Invalid move. Try again.\n";
        }
    }

    if (hero->getHealth() <= 0) {
        std::cout << "\nYOU DIED.\n";
    }
    else {
        std::cout << "\nVICTORY! You survived the dungeon.\n";
    }
    std::cout << "Final Score: " << hero->getScore() << "\n";
}

bool Engine::handleSelection() {
    std::cout << "Enter sequence (x,y x,y x,y): ";
    std::string line;
    std::getline(std::cin, line);

    if (line.empty()) {
        return false;
    }

    std::stringstream ss(line);
    std::string token;
    std::vector<std::pair<int, int>> positions;
    int swordBonus = 0;
    std::vector<std::pair<int, int>> enemyPositions;

    while (ss >> token) {
        int x, y;
        char comma;
        // Using standard stream parsing for portability
        std::stringstream ts(token);
        if (ts >> x >> comma >> y) {
             positions.emplace_back(x, y);
        }
    }

    if (positions.size() < 3) {
        std::cout << "You must select at least 3 matching items.\n";
        return false;
    }

    Entity* first = currentLevel->getEntityAtUser(positions[0].first, positions[0].second);
    if (!first) {
        std::cout << "Empty starting position.\n";
        return false;
    }

    bool isCombat = false;
    ItemType matchType;

    for (auto& pos : positions) {
        Entity* ent = currentLevel->getEntityAtUser(pos.first, pos.second);
        if (!ent) continue;
        if (dynamic_cast<Enemy*>(ent)) {
            isCombat = true;
            break;
        }
    }

    if (!isCombat) {
        auto itemFirst = dynamic_cast<Item*>(first);
        if (!itemFirst) {
            std::cout << "Invalid selection.\n";
            return false;
        }
        matchType = itemFirst->getType();
    }

    for (auto& pos : positions) {
        Entity* ent = currentLevel->getEntityAtUser(pos.first, pos.second);
        if (!ent) {
            std::cout << "Invalid position (" << pos.first << "," << pos.second << ")\n";
            return false;
        }

        if (isCombat) {
            if (auto enemy = dynamic_cast<Enemy*>(ent)) {
                enemyPositions.push_back(pos);
            }
            else if (!(dynamic_cast<Item*>(ent) && dynamic_cast<Item*>(ent)->getType() == ItemType::Sword)) {
                std::cout << "Only Enemies and Swords can be linked in combat.\n";
                return false;
            }
        }
        else {
            auto item = dynamic_cast<Item*>(ent);
            if (!item || item->getType() != matchType) {
                std::cout << "Items must be of the same type.\n";
                return false;
            }
        }
    }

    // Play sound of the first item
    if (!positions.empty()) {
        Entity* ent = currentLevel->getEntityAtUser(positions[0].first, positions[0].second);
        if (ent) {
            std::cout << "> " << ent->getSound() << "\n";
        }
    }

    for (auto& pos : positions) {
        Entity* ent = currentLevel->getEntityAtUser(pos.first, pos.second);
        if (!ent) continue;

        if (auto item = dynamic_cast<Item*>(ent)) {
            ItemType type = item->getType();
            switch (type) {
            case ItemType::Sword:
                hero->addScore(1);
                swordBonus += 5;
                // std::cout << "Sword used (+1 score)\n";
                break;
            case ItemType::Coin:
                hero->addScore(5);
                // std::cout << "Coin collected (+5 score)\n";
                break;
            case ItemType::Potion:
                hero->heal(10);
                hero->addScore(1);
                // std::cout << "Healed 10 HP (+1 score)\n";
                break;
            case ItemType::Armor:
                hero->addArmor(3);
                hero->addScore(1);
                // std::cout << "Armor +3 (+1 score)\n";
                break;
            }
            currentLevel->grid[pos.second - 1][pos.first - 1] = nullptr;
        }
    }

    for (auto& pos : enemyPositions) {
        int x = pos.first - 1;
        int y = pos.second - 1;
        Entity* ent = currentLevel->grid[y][x];

        if (Enemy* enemy = dynamic_cast<Enemy*>(ent)) {
            int dmg = hero->getAttack() + swordBonus - enemy->getDefense();
            if (dmg < 1) dmg = 1;
            enemy->takeDamage(dmg);

            std::cout << " Enemy at (" << pos.first << "," << pos.second << ") took " << dmg << " dmg.\n";

            if (enemy->getHealth() <= 0) {
                std::cout << " Enemy slain! (+2 score)\n";
                hero->addScore(2);
                currentLevel->grid[y][x] = nullptr;
            }
        }
    }

    processEnemyAttacks();

    currentLevel->collapseGrid();

    if (!currentLevel->hasValidMove()) {
        std::cout << "No moves possible. Reshuffling...\n";
        do {
            currentLevel->initializeGrid();
        } while (!currentLevel->hasValidMove());
    }

    return true;
}

bool Engine::updateGame() {
    return handleSelection();
}

void Engine::printGrid() {
    std::cout << "\nMap:\n   ";
    for (int x = 1; x <= Level::GRID_SIZE; ++x)
        std::cout << x << " ";
    std::cout << "\n";

    for (int y = 0; y < Level::GRID_SIZE; ++y) {
        std::cout << std::setw(2) << (y + 1) << " ";
        for (int x = 0; x < Level::GRID_SIZE; ++x) {
            Entity* e = currentLevel->getEntityAtGrid(x, y);
            if (!e) std::cout << ". ";
            else if (dynamic_cast<Enemy*>(e)) std::cout << "E ";
            else {
                Item* item = dynamic_cast<Item*>(e);
                switch (item->getType()) {
                case ItemType::Coin: std::cout << "C "; break;
                case ItemType::Potion: std::cout << "P "; break;
                case ItemType::Sword: std::cout << "S "; break;
                case ItemType::Armor: std::cout << "A "; break;
                }
            }
        }
        std::cout << "\n";
    }
}

void Engine::processEnemyAttacks() {
    int totalDamage = 0;

    for (int y = 0; y < Level::GRID_SIZE; ++y) {
        for (int x = 0; x < Level::GRID_SIZE; ++x) {
            Entity* ent = currentLevel->getEntityAtGrid(x, y);
            if (Enemy* enemy = dynamic_cast<Enemy*>(ent)) {
                int dmg = enemy->getAttack() - hero->getArmor();
                if (dmg < 1) dmg = 1;
                totalDamage += dmg;
            }
        }
    }

    hero->takeDamage(totalDamage);
    if (totalDamage > 0)
        std::cout << "Enemies dealt " << totalDamage << " damage this turn.\n";
}