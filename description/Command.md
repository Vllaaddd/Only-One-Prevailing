# Commands & Command Line Interface

- [Assignment 1 - Only One Prevailing](../README.md)
- Commands
- [Cards](./Card.md)
- [Board](./Board.md)
- [Entities](./Entity.md)
- [Game](./Game.md)

In this part of the description, you can find the details about the classes `Command` and `CommandLine`.

## `Command.hpp` / `Command.cpp`

### Enum class `CommandType`

This enum class collects all possible command types that may be entered by a player.

Those are `QUIT`, `BOARD`, `DECK`, `HAND`, `ACTION`, `SWIM`, and `FLOAT`. It should also contain the types `UNKNOWN`
and `WRONG_PARAMETER_COUNT`, which are used to denote an unknown command and a command that was entered with the wrong
number of parameters.

> **Hint:** You need to use a strongly typed enum class instead of an ordinary enum.

### Class `Command`

This class represents a command, consisting of a command type and parameters.

#### Data Members (Member Variables)

- `type_`
  - represents the command type that was entered by the current player as a `CommandType`
- `parameters_`
  - stores all parameters that were entered by the current player (not including the command type) as
    a `std::vector<std::string>`
  - e.g., for the command `deck action`, we would just store `"action"` here

#### Constructor / Copy Constructor / Destructor

- `Command(std::vector<std::string> &input_tokens)`
  - receives the player input (already split into tokens)
  - initializes the two data members accordingly
- `Command(CommandType type)`
  - additional constructor that receives the command type directly
  - only initializes `type_`
- A suitable copy constructor and destructor should be implemented. If the default ones are used, this should be done
  explicitly.

#### Methods

- `CommandType getType()`
    - getter for `type_`
- `std::vector<std::string> &getParameters()`
    - getter for `parameters_`
- `void setType(CommandType type)`
    - setter for `type_`
- further methods as needed


## `CommandLine.hpp` / `CommandLine.cpp`

### Enum class `ErrorType`

This enum class collects all possible error types that may be encountered by the player.

Those are `UNKNOWN_COMMAND`, `PARAMETER_COUNT`, `INVALID_DECK`, `INSUFFICIENT_RATIONS`, `INVALID_ACTION_CARD`, `ACTION_CARD_NOT_IN_HAND`, `PLAYER_ID_OUT_OF_RANGE`, `TARGET_CURRENT_PLAYER`, `TARGET_PLAYER_STARVED`, `HAND_CARDS_EMPTY`, and `CARD_INDEX_OUT_OF_RANGE`.

### Class `CommandLine`

This class has already been provided to you. You can use the files as they are or extend them if needed.

#### Data Members (Member Variables)

- none

#### Constructor / Copy Constructor / Destructor

- The default constructor and destructor are used explicitly.
- The copy constructor is deleted explicitly.

#### Methods

- `void printPrompt(const Player &player) const`
  - prints the command prompt for the given player
- `void printErrorMessage(const ErrorType &error_type) const`
  - prints the error message for the given error type
- `Command getCommand() const`
  - reads input and converts it to a `Command`
- `std::size_t getTargetHandCardIndex(Player &current_player, Player &target_player) const`
  - reads an input from the current player for a hand card index of another player and checks for related errors
- getters / setters / further methods as needed
