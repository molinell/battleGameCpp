#ifndef NPC_HPP
#define NPC_HPP

#include "gameCharacter.hpp"

/**
 * Derived class for non playable game character
 */
class NPC : public GameCharacter
{
public:

    /**
     * @brief Enum for default character types
     */
    enum Characters {
        ORK = 0,
        WITCH,
        GHOUL,
        GOBLIN,
        MONSTER,
        SWAMP_MONSTER,
        MAX_Characters_VALUE = SWAMP_MONSTER
    };

    /**
     * @brief Construct a new NPC object
     * 
     * @param character the type of the character
     */
    NPC(Characters character) : 
        GameCharacter(properties_.at(character).name, properties_.at(character).hp, (new Weapon(properties_.at(character).weapon)), properties_.at(character).dexterity),
        value_(properties_.at(character).value) {}
    ~NPC() {
        delete this->getEquippedWeapon();
    }
    /**
     * @brief Heals the NPC by 0.05 of its HP
     */
    void heal(int) override;

    /**
     * @brief Spawns a random NPC
     * Chooses type randomly
     * 
     * @return NPC* the character
     */
    static NPC* spawnNPC();
    int getValue() const;

private:
    int value_;

    /**
     * @brief Struct for the properties of a specific NPC type
     * 
     * @param name the string name of the NPC type
     * @param hp the initial hitpoints
     * @param dexterity the minimum dexterity
     * @param weapon the weapon type assigned
     * @param value the monetary value
     */
    struct Properties{
        std::string name;
        int hp;
        double dexterity;
        Weapon::Types weapon;
        int value;
    };

    /**
     * @brief Map of default NPC characters
     */
    static const std::unordered_map<Characters, Properties> properties_;
};

#endif
