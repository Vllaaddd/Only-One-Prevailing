#include "Card.hpp"

Card::Card(std::string &id):
    id_(id), owner_(nullptr) {
        if(id == "DBRIS"){
            name_ = "Ocean Debris";
        }else if(id == "ISLND"){
            name_ = "Island Calling";
        }else if(id == "KRKEN"){
            name_ = "Kraken";
        }else if(id == "WATER"){
            name_ = "Calm Waters";
        }else if(id == "MSSGE"){
            name_ = "Message in a Bottle";
        }else if(id == "RWAVE"){
            name_ = "Rogue Wave";
        }else if(id == "PIRAT"){
            name_ = "Pirate";
        }else if(id == "LOSTS"){
            name_ = "Lost At Sea";
        };
}