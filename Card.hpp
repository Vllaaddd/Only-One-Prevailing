#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <vector>

class Player;

class Card{
    protected:
        std::string id_;
        std::string name_;
        Player* owner_;

    public:
        Card(std::string &id);
        Card(const Card&) = delete;
        ~Card() = default;

        virtual void printInformationString() = 0;
        virtual void printPlayMessage() = 0;
        virtual void play() = 0;

        std::string getId() const;
        std::string getName() const;

        Player* getOwner() const;
        void setOwner(Player* player);
                
};

#endif