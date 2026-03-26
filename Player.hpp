#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include <cstddef>
#include <vector>
#include "ActionCard.hpp"

class Player: public Entity{
    private:
        std::size_t id_;
        std::vector<ActionCard *> hand_cards_;
        std::size_t rations_;

    public:
        Player(std::size_t id);
        Player(const Player&) = delete;
        ~Player();

        bool move(CompassDirection movement_direction) override;
        bool hasStarved();
        std::vector<ActionCard *> &getHandCards();

        std::size_t getId() const;
        std::size_t getRations() const {
            return rations_;
        }
};

#endif
