#include "HandActionCard.hpp"

HandActionCard::HandActionCard(std::string &id, CompassDirection shark_direction):
    ActionCard(id, shark_direction), target_hand_index_(std::nullopt) {}

void HandActionCard::play(){
    
}