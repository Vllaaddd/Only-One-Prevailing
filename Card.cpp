#include "Card.hpp"

Card::Card(std::string &id):
    id_(id), owner_(nullptr) {
        if(id == "DBRIS"){
            name_ = "OCEAN_DEBRIS";
        }else if(id == "ISLND"){
            name_ = "ISLAND_CALLING";
        }else if(id == "KRKEN"){
            name_ = "KRAKEN";
        }else if(id == "WATER"){
            name_ = "CALM_WATERS";
        }else if(id == "MSSGE"){
            name_ = "MESSAGE_IN_A_BOTTLE";
        }else if(id == "RWAVE"){
            name_ = "ROGUE_WAVE";
        }else if(id == "PIRAT"){
            name_ = "PIRATE";
        }else if(id == "LOSTS"){
            name_ = "LOST_AT_SEA";
        };
}