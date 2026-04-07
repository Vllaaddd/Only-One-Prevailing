#include "Shark.hpp"

Shark::Shark():
    Entity(EntityType::SHARK) {}

bool Shark::move(CompassDirection movement_direction){
    std::size_t y = coordinates_->getY();
    std::size_t x = coordinates_->getX();

    if(movement_direction == CompassDirection::NORTH){
        if(y < 5){
            y++;
        }
    }else if(movement_direction == CompassDirection::SOUTH){
        if(y > 1){
            y--;
        }
    }else if(movement_direction == CompassDirection::WEST){
        if(x > 1){
            x--;
        }
    }else if(movement_direction == CompassDirection::EAST){
        if(x < territory_width_){
            x++;
        }
    }
    
    coordinates_.emplace(x, y);
    return true;
}

bool Shark::isActive(){
    if(getCoordinates() == std::nullopt){
        return false;
    }
    return true;
}

void Shark::play(Player &current_player, std::vector<Player *> &players, std::vector<CompassDirection> &shark_path){

}

void Shark::setTerritoryWidth(std::size_t width){
    territory_width_ = width;
}