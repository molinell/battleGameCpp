#include "npc.hpp"
#include <random>

const std::unordered_map<NPC::Characters, NPC::Properties> NPC::properties_ = {
    {Characters::ORK, {"Ork", 90, 0.6, Weapon::Types::FIST, 20}},
    {Characters::WITCH, {"Witch", 100, 0.8, Weapon::Types::POTION, 40}},
    {Characters::GHOUL, {"Ghoul", 70, 0.8, Weapon::Types::SWORD, 15}},
    {Characters::GOBLIN, {"Goblin", 50, 0.5, Weapon::Types::MACE, 8}},
    {Characters::MONSTER, {"Monster", 80, 0.7, Weapon::Types::CROSSBOW, 25}},
    {Characters::SWAMP_MONSTER, {"Swamp monster", 60, 0.5, Weapon::Types::SPEAR, 15}}
};

void NPC::heal(int){
    setHitPoints(getHitPoints()*1.05);
}

int NPC::getValue() const {
    return value_;
}

NPC* NPC::spawnNPC(){
    std::random_device rd;
    std::uniform_int_distribution<int> range(0, static_cast<int>(NPC::Characters::MAX_Characters_VALUE));

    NPC::Characters type = static_cast<NPC::Characters> (range(rd));
    return new NPC(type);
}
