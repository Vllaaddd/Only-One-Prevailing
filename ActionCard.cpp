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

void ActionCard::printPlayMessage(){
    std::string play_message;
    if(name_ == "Message in a Bottle"){
        play_message = "Stole up to 2 rations!";
    }else if(name_ == "Pirate"){
        play_message = "Stole another player's hand card!";
    }else if(name_ == "Rogue Wave"){
        play_message = "Moved back one space!";
    }else if(name_ == "Lost at Sea"){
        play_message = "Discarded another player's hand card!";
    }

    std::cout << "[" << UNICODE_ACTION_FIRE << "] " << "Played " << getName() << " - " << play_message << std::endl;
};

void ActionCard::setTargetPlayer(Player* player){
    target_player_ = player;
}

CompassDirection ActionCard::getSharkDirection() const{
    return shark_direction_;
}

void ActionCard::play(){};