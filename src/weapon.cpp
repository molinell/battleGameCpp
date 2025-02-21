#include "weapon.hpp"

const std::unordered_map<Weapon::Types, Weapon::Properties> Weapon::properties_ = {
    {Types::SWORD, {"sword", 30, 2.0, 60}},
    {Types::AXE, {"axe", 15, 1.5, 30}},
    {Types::CROSSBOW, {"crossbow", 25, 5.0, 40}},
    {Types::FIREARM, {"firearm", 40, 1.0, 80}},
    {Types::MACE, {"mace", 20, 7.0, 25}},
    {Types::FIST, {"fist", 5, 0.0, 0}},
    {Types::SPEAR, {"spear", 10, 10.0, 10}},
    {Types::POTION, {"magic potion", 50, (1/3), 70}}
};

int Weapon::getDamage() const {
    return damage_;
}

double Weapon::getHealth() const {
    return health_;
}

double Weapon::wearDown(){
    return (health_ -= wear_);
}

const std::string& Weapon::getName() const {
    return name_;
}

Weapon::Types Weapon::getType() const {
    return type_;
}
