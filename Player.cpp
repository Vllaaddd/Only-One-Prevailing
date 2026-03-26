#include "Player.hpp"

Player::Player(std::size_t id):
    id_(id), rations_(12), hand_cards_(), Entity(EntityType::PLAYER, id, 1) {}

Player::~Player() {
    for(ActionCard *card : hand_cards_){
        delete card;
    } 
};

bool Player::move(CompassDirection movement_direction){
    return true;
}

bool Player::hasStarved(){
    if(rations_ <= 0){
        return true;
    }else{
        return false;
    }
}

std::vector<ActionCard *> &Player::getHandCards(){
    return hand_cards_;
}

std::size_t Player::getId() const {
    return id_;
}