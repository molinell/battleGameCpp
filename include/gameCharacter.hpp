#ifndef GAME_CHARACTER
#define GAME_CHARACTER

#include <string>
#include <iostream>
#include <memory>
#include <vector>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>

#include "weapon.hpp"

/**
 * Abstract class for game characters
 */

class GameCharacter
{
private:
    std::string name_;
    int hitPoints_;
    double dexterity_;
    Weapon* equippedWeapon_;

    friend class boost::serialization::access;
    /**
     * @brief Serialises a GameCharacter object
     * 
     * @tparam Archive 
     * @param ar the archive to write to
     * @param version 
     */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version){
        ar & name_;
        ar & hitPoints_;
        ar & dexterity_;
    }

public:
    GameCharacter() = default;

    /**
     * @brief Construct a new Game Character object
     * 
     * @param name the name of the character
     * @param hitPoints the hitpoints of the character
     * @param weapon the initial weapon of the character
     * @param dexterity the minimum dexterity of the charcter, default 0.8
     *                  (1 if character should always attack perfectly)
     */
    GameCharacter(std::string name, int hitPoints, Weapon* weapon, double dexterity = 0.8):
        name_(name), hitPoints_(hitPoints), equippedWeapon_(weapon), dexterity_(dexterity){}

    /**
     * @brief Copy constructor for GameCHaracter
     * 
     * @param other the GameCharacter to copy
     */
    GameCharacter(const GameCharacter& other): 
        name_(other.name_), hitPoints_(other.hitPoints_), equippedWeapon_(other.equippedWeapon_), dexterity_(other.dexterity_) {}
    
    virtual ~GameCharacter() {}

    int getHitPoints() const;
    void setHitPoints(int hp);

    /**
     * @brief Manages how the hitpoints are affected when attacked
     * 
     * @param amount how much damage was caused
     */
    virtual void takeDamage(int amount);
    const std::string& getName() const;

    /**
     * @brief Heals the GameCharacter
     * 
     */
    virtual void heal(int) = 0;
    void setEquippedWeapon(Weapon* weapon);
    Weapon* getEquippedWeapon();
    double getDexterity() const;

    /**
     * @brief Attacks (causes damage to) the opponent
     * 
     * Randomises the damage caused based on the GameCharacters dexterity and the weapons max damage
     * 
     * @param defender the GameCharacter to attack
     * @return int how much damage was caused
     */
    virtual int attack(GameCharacter* defender);
};


#endif
