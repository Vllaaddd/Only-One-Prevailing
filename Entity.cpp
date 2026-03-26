#include "Entity.hpp"

Entity::Entity(EntityType type):
    type_(type), coordinates_(std::nullopt) {}

Entity::Entity(EntityType type, std::size_t x, std::size_t y): 
    type_(type), coordinates_(Coordinates(x, y)) {}

bool Entity::move(CompassDirection movement_direction){
    return true;
}

std::optional<Coordinates> Entity::getCoordinates() const{
    return coordinates_;
}