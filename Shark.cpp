#include "Shark.hpp"

Shark::Shark():
    Entity(EntityType::SHARK) {}

bool Shark::move(CompassDirection movement_direction){
    return true;
}

bool Shark::isActive(){
    if(getCoordinates() == std::nullopt){
        return true;
    }
    return true;
}

void Shark::play(Player &current_player, std::vector<Player *> &players, std::vector<CompassDirection> &shark_path){

}