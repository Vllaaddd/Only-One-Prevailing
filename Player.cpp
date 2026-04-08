#include "Player.hpp"

Player::Player(std::size_t id):
    Entity(EntityType::PLAYER, id, 1), id_(id), hand_cards_(), rations_(12) {}

Player::~Player() {
    for(ActionCard *card : hand_cards_){
        delete card;
    } 
};

bool Player::move(CompassDirection movement_direction){

    std::size_t y = coordinates_->getY();
    std::size_t x = coordinates_->getX();

    if(movement_direction == CompassDirection::NORTH){
        y++;
    }else if(movement_direction == CompassDirection::SOUTH){
        y--;
    }
    
    coordinates_.emplace(x, y);
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

std::size_t Player::setRations(std::size_t rations){
    rations_ = rations;
    return rations_;
}