#include "Game.hpp"
#include <windows.h>

Game::Game(std::size_t player_count):
    board_(player_count), shark_(new Shark()), is_running_(true){
        for(int i = 1; i <= player_count; i++){
            players_.push_back(new Player(i));
        }
}

Game::~Game(){
    for(auto* player: players_){
        delete player;
    }
    for(auto* card : action_deck_){
        delete card;
    }
    for(auto* card : ocean_deck_){
        delete card;
    }
    delete shark_;
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

    //Code from Github Copilot, beginning:
    for (auto* player : players_) {
        for (int i = 0; i < 3; i++) {
            ActionCard* card = action_deck_.back();
            card->setOwner(player);
            player->getHandCards().push_back(card);
            action_deck_.pop_back();
        }
    }
    //end
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
        }

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
    }else if(command.getType() == CommandType::SWIM){
        if(player->getRations() < 2){
            command_line_.printErrorMessage(ErrorType::INSUFFICIENT_RATIONS);
            return false;
        }
    }
    return true;
}

bool Game::executeCommand(Command &command, std::size_t target_hand_index){
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
            return true;
        }else{
            std::cout << "Cards of the ocean deck:" << std::endl;
            for(auto card : ocean_deck_){
                card->printInformationString(card);
            }
            return true;
        }
    }else if(command.getType() == CommandType::HAND){
        std::vector<ActionCard*> cards = player->getHandCards();
        std::cout << "Hand cards:" << std::endl;
        if(cards.empty()){
            std::cout << "No hand cards to display." << std::endl;
            return true;
        }else{
            for(auto card : cards){
                std::map<CompassDirection, std::string> directions = {
                    {CompassDirection::NORTH, "NORTH"},
                    {CompassDirection::EAST, "EAST"},
                    {CompassDirection::SOUTH, "SOUTH"},
                    {CompassDirection::WEST, "WEST"}
                };
                std::cout << "- " << card->getId() << " - " << card->getName() << " - " << directions[card->getSharkDirection()] << std::endl;
            }
            return true;
        }
    }else if(command.getType() == CommandType::ACTION){
        std::string card_name = command.getParameters()[0];
        int target_player_id;
        Utils::stringToInt(command.getParameters()[1], target_player_id);
        Utils::toLowerCase(card_name);
        auto& cards = player->getHandCards();
        // Code from Github Copilot, begining:
        for(int i = 0; i < cards.size(); i++){
            std::string card_id = cards[i]->getId();
            Utils::toLowerCase(card_id);
            if(card_name == card_id){
                if(card_name == "pirat" || card_name == "losts"){
                    HandActionCard* hand_card = dynamic_cast<HandActionCard*>(cards[i]);
                    if(hand_card){
                        hand_card->setTargetHandIndex(target_hand_index);
                    }
                }
                cards[i]->setTargetPlayer(players_[target_player_id - 1]);
                cards[i]->printPlayMessage();
                cards[i]->play();
                cards.erase(cards.begin() + i);
                break;
            }
        }
        //end
    }else if(command.getType() == CommandType::SWIM){
        player->move(CompassDirection::NORTH);
        std::cout << "Player " << player->getId() << " swims closer to safety." << std::endl;

        if(player->getCoordinates()->getY() == 5){
            board_.print(players_, shark_);
            std::cout << "Congratulations player " << player->getId() << ", you are the Only One Prevailing!" << std::endl;
            is_running_ = false;
            return true;
        }

        if(ocean_deck_.size() == 1){
            board_.print(players_, shark_);
            std::cout << "Beaten by the whims of the sea, the game ends in a draw... Better luck next time." << std::endl;
            is_running_ = false;
        }else{
            OceanCard* ocean_card = ocean_deck_.back();
            ocean_deck_.pop_back();

            ocean_card->printPlayMessage();
            ocean_card->setOwner(player);
            ocean_card->play();

            Coordinates coordinates = player->getCoordinates().value();
            if(ocean_card->getId() == "islnd"){
                coordinates = Coordinates(coordinates.getX(), coordinates.getY() + 1);
                board_.placeOceanCard(ocean_card, coordinates);
            }else{
                board_.placeOceanCard(ocean_card, coordinates);
            }
            
            if(player->getRations() > 1){
                player->setRations(player->getRations() - 2);
            }else if(player->getRations() == 1){
                player->setRations(0);
            }

            if(player->hasStarved()){
                std::cout << "Oh no, Player " << player->getId() << " has starved!" << std::endl;
                return true;
            }

            if(ocean_card->getSharkIcon()){
                if(shark_->isActive()){
                    std::cout << "[" << UNICODE_SHARK << "] " << "Oh no, the shark is looking for food!" << std::endl;

                    std::vector<CompassDirection> shark_path;
                    int shark_eat_times = 0;
                    for(auto* player: players_){
                        if(!player->hasStarved() && !player->getHandCards().empty()){
                            target_hand_index = command_line_.getTargetHandCardIndex(*player, *player);
                            ActionCard* selected_card = player->getHandCards()[target_hand_index];
                            CompassDirection shark_direction = selected_card->getSharkDirection();
                            shark_path.push_back(shark_direction);
                            shark_->move(shark_direction);

                            Coordinates shark_coordinates = shark_->getCoordinates().value();
                            Coordinates player_coordinates = player->getCoordinates().value();
                            if(player_coordinates.getX() == shark_coordinates.getX() && player_coordinates.getY() == shark_coordinates.getY()){
                                shark_->play(*player, players_, shark_path);      
                                shark_eat_times++;                 
                            }
                        }
                    }
                    std::cout << "[" << UNICODE_SHARK << "] " << "The shark will move along the path [";
                    for(CompassDirection direction : shark_path){
                        if(direction == CompassDirection::NORTH){
                            std::cout << " N";
                        }else if(direction == CompassDirection::SOUTH){
                            std::cout << " S";
                        }else if(direction == CompassDirection::WEST){
                            std::cout << " W";
                        }else if(direction == CompassDirection::EAST){
                            std::cout << " E";
                        }
                    }
                    std::cout << " ] swiftly!" << std::endl;
                    for(int i = 0; i < shark_eat_times; i++){
                        std::cout << "[" << UNICODE_SHARK << "] " << " Yum, the shark was given a ration to eat!" << std::endl;
                    }
                }else{
                    std::cout << "[" << UNICODE_SHARK << "] " << "The shark smells food and approaches the players..." << std::endl;
                    if(player->getCoordinates()->getY() == 1){
                        shark_->setCoordinates(player->getCoordinates()->getX(), 1);
                    }else{
                        shark_->setCoordinates(player->getCoordinates()->getX(), player->getCoordinates()->getY() - 1);
                    }
                    shark_->setTerritoryWidth(players_.size());
                }
            }
        }
        return true;
    }else if(command.getType() == CommandType::FLOAT){
        std::cout << "Player " << player->getId() << " floats in place." << std::endl;
        if(player->getRations() > 0){
            player->setRations(player->getRations() - 1);
        }

        if(player->hasStarved()){
            std::cout << "Oh no, Player " << player->getId() << " has starved!" << std::endl;
            return true;
        }
        return true;
    }
    return false;
}

void Game::start(){
    SetConsoleOutputCP(CP_UTF8);
    while(is_running_){
        Player* current_player = getNextPlayer();
        if(current_player == nullptr){
            std::cout << "All players have starved! Game over!" << std::endl;
            is_running_ = false;
            break;
        }

        if(action_deck_.size() > 1){
            ActionCard* last_deck_card = action_deck_.back();
            last_deck_card->setOwner(current_player);
            current_player->getHandCards().push_back(last_deck_card);
            action_deck_.pop_back();
        }else{
            board_.print(players_, shark_);
            is_running_ = false;
            std::cout << "Beaten by the whims of the sea, the game ends in a draw... Better luck next time." << std::endl;
            break;
        }

        board_.print(players_, shark_);

        while(true){

            command_line_.printPrompt(*current_player);
            Command command = command_line_.getCommand();

            if(validateCommand(command)){
                std::size_t target_hand_index = 0;
                if(command.getType() == CommandType::ACTION){
                    std::string card_name = command.getParameters()[0];
                    Utils::toLowerCase(card_name);

                    if(card_name == "pirat" || card_name == "losts"){
                        int target_player_id;
                        Utils::stringToInt(command.getParameters()[1], target_player_id);
                        Player* target_player = players_[target_player_id - 1];
                        target_hand_index = command_line_.getTargetHandCardIndex(*current_player, *target_player);
                    }
                }
                executeCommand(command, target_hand_index);

                if(!is_running_ || command.getType() == CommandType::SWIM || command.getType() == CommandType::FLOAT){
                    break;
                }
            }
        }
    }
};