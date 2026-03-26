#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <vector>
#include <iostream>

enum class CommandType{
    QUIT,
    BOARD,
    DECK,
    HAND,
    ACTION,
    SWIM,
    FLOAT,
    UNKNOWN,
    WRONG_PARAMETER_COUNT,
};

class Command{
    private:
        CommandType type_;
        std::vector<std::string> parameters_;

    public:
        Command(std::vector<std::string> &input_tokens);
        Command(CommandType type);
        Command(const Command&) = default;
        ~Command() = default;

        CommandType getType() const;
        std::vector<std::string> getParameters() const;
        void setType(CommandType type);
};

#endif