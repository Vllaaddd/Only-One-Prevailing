#include "OceanCard.hpp"

OceanCard::OceanCard(std::string &id, bool shark_icon):
    Card(id), shark_icon_(shark_icon) {}

void OceanCard::printInformationString(std::vector<Card *> deck){

}

void OceanCard::printPlayMessage(){
    std::cout << "OceanCard is played." << std::endl;
}

void OceanCard::play(){
    
}