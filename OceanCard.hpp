#ifndef OCEANCARD_HPP
#define OCEANCARD_HPP

#include "Card.hpp"
#include <iostream>

enum class OceanCardType{
    CALM_WATERS,
    OCEAN_DEBRIS,
    ISLAND_CALLING,
    KRAKEN,
};

class OceanCard: public Card{
    private:
        bool shark_icon_;

    public:
        OceanCard(std::string &id, bool shark_icon);
        OceanCard(const OceanCard&) = delete;
        ~OceanCard() = default;

        void printInformationString(std::vector<Card *> deck) override;
        void printPlayMessage() override;
        void play() override;
};

#endif