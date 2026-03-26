#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <vector>

class Player;

class Card{
    private:
        std::string id_;
        std::string name_;
        Player* owner_;

    public:
        Card(std::string &id);
        Card(const Card&) = delete;
        ~Card() = default;

        virtual void printInformationString(std::vector<Card *> deck) = 0;
        virtual void printPlayMessage() = 0;
        virtual void play() = 0;

        std::string getId() const{
            return id_;
        }

        std::string getName() const{
            return name_;
        }
                
};

#endif