#ifndef GAME_HPP
#define GAME_HPP

#include "CommandLine.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include "Shark.hpp"
#include "OceanCard.hpp"
#include "PlayerActionCard.hpp"
#include "HandActionCard.hpp"
#include <fstream>

class Game{
    private:
        CommandLine command_line_;
        Board board_;
        std::vector<Player *> players_;
        Shark* shark_;
        std::vector<ActionCard *> action_deck_;
        std::vector<OceanCard *> ocean_deck_;
        bool is_running_;
        std::size_t current_player_index_ = 0;

    public:
        Game(std::size_t player_count);
        Game(const Game&) = delete;
        ~Game() = default;

        bool checkMagicNumber(std::string &config_file_path);
        void loadConfigFile(std::string &config_file_path);
        Player* getNextPlayer();
        bool validateCommand(Command &command);
        bool executeCommand(Command &command);
        void start();
};

#endif