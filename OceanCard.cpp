#include "OceanCard.hpp"
#include "HandActionCard.hpp"

OceanCard::OceanCard(std::string &id, bool shark_icon):
    Card(id), shark_icon_(shark_icon) {}

void OceanCard::printInformationString(){
    std::string shark_string;
    if(shark_icon_){
        shark_string = "SHARK";
    }else{
        shark_string = "NO SHARK";
    }
    std::cout << "- " << getName() << " - " << shark_string << std::endl;
}

void OceanCard::printPlayMessage(){
    std::string play_message;
    if(name_ == "Calm Waters"){
        play_message = "The sea is calm, nothing happened.";
    }else if(name_ == "Ocean Debris"){
        play_message = "Gained a new action card!";
    }else if(name_ == "Island Calling"){
        play_message = "Moved forward and back again due to the island's calling!";
    }else if(name_ == "Kraken"){
        play_message = "Lost a ration to the Kraken!";
    }

    std::cout << "[" << UNICODE_OCEAN << "] " << "Drew " << getName() << " - " << play_message << std::endl;
}

void OceanCard::play(){
    Utils::toLowerCase(id_);
    if(id_ == "dbris"){
        ActionCard* new_action_card;
        if(owner_->getRations() % 2 == 0){
            std::string card_id = "LOSTS";
            if(owner_->getHandCards().empty()){
                new_action_card = new HandActionCard(card_id, CompassDirection::NORTH);
            }else{
                CompassDirection shark_direction = owner_->getHandCards()[0]->getSharkDirection();
                new_action_card = new HandActionCard(card_id, shark_direction);
            }
        }else{
            std::string card_id = "PIRAT";
            if(owner_->getHandCards().empty()){
                new_action_card = new HandActionCard(card_id, CompassDirection::NORTH);
            }else{
                CompassDirection shark_direction = owner_->getHandCards()[0]->getSharkDirection();
                new_action_card = new HandActionCard(card_id, shark_direction);
            }
        }
        new_action_card->setOwner(owner_);
        owner_->getHandCards().push_back(new_action_card);
    }else if(id_ == "islnd"){
        if(owner_->getCoordinates()->getY() > 1){
            owner_->move(CompassDirection::SOUTH);
        }
    }else if(id_ == "krken"){
        if(owner_->getRations() > 0){
            owner_->setRations(owner_->getRations() - 1);
        }
    }
}

bool OceanCard::getSharkIcon() const{
    return shark_icon_;
}