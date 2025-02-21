#ifndef PLAYER
#define PLAYER

#include "gameCharacter.hpp"
#include <vector>
#include <iostream>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>

/**
 * Derived class for the (human) player
 */
class Player : public GameCharacter
{
private:
    int coins_;
    std::vector<Weapon*> inventory_;
    int lives_;

    friend class boost::serialization::access;
    /**
     * @brief Serialises a Player object
     * 
     * @tparam Archive 
     * @param ar the archive to write to
     * @param version 
     */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version){
        ar & boost::serialization::base_object<GameCharacter>(*this);

        ar & coins_;
        ar & lives_;
        ar & inventory_;
    }

public:
    Player() = default;

    /**
     * @brief Construct a new Player object
     * 
     * @param name the name of the player
     * @param coins the initial amount of coins, default 50
     * @param lives the initial amount of lives, default 3
     * 
     * Player has initial weapon of type Spear and 100 HP per life
     */
    Player(std::string name, int coins = 50, int lives = 3) : GameCharacter(name, 100, new Weapon(Weapon::Types::SPEAR)), coins_(coins), lives_(lives){
            inventory_.push_back(this->getEquippedWeapon());
    }

    /**
     * @brief Copy constructor for player
     * 
     * @param other the Player to copy
     */
    Player(const Player& other) : 
            GameCharacter(other), coins_(other.coins_), lives_(other.lives_), inventory_(other.inventory_){}

    ~Player() {
        for (auto i : inventory_) delete i;
    }

    /**
     * @brief Heals the player
     * 
     * If combined HP (current + \p amount ) is over 100, a life is added for every 100 HP
     * 
     * @param amount how many HP to add
     */
    void heal(int amount) override;

    /**
     * @brief Cause damage to Player
     * 
     * If \p amount is more than the players current HP, a life is lost
     * 
     * @param amount how much damage to cause
     */
    void takeDamage(int amount) override;

    /**
     * @brief Attacks the opponent
     * 
     * Wears down the Players weapon, 
     * and if Weapon is worn down, loses it and gets replaced with a fist
     * 
     * @param defender the GameCharacter to attac
     * @return int the damage
     */
    int attack(GameCharacter* defender) override;

    int getCoins() const;
    int setCoins(int amount);
    int getLives() const;

    /**
     * @brief Causes player to lose a weapon
     * 
     * If player has no other weapon than their fist nothing happens.
     * Otherwise the equipped weapon is removed from inventory.
     * If player is left with no weapon, a fist is added
     * 
     * @return int 0 if player only has fist, 1 otherwise
     */
    int loseWeapon();

    const std::vector<Weapon*>& getInventory() const;
    void addToInventory(Weapon* weapon);

    /**
     * @brief Prints the players stats in a formatted way
     * 
     * @param os the stream which to output
     * @param player the player object to print
     * @return std::ostream& 
     */
    friend std::ostream& operator<<(std::ostream& os, Player* player);

};

#endif
