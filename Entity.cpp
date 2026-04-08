#include "Entity.hpp"

Entity::Entity(EntityType type):
    type_(type), coordinates_(std::nullopt) {}

Entity::Entity(EntityType type, std::size_t x, std::size_t y): 
    type_(type), coordinates_(Coordinates(x, y)) {}

std::optional<Coordinates> Entity::getCoordinates() const{
    return coordinates_;
}

bool Entity::move(CompassDirection movement_direction){
    return true;
    (void)movement_direction;
}

// Code from Github Copilot, beginning:
void Entity::setCoordinates(std::size_t x, std::size_t y){
    coordinates_.emplace(x, y);
}
//end