#ifndef OCEANCARD_HPP
#define OCEANCARD_HPP

#include "Card.hpp"
#include "Utils.hpp"
#include "Player.hpp"
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
        virtual ~OceanCard() = default;

        void printInformationString() override;
        void printPlayMessage() override;
        void play() override;

        bool getSharkIcon() const;
};

#endif