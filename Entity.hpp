#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <optional>
#include "Coordinates.hpp"
#include "ActionCard.hpp"

enum class EntityType{
    PLAYER,
    SHARK,
};

class Entity{
    protected:
        EntityType type_;
        std::optional<Coordinates> coordinates_;

    public:
        Entity(EntityType type);
        Entity(EntityType type, std::size_t x, std::size_t y);
        Entity(const Entity& ) = delete;
        ~Entity() = default;

        std::optional<Coordinates> getCoordinates() const;
        void setCoordinates(std::size_t x, std::size_t y);

        virtual bool move(CompassDirection movement_direction) = 0;
};

#endif