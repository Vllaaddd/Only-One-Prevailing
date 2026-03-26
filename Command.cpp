#include "Command.hpp"
#include "Utils.hpp"

Command::Command(std::vector<std::string> &input_tokens){
    if(input_tokens.empty()){
        type_ = CommandType::UNKNOWN;
        return;
    }

    std::string command = input_tokens[0];
    Utils::toLowerCase(command);
    
    if(command == "quit"){
        type_ = CommandType::QUIT;
    }else if(command == "board"){
        type_ = CommandType::BOARD;
    }else if(command == "deck"){
        type_ = CommandType::DECK;
    }else if(command == "hand"){
        type_ = CommandType::HAND;
    }else if(command == "action"){
        type_ = CommandType::ACTION;
    }else if(command == "swim"){
        type_ = CommandType::SWIM;
    }else if(command == "float"){  
        type_ = CommandType::FLOAT;
    }else{
        type_ = CommandType::UNKNOWN;
    }

    for(int i = 1; i < input_tokens.size(); i++){
        parameters_.push_back(input_tokens[i]);
    }
};

Command::Command(CommandType type):
    type_(type){};

CommandType Command::getType() const{
    return type_;
}

std::vector<std::string> Command::getParameters() const{
    return parameters_;
}

void Command::setType(CommandType type){
    type_ = type;
}