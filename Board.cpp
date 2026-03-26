#include "Board.hpp"

Board::Board(std::size_t column_count):
    column_count_(column_count), active_(true) {
        card_slots_.resize(column_count_);
        for (auto &column : card_slots_)
            column.fill(nullptr);
    }

Board::~Board() {
    for (auto &column : card_slots_) {
        for (auto &card_ptr : column) {
            delete card_ptr;
            card_ptr = nullptr;
        }
    }
}

void Board::print(std::vector<Player *> &players, Shark *shark) {

    if(active_){
        std::optional<Coordinates> shark_coordinates = shark->getCoordinates();
        std::size_t shark_x;
        std::size_t shark_y;
        if(shark_coordinates.has_value()){
            shark_x = shark_coordinates->getX();
            shark_y = shark_coordinates->getY();
        }

        for(int i = 5; i > 0; i--){
            std::cout << i;
            for (int j = 1; j <= column_count_ + 1; j++){
                bool cell_printed = false;
                if(shark_coordinates.has_value() && shark_x == j && shark_y == i){
                    std::cout << "|S  ";
                    cell_printed = true;
                }else{
                    for(auto* player: players){
                        auto coordinates = player->getCoordinates();
                        auto player_x = coordinates->getX();
                        auto player_y = coordinates->getY();
                        auto id = player->getId();
                        if(player_x == j && player_y == i && !cell_printed){
                            std::cout << "|PO" << id;
                            cell_printed = true;
                        }
                    }
                    if(!cell_printed){
                        std::cout << "|   ";
                    }
                }
            }
            std::cout << "" << std::endl;
        }
    }
}

void Board::togglePrint(){
    if(active_ == true){
        active_ = false;
        std::cout << "The board is deactivated!" << std::endl;
    }else{
        active_ = true;
        std::cout << "The board is activated!" << std::endl;
    }
}