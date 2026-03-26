# Game

- [Assignment 1 - Only One Prevailing](../README.md)
- [Commands](./Command.md)
- [Cards](./Card.md)
- [Board](./Board.md)
- [Entities](./Entity.md)
- Game

The `Game` class is the central part of this assignment. Here you will need to implement the game's logic, like
loading and parsing configuration files, handling player input, and executing commands.

## `Game.hpp` / `Game.cpp`

### Class `Game`

#### Data Members (Member Variables)

- `command_line_`
    - stores the command line as `CommandLine`
- `board_`
    - stores the board as `Board`
- `players_`
    - stores a `std::vector<Player *>` including pointers to all players, sorted in ascending order by their player ID
- `shark_`
    - stores the shark as `Shark *`
- `action_deck_`
    - stores a `std::vector<ActionCard *>` including pointers to all action cards not yet drawn by a player, in the order they were loaded from the configuration file
- `ocean_deck_`
    - stores a `std::vector<OceanCard *>` including pointers to all ocean cards not yet placed on the board, in the order they were loaded from the configuration file
- `is_running_`
    - stores whether the game is still running or not as `bool`

#### Constructor / Copy Constructor / Destructor

- `Game(std::size_t player_count)`
    - constructor of the class
    - initializes all data members accordingly, i.e.,
        - creates data member instances (command line, board, players, shark)
            > **Attention:** All entities (players and the shark) must be stored on the heap using the `new` operator. As stated in [Specification](../README.md#specification), you do **not** need to check if allocation was sucessful in this assignment. The allocated players will need to be free'd using the `delete` operator at an appropriate time, i.e., when the game ends. You should use the destructors of the `Game` class to implement this.
        - sets `is_running_` to `true`
- The copy constructor should be deleted explicitly.
- A suitable destructor should be implemented. **Do not forget to free players and cards stored on the heap!**

#### Methods

- `bool checkMagicNumber(std::string &config_file_path)`
    - checks if the configuration file can be opened and if the magic number is correct
    - called in `main.cpp` to check for invalid file errors
- `void loadConfigFile(std::string &config_file_path)`
    - loads and parses the cards from the configuration file as described in [Assignment Description](../README.md#assignment-description) > Starting the Game > Parsing the Game Config File
      > **Attention:** All cards must be stored on the heap using the `new` operator. As stated in [Specification](../README.md#specification), you do **not** need to check if allocation was sucessful in this assignment. The allocated cards will need to be free'd using the `delete` operator at an appropriate time, e.g., when they are played and discarded, or when the game ends. You should use destructors of classes whose instances store card pointers to implement this.
- `Player *getNextPlayer()`
    - finds the next player in ascending ID order within the `player_` vector of the Game whose rations are > 0 and returns it. If all players are out of rations, returns a `nullptr`.
- `bool validateCommand(Command &command)`
    - responsible for the error handling of a received command before executing it
- `bool executeCommand(Command &command)`
    - executes the given command based on the given `CommandType`
- `void start()`
    - manages the game loop logic and player turns, calling any necessary functions to do so
    - called in `main.cpp` to start the game

- getters / setters / further methods as needed
