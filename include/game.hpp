#ifndef GAME
#define GAME

#include "player.hpp"
#include "npc.hpp"

class Game
{
private:
    Player* player_ = nullptr;
    NPC* currentNPC_ = nullptr;

    /**
     * @brief the path which to save the serialised Player object
     */
    const std::string savePath_;

public:
    /**
     * @brief Construct a new Game object
     * 
     * Initialises the player
     */
    Game();
    ~Game(){
        delete player_;
        delete currentNPC_;
    }

    /**
     * @brief Runs the game logic
     * 
     * Prompts the player to choose a weapon for the round. 
     * Duel continues until one is dead.
     * 
     * If palyer wins, it earns some coins and can pick up the NPC's weapon to its inventory.
     * If player loses, it loses its weapon and can choose to purchase more HP
     */
    void run();
};

#endif
