#include "player.hpp"
#include <stdexcept>
#include <memory>
#include <random>
#include <format>

void Player::heal(int amount){
    if(amount > coins_) throw std::invalid_argument("Cannot afford");

    this->setCoins(-amount);

    if(this->getHitPoints() + amount > 100){
        int temp = this->getHitPoints() + amount;
        for(; temp > 100; temp -= 100) lives_++;
        this->setHitPoints(-100);
        this->setHitPoints(temp);
        return;
    }

    this->setHitPoints(amount);
}

void Player::takeDamage(int amount){

    if(amount + this->getHitPoints() < 0){
        lives_--;
    }
    
    this->setHitPoints(amount);
}

int Player::attack(GameCharacter* defender){
    std::random_device rd;

    int lowerbound = (int) this->getEquippedWeapon()->getDamage()*this->getDexterity();
    std::uniform_int_distribution<int> range (lowerbound, this->getEquippedWeapon()->getDamage());
    int damage = range(rd);

    defender->takeDamage(-damage);

    if(this->getEquippedWeapon()->wearDown() <= 0){
        loseWeapon();
        this->setEquippedWeapon(new Weapon(Weapon::Types::FIST));
    }

    return damage;
}

int Player::loseWeapon(){
    if(inventory_.size() < 2 && inventory_.at(0)->getType() == Weapon::Types::FIST) return 0;

    const Weapon* target = this->getEquippedWeapon();
    auto it = std::find_if(inventory_.begin(), inventory_.end(), [target](const Weapon* w){return w == target;});
   
    if(it != inventory_.end()) {
        inventory_.erase(it);
        delete *it;
    }

    if(inventory_.size() == 0){
        Weapon* fist = new Weapon(Weapon::Types::FIST);
        addToInventory(fist);
        this->setEquippedWeapon(fist);
        return 0;
    }
    return 1;
}

std::ostream& operator<<(std::ostream& os, Player* player){
    os << std::format(" *** Current stats ***\nLives: {}     HP on this life: {}\nCoins: {}    Weapons: {}", 
                player->getLives(), player->getHitPoints(), player->getCoins(), player->getInventory().size()) 
                << std::endl;

    return os;
}

int Player::setCoins(int amount){
    coins_ += amount;

    return amount;
}

int Player::getCoins() const {
    return coins_;
}

int Player::getLives() const {
    return lives_;
}

const std::vector<Weapon*>& Player::getInventory() const {
    return inventory_;
}

void Player::addToInventory(Weapon* weapon){
    inventory_.push_back(weapon);
}
