#include "game.hpp"
#include "utils.hpp"
#include <regex>
#include <stdexcept>
#include <cctype>
#include <format>
#include <fstream>
#include <iostream>
#include <filesystem>

Game::Game() : savePath_("../assets/game.save"){
    Utils::setUp();
    currentNPC_ = NPC::spawnNPC();

    if(std::filesystem::exists(savePath_)){
        std::cout << "Do you want to continue with saved game? [Y/n]" << std::endl;
        std::string input;
        std::getline(std::cin, input);
        if(!std::regex_match(input, std::regex("^[Nn]{1}$"))){
            try
            {
                player_ = new Player(Utils::loadObject<Player>(savePath_));
                player_->setCoins(20);
                player_->heal(20);
                std::cout << "While you were away " << player_->getName() << " healed and earned 20 HP" << std::endl;
                return;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            
        }
    }

    std::cout << "Name your character: ";
    std::string name;
    std::cin >> name;
    player_ = new Player(name);
}

void Game::run(){

    GameCharacter* attacker = currentNPC_;
    GameCharacter* defender = player_;

    std::cout << Utils::colors.at(Utils::Colors::BLUE) << "\n*** Let the battle begin! ***\n" << Utils::colors.at(Utils::Colors::RESET) << std::endl;

    while (player_->getLives() > 0)
    {
        std::cout <<  Utils::colors.at(Utils::Colors::MAGENTA) << player_  <<  Utils::colors.at(Utils::Colors::RESET) << std::endl;

        std::cout << std::format("A scary looking {} is running towards you\n\n", currentNPC_->getName());

        std::cout << "Choose a weapon for this round: " << std::endl;

        for(auto i = player_->getInventory().begin(); i != player_->getInventory().end(); i++){
            std::cout << std::format("{}: {} - damage: {}, health: {}\n", i - player_->getInventory().begin() + 1, (*i)->getName(), (*i)->getDamage(), (*i)->getHealth());
        }

        std::cout << std::flush;

        while (true)
        {
            try
            {
                std::string input;
                std::cin >> input;
                std::cin.ignore(INT_MAX, '\n');
                
                if(!std::regex_match(input, std::regex("[1-9]*")) || std::stoi(input)-1 >= player_->getInventory().size() || std::stoi(input)-1 < 0) throw std::invalid_argument("Input a valid number");
                player_->setEquippedWeapon(player_->getInventory().at(std::stoi(input)-1));
                break;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            
        }

        std::cout << std::endl;

        while(currentNPC_->getHitPoints() > 0 && player_->getHitPoints() > 0){
            GameCharacter* tmp = attacker;
            attacker = defender;
            defender = tmp;

            if(attacker == player_){
                std::cout << "Do you want to attack? [Y/n] ";

               std::string input;
               std::getline(std::cin, input);
               if(std::regex_match(input, std::regex("^[Nn]{1}$"))){
                    std::cout << Utils::colors.at(Utils::Colors::CYAN) << "  > Coward" << Utils::colors.at(Utils::Colors::RESET) << std::endl;
                    continue;
               }

            }

            std::cout << Utils::colors.at(Utils::Colors::CYAN) << std::format("  > {} attacked {} with a {} for {} HP, {} {}\n",
                         attacker->getName(),
                         defender->getName(),
                         attacker->getEquippedWeapon()->getName(),
                         attacker->attack(defender),
                         defender->getName(),
                         (defender->getHitPoints() > 0) 
                         ? std::format("has {} HP left", defender->getHitPoints())
                         : "is dead") << Utils::colors.at(Utils::Colors::RESET);
        }

        if(player_->getHitPoints() > 0){
            std::cout << std::format("You won and earned {} coins!\n", player_->setCoins(currentNPC_->getValue()));

            std::cout << std::format("{} dropped a {}, do you want to pick it up? [Y/n]\n",
                         currentNPC_->getName(),
                         currentNPC_->getEquippedWeapon()->getName());

            std::string input;
            std::getline(std::cin, input);
            if(!std::regex_match(input, std::regex("^[Nn]{1}$"))){
                    player_->addToInventory(new Weapon(currentNPC_->getEquippedWeapon()));
            }

            std::cout << "Do you want to play again? [Y/n]";

            std::getline(std::cin, input);
            if(std::regex_match(input, std::regex("^[Nn]{1}$"))){
                break;
            }

            delete currentNPC_;
            currentNPC_ = NPC::spawnNPC();

            attacker = currentNPC_;
            defender = player_;
            continue;
        } //else {
            player_->setHitPoints(100);
                
            std::cout << "Oh no! You dropped your weapon" << ((player_->loseWeapon() == 1) ? "" : ", now your left to fighting with your fists");
        //}
        
        std::cout << std::endl;

        std::cout << "Do you want to purchase more HP? 1 coin - 1 HP [[amount] / n] ";
        std::string input;
        //std::cin >> input;
        while (true)
        {
            std::getline(std::cin, input);
            if(std::regex_match(input, std::regex("[0-9]+"))){
                try
                {
                    player_->heal(std::stoi(input));
                    break;
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
                
            }
            if(std::regex_match(input, std::regex("^[Nn]{1}$"))) break;
        }
    }

    std::cout << "*** Game over ***\nDo you want to save the game? [Y/n]";
    std::string input;
    std::getline(std::cin, input);
    if(!std::regex_match(input, std::regex("^[Nn]{1}$"))){
        try
        {
            Utils::saveObject(savePath_, player_);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
    
}
