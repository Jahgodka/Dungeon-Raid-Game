#include "Item.h"

Item::Item() : Entity(), type(ItemType::Coin) {}

Item::~Item() {}

void Item::setType(ItemType t) {
    type = t;
}

ItemType Item::getType() const {
    return type;
}

std::string Item::getSound() const {
    switch (type) {
    case ItemType::Coin: return "*Cling* (Coin)";
    case ItemType::Sword: return "*Swish* (Sword)";
    case ItemType::Potion: return "*Gulp* (Potion)";
    case ItemType::Armor: return "*Clank* (Armor)";
    default: return "";
    }
}