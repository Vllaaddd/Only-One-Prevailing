#include "Game.hpp"

Game::Game(std::size_t player_count):
    board_(player_count), shark_(new Shark()), is_running_(true){
        for(int i = 1; i <= player_count; i++){
            players_.push_back(new Player(i));
        }
}

bool Game::checkMagicNumber(std::string &config_file_path){
    std::fstream config_file(config_file_path);
    if(!config_file.is_open()){
        return false;
    }

    std::string magic_number;
    std::getline(config_file, magic_number);

    if(magic_number != "OOP"){
        return false;
    }else{
        return true;
    }
}

void Game::loadConfigFile(std::string &config_file_path){
    std::fstream config_file(config_file_path);
    if(!config_file.is_open()){
        std::cout << "Could not open file!" << std::endl;
        return;
    }

    std::string first_line;
    std::getline(config_file, first_line);

    std::string card;
    while(std::getline(config_file, card)){
        std::string card_id = card.substr(2, 5);
        if(card.at(0) == 'O'){
            std::string shark_icon = card.substr(8, 1);
            if(shark_icon == "T"){
                ocean_deck_.push_back(new OceanCard(card_id, true));
            }else{
                ocean_deck_.push_back(new OceanCard(card_id, false));
            }
        }else if(card.at(0) == 'A'){
            std::string shark_direction = card.substr(8, 1);
            if(card_id == "MSSGE" || card_id == "RWAVE"){
                if(shark_direction == "N"){
                    action_deck_.push_back(new PlayerActionCard(card_id, CompassDirection::NORTH));
                }else if(shark_direction == "E"){
                    action_deck_.push_back(new PlayerActionCard(card_id, CompassDirection::EAST));
                }else if(shark_direction == "S"){
                    action_deck_.push_back(new PlayerActionCard(card_id, CompassDirection::SOUTH));
                }else if(shark_direction == "W"){
                    action_deck_.push_back(new PlayerActionCard(card_id, CompassDirection::WEST));
                }
            }else if(card_id == "PIRAT" || card_id == "LOSTS"){
                if(shark_direction == "N"){
                    action_deck_.push_back(new HandActionCard(card_id, CompassDirection::NORTH));
                }else if(shark_direction == "E"){
                    action_deck_.push_back(new HandActionCard(card_id, CompassDirection::EAST));
                }else if(shark_direction == "S"){
                    action_deck_.push_back(new HandActionCard(card_id, CompassDirection::SOUTH));
                }else if(shark_direction == "W"){
                    action_deck_.push_back(new HandActionCard(card_id, CompassDirection::WEST));
                }
            }
        }
    }

    for (auto* player : players_) {
        for (int i = 0; i < 3; i++) {
            player->getHandCards().push_back(action_deck_.front());
            action_deck_.erase(action_deck_.begin());
        }
    }
}

Player* Game::getNextPlayer(){
    for(int i = 0; i < players_.size(); i++){

        if(current_player_index_ >= players_.size()){
            current_player_index_ = 0;
        }
        
        Player* current_player = players_[current_player_index_];
        current_player_index_++;

        if(!current_player->hasStarved()){
            return current_player;
        }
    }
    return nullptr;
}

bool Game::validateCommand(Command &command){
    Player* player = players_[current_player_index_ - 1];

    if(command.getType() == CommandType::UNKNOWN){
        command_line_.printErrorMessage(ErrorType::UNKNOWN_COMMAND);
        return false;
    }else if(command.getType() == CommandType::WRONG_PARAMETER_COUNT){
        command_line_.printErrorMessage(ErrorType::PARAMETER_COUNT);
        return false;
    }else if(command.getType() == CommandType::DECK){
        std::string param = command.getParameters()[0];
        Utils::toLowerCase(param);
        if(param != "ocean" && param != "action"){
            command_line_.printErrorMessage(ErrorType::INVALID_DECK);
            return false;
        }
    }else if(command.getType() == CommandType::ACTION){
        std::string card_name = command.getParameters()[0];
        Utils::toLowerCase(card_name);
        int target_player_id;
        Utils::stringToInt(command.getParameters()[1], target_player_id);
        if(card_name != "mssge" && card_name != "pirat" && card_name != "rwave" && card_name != "losts"){
            command_line_.printErrorMessage(ErrorType::INVALID_ACTION_CARD);
            return false;
        }else if(target_player_id < 1 || target_player_id > players_.size()){
            command_line_.printErrorMessage(ErrorType::PLAYER_ID_OUT_OF_RANGE);
            return false;
        }else if(target_player_id == player->getId()){
            command_line_.printErrorMessage(ErrorType::TARGET_CURRENT_PLAYER);
            return false;
        }else if(players_[target_player_id - 1]->hasStarved()){
            command_line_.printErrorMessage(ErrorType::TARGET_PLAYER_STARVED);
            return false;
        }else if(card_name == "pirat" || card_name == "losts"){
            if(players_[target_player_id - 1]->getHandCards().empty()){
                command_line_.printErrorMessage(ErrorType::HAND_CARDS_EMPTY);
                return false;
            }
        }else{
            std::vector<ActionCard *> player_cards = player->getHandCards();
            for(int i = 0; i < player_cards.size(); i++){

                std::string card = player_cards[i]->getId();
                Utils::toLowerCase(card);
                if(card_name == card){
                    return true;
                }
            }
            command_line_.printErrorMessage(ErrorType::ACTION_CARD_NOT_IN_HAND);
            return false;
        }
    }else if(command.getType() == CommandType::SWIM){
        if(player->getRations() < 2){
            command_line_.printErrorMessage(ErrorType::INSUFFICIENT_RATIONS);
            return false;
        }
    }
    return true;
}

bool Game::executeCommand(Command &command){
    Player* player = players_[current_player_index_ - 1];
    if(command.getType() == CommandType::QUIT){
        is_running_ = false;
        return true;
    }if(command.getType() == CommandType::BOARD){
        board_.togglePrint();
        return true;
    }if(command.getType() == CommandType::DECK){
        std::string deck_type = command.getParameters()[0];
        Utils::toLowerCase(deck_type);
        if(deck_type == "action"){
            std::cout << "Cards of the action deck:" << std::endl;
            for(auto card : action_deck_){
                card->printInformationString(card);
            }
        }else{
            std::cout << "Cards of the ocean deck:" << std::endl;
            for(auto card : ocean_deck_){
                card->printInformationString(card);
            }
        }
    }else if(command.getType() == CommandType::HAND){
        std::vector<ActionCard*> cards = player->getHandCards();
        std::cout << "Hand cards:" << std::endl;
        for(auto card : cards){
            card->printInformationString(card);
        }
    }
    return false;
}

void Game::start(){
    std::cout << "Game started!" << std::endl;

    while(is_running_){
        Player* current_player = getNextPlayer();
        if(current_player == nullptr){
            std::cout << "All players have starved! Game over!" << std::endl;
            is_running_ = false;
            break;
        }

        board_.print(players_, shark_);

        while(true){

            command_line_.printPrompt(*current_player);
            Command command = command_line_.getCommand();

            if(validateCommand(command)){
                executeCommand(command);
                if(is_running_ == false){
                    break;
                }
            }
            

            if(command.getType() == CommandType::SWIM || command.getType() == CommandType::FLOAT){
                break;
            }
        }
    }
};