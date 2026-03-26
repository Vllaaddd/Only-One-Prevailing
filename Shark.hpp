#ifndef SHARK_HPP
#define SHARK_HPP

#include "Entity.hpp"
#include <vector>

class Shark: public Entity{
    private:
        std::size_t territory_width_;

    public:
        Shark();
        Shark(const Shark& ) = delete;
        ~Shark() = default;

        bool move(CompassDirection movement_direction) override;
        bool isActive();
        void play(Player &current_player, std::vector<Player *> &players, std::vector<CompassDirection> &shark_path);
};

#endif