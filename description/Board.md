# Board

- [Assignment 1 - Only One Prevailing](../README.md)
- [Commands](./Command.md)
- [Cards](./Card.md)
- Board
- [Entities](./Entity.md)
- [Game](./Game.md)

In this part of the description, you can find the details about the `Board` and `Coordinates` classes, which serve as the frame for placing ocean cards and are important to entity-related logic.

## `Coordinates.hpp` / `Coordinates.cpp`

### Class `Coordinates`

#### Data Members (Member Variables)

- `x_`
    - stores the x coordinate as `std::size_t`
- `y_`
    - stores the y coordinate as `std::size_t`

#### Constructor / Copy Constructor / Destructor

- `Coordinates(std::size_t x, std::size_t y)`
    - constructor of the class
    - initializes all data members accordingly
- The default copy constructor should be used explicitly.
- A suitable destructor should be implemented. If the default destructor is used, this should be done explicitly.

#### Methods

- getters / setters / further methods as needed

## `Board.hpp` / `Board.cpp`

### Class `Board`

#### Data Members (Member Variables)

- `column_count_`
    - stores the number of columns (=&nbsp;number of players) as `std::size_t`
- `card_slots_`
    - stores the board structure as `std::vector<std::array<OceanCard *, 5>>`
- `active_`
    - stores whether the board is active or not as `bool`, toggled by the `board` command

#### Constructor / Copy Constructor / Destructor

- `Board(std::size_t column_count)`
    - constructor of the class
    - initializes all data members accordingly
    - `active_` is set to `true`
- The copy constructor should be deleted explicitly.
- A suitable destructor should be implemented. **Do not forget to free cards stored on the heap!**

#### Methods

- `void print(std::vector<Player *> &players, Shark *shark)`
    - handles the printing logic of the board
- `void togglePrint()`
    - toggles the `active_` member of the board for the board print
- `void placeOceanCard(OceanCard *ocean_card, Coordinates coordinates)`
    - places the given ocean card at the given coordinates on the board
- getters / setters / further methods as needed
