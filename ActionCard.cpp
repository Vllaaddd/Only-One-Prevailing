#include "ActionCard.hpp"

ActionCard::ActionCard(std::string &id, CompassDirection shark_direction):
    Card(id), shark_direction_(shark_direction), target_player_(nullptr) {}

void ActionCard::printInformationString(Card* card){
    std::map<CompassDirection, std::string> directions = {
        {CompassDirection::NORTH, "NORTH"},
        {CompassDirection::EAST, "EAST"},
        {CompassDirection::SOUTH, "SOUTH"},
        {CompassDirection::WEST, "WEST"}
    };
    std::cout << "- " << card->getName() << " - " << directions[shark_direction_] << std::endl;
    
};

void ActionCard::printPlayMessage(){};

void ActionCard::play(){

};