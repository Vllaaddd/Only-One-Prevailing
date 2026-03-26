# Entity

- [Assignment 1 - Only One Prevailing](../README.md)
- [Commands](./Command.md)
- [Cards](./Card.md)
- [Board](./Board.md)
- Entities
- [Game](./Game.md)

In this part of the description, you can find the details about the `Entity` class, which is the base class for all
entities, as well as information about all `Entity` subclasses.

## `Entity.hpp` / `Entity.cpp`

### Enum class `EntityType`

This enum class collects all entity types.
Those are `PLAYER` and `SHARK`.

> **Hint:** It is preferable to use strongly typed enum classes instead of ordinary enums.

### Class `Entity`

#### Data Members (Member Variables)

- `type_`
    - stores the type as `EntityType`
- `coordinates_`
    - stores the coordinates of an entity as `std::optional<Coordinates>`

#### Constructor / Copy Constructor / Destructor

- `Entity(EntityType type)`
    - constructor of the class
    - initializes all data members accordingly
- `Entity(EntityType type, std::size_t x, std::size_t y)`
    - constructor of the class that also accepts initial coordinate values
    - initializes all data members accordingly
- The copy constructor should be deleted explicitly.
- A suitable destructor should be implemented. If the default destructor is used, this should be done explicitly.

#### Methods

- pure `virtual bool move(CompassDirection movement_direction)`
    - overridden by subclasses, executes the respective movement of an entity, returns `true` if it was able to move
- getters / setters / further methods as needed

# Player

In this part of the description, you can find the details about the `Player` class, which is a subclass of the `Entity` class.

## `Player.hpp` / `Player.cpp`

### Class `Player` extends `Entity`

#### Data Members (Member Variables)

- `id_`
    - stores the player's ID as `std::size_t`
- `hand_cards_`
    - stores the player's hand cards as `std::vector<ActionCard *>`
- `rations_`
    - stores the player's rations as `std::size_t`

#### Constructor / Copy Constructor / Destructor

- `Player(std::size_t id)`
    - constructor of the class
    - initializes all data members accordingly (and calls the base class constructor)
    - `rations_` should be set to 12.
    - `type_` should be set to `PLAYER`
    - `coordinates_` should be set to the column with the same ID as the player's ID and row 1 (so player 1 starts in (1,1), player 2 starts in (2,1), etc.)
- The copy constructor should be deleted explicitly.
- A suitable destructor should be implemented. **Do not forget to free cards stored on the heap!**

#### Methods

- `bool move(CompassDirection movement_direction) override`
    - executes the player's movement, returns `true` if they were able to move
- `bool hasStarved()`
    - checks whether player's rations are <= 0. If yes, returns `true`, otherwise `false`
- `std::vector<ActionCard *> &getHandCards()`
    - getter for the `hand_cards_` of a player
    - needed in the `CommandLine` class
- `std::size_t getId()`
    - getter for the `id_` of a player
    - needed in the `CommandLine` class
- getters / setters / further methods as needed

## Staying in the Game

If at any point in the game a player's rations reach 0, no matter if this is caused by another player's action card, an ocean card, a shark attack or the `float`/`swim` commands, they shouldn't be printed on the board and will not receive any further turns.

When a player's rations reach 0, the following text should be printed:

```
Oh no, Player <PLAYER_ID> has starved!\n
```

During the `swim` command, multiple ration decreases may occur that could reduce a player's rations to < 0. Take care that they stay at 0 and the text above is only printed once.

**Example:** Player 1 swims with 2 rations and draws the `KRAKEN` ocean card with a shark icon (shark is active), reducing their rations to 1. The ration decrease from swim would reduce their rations to -1, but this is adjusted to 0. The above text is printed once. Player 1 will not be considered in the following shark movement.

# Shark

In this part of the description, you can find the details about the `Shark` class, which is a subclass of the `Entity`
class.

## `Shark.hpp` / `Shark.cpp`

### Class `Shark` extends `Entity`

#### Data Members (Member Variables)

- `territory_width_`
    - stores the shark's territory width as `std::size_t`, the territory spans across the entire board

#### Constructor / Copy Constructor / Destructor

- `Shark()`
    - constructor of the class
    - initializes all data members accordingly (and calls the base class constructor)
    - `type_` should be set to `SHARK`
    - `coordinates_` should be set to `std::nullopt` before the shark is active
- The copy constructor should be deleted explicitly.
- A suitable destructor should be implemented. If the default destructor is used, this should be done explicitly.

#### Methods

- `bool move(CompassDirection movement_direction) override`
    - executes the shark's movement, returns `true` if they were able to move
- `bool isActive()`
    - should return `true` if and only if `coordinates_` has a value other than `std::nullopt`
        > **Hint:** You can use `std::optional<Coordinates>::has_value()` in this method.
- `void play(Player &current_player, std::vector<Player *> &players, std::vector<CompassDirection> &shark_path)`
    - handles the initial shark's trigger as well as the shark's movement after the players selected the hand cards to be used for the shark's path
- getters / setters / further methods as needed
