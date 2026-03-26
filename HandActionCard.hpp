#ifndef HAND_ACTION_CARD_HPP
#define HAND_ACTION_CARD_HPP

#include "ActionCard.hpp"
#include <optional>

class HandActionCard: public ActionCard{
    private:
        std::optional<std::size_t> target_hand_index_;

    public:
        HandActionCard(std::string &id, CompassDirection shark_direction);
        HandActionCard(const HandActionCard&) = delete;
        ~HandActionCard() = default;

        void play() override;
};

#endif