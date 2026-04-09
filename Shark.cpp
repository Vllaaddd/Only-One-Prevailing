#include "Shark.hpp"
#include "Player.hpp"

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
    int shark_eat_times = 0;

    for(CompassDirection direction : shark_path){
        move(direction);

        for(auto* player : players){
            if(!player->hasStarved()){
                Coordinates player_coords = player->getCoordinates().value();
                Coordinates shark_coords = this->getCoordinates().value();

                if(player_coords.getX() == shark_coords.getX() && player_coords.getY() == shark_coords.getY()) {
                    player->setRations(player->getRations() - 1);
                    shark_eat_times++;
                }
            }
        }
    }

    std::cout << "[" << UNICODE_SHARK << "] " << "The shark will move along the path [";

    for(CompassDirection direction : shark_path){
        if(direction == CompassDirection::NORTH){
            std::cout << " N";
        }else if(direction == CompassDirection::SOUTH){
            std::cout << " S";
        }else if(direction == CompassDirection::WEST){
            std::cout << " W";
        }else if(direction == CompassDirection::EAST){
            std::cout << " E";
        }
    }

    std::cout << " ] swiftly!" << std::endl;

    for(int i = 0; i < shark_eat_times; i++){
        std::cout << "[" << UNICODE_SHARK << "]" << " Yum, the shark was given a ration to eat!" << std::endl;
    }
}

void Shark::setTerritoryWidth(std::size_t width){
    territory_width_ = width;
}