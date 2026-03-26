#ifndef BOARD_HPP
#define BOARD_HPP

#include "OceanCard.hpp"
#include "Shark.hpp"
#include <cstddef>
#include <vector>
#include <array>
#include "Player.hpp"

class Board{
    private:
        std::size_t column_count_;
        std::vector<std::array<OceanCard *, 5>> card_slots_;
        bool active_ = true;
    
    public:
        Board(std::size_t column_count);
        Board(const Board&) = delete;
        ~Board();

        void print(std::vector<Player *> &players, Shark *shark);
        void togglePrint();
        void placeOceanCard(OceanCard *ocean_card, Coordinates coordinates);
};

#endif