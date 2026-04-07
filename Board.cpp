#include "Board.hpp"

// Code from Github Copilot, beginning:
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
//end

void Board::print(std::vector<Player *> &players, Shark *shark) {

    if(active_){
        std::optional<Coordinates> shark_coordinates = shark->getCoordinates();
        std::size_t shark_x;
        std::size_t shark_y;
        if(shark_coordinates.has_value()){
            shark_x = shark_coordinates->getX();
            shark_y = shark_coordinates->getY();
        }

        std::cout << "" << std::endl;

        for(int i = 5; i > 0; i--){
            std::cout << i;
            for (int j = 1; j <= column_count_ + 1; j++){
                bool cell_printed = false;
                if(shark_coordinates.has_value() && shark_x == j && shark_y == i){
                    std::cout << "|" << UNICODE_SHARK << " ";
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
                            break;
                        }
                    }
                    if(!cell_printed && j <= column_count_ && card_slots_[j - 1][i - 1] != nullptr){
                        OceanCard* card = card_slots_[j - 1][i - 1];
                        std::string card_id = card->getId();
                        Utils::toUpperCase(card_id);
                        std::cout << "| " << card_id.at(0) << " ";
                        cell_printed = true;
                    }
                    if(!cell_printed){
                        std::cout << "|   ";
                    }
                }
            }
            std::cout << "" << std::endl;
        }

        for(auto* player : players){
            auto id = player->getId();
            std::cout << "   " << id;
        }

        std::cout << "" << std::endl;

        std::cout << " ";
        for(auto* player : players){
            auto rations = player->getRations();
            if(rations >= 10){
               std::cout << " 0" << rations; 
            }else{
                std::cout << " 00" << rations;
            }
        }

        std::cout << " rations" << std::endl;
        std::cout << "" << std::endl;
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

void Board::placeOceanCard(OceanCard *ocean_card, Coordinates coordinates){
    std::size_t x = coordinates.getX();
    std::size_t y = coordinates.getY();

    if(y > 1){
        card_slots_[x - 1][y - 2] = ocean_card;
    }else{
        card_slots_[x - 1][y - 1] = ocean_card;
    }
}