#include "PlayerActionCard.hpp"
#include "Player.hpp"

PlayerActionCard::PlayerActionCard(std::string &id, CompassDirection shark_direction):
    ActionCard(id, shark_direction) {}

void PlayerActionCard::play(){
    Utils::toLowerCase(id_);
    if(id_ == "mssge"){
        if(target_player_->getRations() >= 2){
            target_player_->setRations(target_player_->getRations() - 2);
            owner_->setRations(owner_->getRations() + 2);
        }else if(target_player_->getRations() == 1){
            target_player_->setRations(target_player_->getRations() - 1);
            owner_->setRations(owner_->getRations() + 1);
        }
    }if(id_ == "rwave"){
        std::optional<Coordinates> target_player_coordinates = target_player_->getCoordinates();
        if(target_player_coordinates->getY() > 1){
            target_player_->move(CompassDirection::SOUTH);
        }
    }
}