#include "gameCharacter.hpp"
#include <random>

int GameCharacter::getHitPoints() const {
    return hitPoints_;
}

void GameCharacter::setHitPoints(int amount){
    if(amount + hitPoints_ < 0){
        hitPoints_ = 0;
        return;
    }
    hitPoints_ += amount;
}

void GameCharacter::takeDamage(int amount){
    setHitPoints(amount);
}

const std::string& GameCharacter::getName() const {
    return name_;
}

void GameCharacter::setEquippedWeapon(Weapon* weapon){
    equippedWeapon_ = weapon;
}

Weapon* GameCharacter::getEquippedWeapon(){
    return equippedWeapon_;
}

double GameCharacter::getDexterity() const {
    return dexterity_;
}

int GameCharacter::attack(GameCharacter* defender){
    std::random_device rd;

    int lowerbound = (int) this->equippedWeapon_->getDamage()*dexterity_;
    std::uniform_int_distribution<int> range (lowerbound, this->equippedWeapon_->getDamage());
    int damage = range(rd);

    defender->takeDamage(-damage);

    return damage;
}
