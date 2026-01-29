#pragma once
#include "Entity.h"
#include <string>

enum class ItemType {
    Coin,
    Sword,
    Armor,
    Potion
};

class Item : public Entity {
private:
    ItemType type;

    Item(const Item& other);
    Item& operator=(const Item& other);

public:
    Item();
    virtual ~Item();

    void setType(ItemType t);
    ItemType getType() const;

    virtual std::string getSound() const override;
};