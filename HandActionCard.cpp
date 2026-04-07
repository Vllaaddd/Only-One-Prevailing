#include "HandActionCard.hpp"

HandActionCard::HandActionCard(std::string &id, CompassDirection shark_direction):
    ActionCard(id, shark_direction), target_hand_index_(std::nullopt) {}

void HandActionCard::setTargetHandIndex(std::size_t index){
    target_hand_index_ = index;
}

void HandActionCard::play(){
    Utils::toLowerCase(id_);
    auto& target_player_hand_cards = target_player_->getHandCards();
    std::size_t index = target_hand_index_.value();
    ActionCard* taken_card = target_player_hand_cards[index];
    if(id_ == "pirat"){
        taken_card->setOwner(owner_);
        owner_->getHandCards().push_back(taken_card);
        target_player_hand_cards.erase(target_player_hand_cards.begin() + index);
    }else if(id_ == "losts"){
        target_player_hand_cards.erase(target_player_hand_cards.begin() + index);
    }
}