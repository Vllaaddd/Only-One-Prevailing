#ifndef ACTIONCARD_HPP
#define ACTIONCARD_HPP

#include "Card.hpp"
#include <vector>
#include <iostream>
#include <map>

enum class ActionCardType{
    MESSAGE_IN_A_BOTTLE,
    PIRATE,
    ROGUE_WAVE,
    LOST_AT_SEA,
};

enum class CompassDirection{
    NORTH,
    EAST,
    SOUTH,
    WEST,
};

class ActionCard: public Card{
    private:
        CompassDirection shark_direction_;
        Player * target_player_;
    
    public:
        ActionCard(std::string &id, CompassDirection shark_direction);
        ActionCard(const ActionCard&) = delete;
        ~ActionCard() = default;

        void printInformationString(std::vector<Card *> deck) override;
        void printPlayMessage() override;
        virtual void play() override;
};

#endif