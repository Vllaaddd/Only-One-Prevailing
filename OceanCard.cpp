#include "OceanCard.hpp"

OceanCard::OceanCard(std::string &id, bool shark_icon):
    Card(id), shark_icon_(shark_icon) {}

void OceanCard::printInformationString(Card* card){
    std::string shark_string;
    if(shark_icon_){
        shark_string = "SHARK";
    }else{
        shark_string = "NO SHARK";
    }
    std::cout << "- " << card->getName() << " - " << shark_string << std::endl;
}

void OceanCard::printPlayMessage(){
    std::cout << "OceanCard is played." << std::endl;
}

void OceanCard::play(){
    
}