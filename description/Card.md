# Card

- [Assignment 1 - Only One Prevailing](../README.md)
- [Commands](./Command.md)
- Cards
- [Board](./Board.md)
- [Entities](./Entity.md)
- [Game](./Game.md)

In this part of the description, you can find the details about the `Card` class, which is the base class for all cards, as well as information about all `Card` subclasses.

## Card Types

There are two types of cards in the game:
- [Ocean cards](#ocean-cards)
- [Action cards](#action-cards)

All cards with their effects are listed in this document.

## `Card.hpp` / `Card.cpp`

### Class `Card`

#### Data Members (Member Variables)

- `id_`
    - stores the ID as `std::string`
- `name_`
    - stores the name as `std::string`
- `owner_`
    - stores the owner as a `Player *`

#### Constructor / Copy Constructor / Destructor

- `Card(std::string &id)`
    - constructor of the class
    - initializes all data members accordingly
    - `owner_` is set to `nullptr`
- The copy constructor should be deleted explicitly.
- A suitable destructor should be implemented. If the default destructor is used, this should be done explicitly.

#### Methods

- pure `virtual void printInformationString()`
    - overridden by subclasses, prints the card information
- pure `virtual void printPlayMessage()`
    - overridden by subclasses, prints a message when a card is played in the game
- pure `virtual void play()`
    - overriden by subclasses, executes a card's effect
- getters / setters / further methods as needed

# OceanCard

In this part of the description, you can find the details about the `OceanCard` class, which is a subclass of the `Card` class.

## `OceanCard.hpp` / `OceanCard.cpp`

### Enum class `OceanCardType`

This enum class collects all ocean card types.
Those are `CALM_WATERS`, `OCEAN_DEBRIS`, `ISLAND_CALLING`, and `KRAKEN`.

> **Hint:** It is preferable to use strongly typed enum classes instead of ordinary enums.

### Class `OceanCard` extends `Card`

#### Data Members (Member Variables)

- `shark_icon_`
    - stores a `bool` whether or not there is a shark icon on the card

#### Constructor / Copy Constructor / Destructor

- `OceanCard(std::string &id, bool shark_icon)`
    - constructor of the class
    - initializes all data members accordingly (and calls the base class constructor)
- The copy constructor should be deleted explicitly.
- A suitable destructor should be implemented. If the default destructor is used, this should be done explicitly.

#### Methods

- `void printInformationString() override`
    - prints information about this card as specified by the `hand` and `deck` commands
- `void printPlayMessage() override`
    - prints the respective message when this card is played in the game
- `void play() override`
    - executes the effect of the given ocean card
- getters / setters / further methods as needed

# ActionCard

In this part of the description, you can find the details about the `ActionCard` class, which is a subclass of the `Card` class.

## `ActionCard.hpp` / `ActionCard.cpp`

### Enum class `ActionCardType`

This enum class collects all action card types.
Those are `MESSAGE_IN_A_BOTTLE`, `PIRATE`, `ROGUE_WAVE`, and `LOST_AT_SEA`.

### Enum class `CompassDirection`

This enum class collects the compass directions `NORTH`, `EAST`, `SOUTH`, and `WEST`.

> **Hint:** It is preferable to use strongly typed enum classes instead of ordinary enums.

### Class `ActionCard` extends `Card`

#### Data Members (Member Variables)

- `shark_direction_`
    - stores the set shark direction of the card as a `CompassDirection`
- `target_player_`
    - stores the card's target player as `Player *`

#### Constructor / Copy Constructor / Destructor

- `ActionCard(std::string &id, CompassDirection shark_direction)`
    - constructor of the class
    - initializes all data members accordingly (and calls the base class constructor)
    - `target_player_` is set to `nullptr`
- The copy constructor should be deleted explicitly.
- A suitable destructor should be implemented. If the default destructor is used, this should be done explicitly.

#### Methods

- `void printInformationString() override`
    - prints information about this card as specified by the `hand` and `deck` commands
- `void printPlayMessage() override`
    - prints the respective message when this card is played in the game
- pure `virtual void play() override`
    - overriden by subclasses, executes a card's effect
- getters / setters / further methods as needed

# PlayerActionCard

In this part of the description, you can find the details about the `PlayerActionCard` class, which is a subclass of the `ActionCard` class and represents action cards that target a player directly without requiring the selection of a specific hand card.

## `PlayerActionCard.hpp` / `PlayerActionCard.cpp`

### Class `PlayerActionCard` extends `ActionCard`

#### Data Members (Member Variables)

- none

#### Constructor / Copy Constructor / Destructor

- `PlayerActionCard(std::string &id, CompassDirection shark_direction)`
    - constructor of the class
    - initializes all data members accordingly (and calls the base class constructor)
- The copy constructor should be deleted explicitly.
- A suitable destructor should be implemented. If the default destructor is used, this should be done explicitly.

#### Methods

- `void play() override`
    - executes the effect of the given PlayerActionCard
- getters / setters / further methods as needed

# HandActionCard

In this part of the description, you can find the details about the `HandActionCard` class, which is a subclass of the `ActionCard` class and represents action cards that target a specific card in a player’s hand, requiring both a target player and a selected hand card index.

## `HandActionCard.hpp` / `HandActionCard.cpp`

### Class `HandActionCard` extends `ActionCard`

#### Data Members (Member Variables)

- `target_hand_index_`
    - stores the index of the card's target card in the hand cards of the targeted player as `std::optional<std::size_t>`

#### Constructor / Copy Constructor / Destructor

- `HandActionCard(std::string &id, CompassDirection shark_direction)`
    - constructor of the class
    - initializes all data members accordingly (and calls the base class constructor)
    - `target_hand_index_` is set to `std::nullopt`
- The copy constructor should be deleted explicitly.
- A suitable destructor should be implemented. If the default destructor is used, this should be done explicitly.

#### Methods

- `void play() override`
    - executes the effect of the given HandActionCard
- getters / setters / further methods as needed


---
# Card Overview

## Ocean Cards

Ocean Cards represent the path of a player towards the goal. Every time the player swims forward 1 space by ending their turn with the `swim` command (except if the player just moved to row 5, meaning they won), an ocean card is drawn from the deck of ocean cards and the effect of this ocean card has to be executed after the movement. Once the effect of the ocean card was executed through its `play()` method, the following text is printed:

```
[<UNICODE_OCEAN>] Drew <CARD_NAME> - <PLAY_MESSAGE>\n
```

where

- `<UNICODE_OCEAN>` stands for the symbol `🌊` or the raw UTF-8 byte sequence `\xF0\x9F\x8C\x8A`. A constant for this can be found in the `Utils.hpp` file.
- `<CARD_NAME>` is the full name of the ocean card listed in the table further below.
- `<PLAY_MESSAGE>` is the play message of the ocean card listed in the table further below.

The ocean card is then placed on the previous coordinates of the player before they moved.

> **Note:** If the ocean card that is drawn is the last one from the `ocean` deck, **its effect is not executed** and the game should end in a draw as described in the [README](../README.md) > Assignment Description > Ending The Game > Draw section.

<details>
<summary><h4>Shark Icon</h4></summary>

Each ocean card may have a shark icon. If a drawn ocean card has this icon, the following needs to happen after going through the player movement, ocean card effect and ocean card board placement, in that order:
- First time an ocean card with a shark icon is drawn: The shark is triggered and is placed directly behind the player who drew the card. If the shark is triggered while the player triggering it is still in row 1, it is placed on the same field as the player. It does not move. The following text is printed:
```
[<UNICODE_SHARK>] The shark smells food and approaches the players...\n
```

- Every subsequent time an ocean card with a shark icon is drawn: The shark will now move. The following text is printed:
```
[<UNICODE_SHARK>] Oh no, the shark is looking for food!\n
```

`<UNICODE_SHARK>` in both prints stands for the symbol `🦈` or the raw UTF-8 byte sequence `\xF0\x9F\xA6\x88`. A constant for this can be found in the `Utils.hpp` file.

When the shark moves, each player starting with player 1 has to select an action card from their hand cards to discard. Valid indices are `1` to `<NUMBER_HAND_CARDS>`. The following prompt should be **repeated** until a valid index is entered (see `getTargetHandCardIndex()` in the `CommandLine` class):

<pre><code>Select target hand card:\n:\n
P&lt;PLAYER_ID&gt;&nbsp;&gt;&nbsp;</code></pre>

The following errors must be handled (see [Return Values and Error Messages](../README.md#return-values-and-error-messages)):

- The card index is out of range.

> **Note:** If a player does not have any action cards in their hands, they should be skipped without printing the prompt for them, meaning the path of the shark will be shorter. If a player is out of the game due to having 0 rations, they should be skipped as well.

The shark directions of all selected action cards, starting with player 1, are the path the shark will take on the field. For each direction, the shark moves one space in that direction. If the shark cannot move any further in a specific direction (e.g. he is in column 1 and should move west), that movement is disregarded and it is as if the shark moved on the field he's currently on again. The following text is printed for the shark's path:

```
[<UNICODE_SHARK>] The shark will move along the path [ <COMPASS_DIRECTION_1> <COMPASS_DIRECTION_2>...<COMPASS_DIRECTION_N> ] swiftly!\n
```
where

- `<UNICODE_SHARK>` stands for the symbol `🦈` or the raw UTF-8 byte sequence `\xF0\x9F\xA6\x88`. A constant for this can be found in the `Utils.hpp` file.
- `<COMPASS_DIRECTION_1>` up to `<COMPASS_DIRECTION_N>` are the compass directions from the selected action cards, starting from the player with the lowest ID to the one with the highest who are not out of rations yet and had hand cards to select. Each compass direction should be printed as the first letter of its direction, which can be `N`, `E`, `S`, or `W`.

If the shark lands on a player's field after moving a space, it will try to eat a ration from the player and one of 2 events will happen:
  - If the player has more than 1 ration, the player's rations are reduced by 1. The following text is printed:
  ```
  [<UNICODE_SHARK>] Yum, the shark was given a ration to eat!\n
  ```
  > **Note:** This text is always printed before a player's rations are reduced.
  - If the player only has 1 ration, the shark eats this ration and the same text as above is printed. Since the player's rations are now at 0, they shouldn't be printed on the board and will not receive any further turns.

`<UNICODE_SHARK>` in both prints stands for the symbol `🦈` or the raw UTF-8 byte sequence `\xF0\x9F\xA6\x88`. A constant for this can be found in the `Utils.hpp` file.

> **Note:** The shark will never attack a player on its starting field after being triggered again, it only attacks players on fields it actively moves to. If a player is out of the game due to having 0 rations, they should be ignored as well.

> **Note:** These two cases do **not** need to be explicitly handled by your program and will **not be tested**:
> - The shark is triggered (placed on the board) behind a player that just starved after executing the `swim` command.
> - Shark movement starts after all players have starved and none are left to discard hand cards.

</details>

<details>
<summary><h4>List of Ocean Cards</h4></summary>

In the following table, you will find the effects of all ocean cards. **Current player** refers to the player whose movement triggered the ocean card.

| Card Name      | Card ID | Play Message | Effect
|----------------|---------|-------------|----------------|
| Calm Waters    | WATER   | The sea is calm, nothing happened. | Nothing happens to the current player after moving. |
| Ocean Debris   | DBRIS   | Gained a new action card! | Based on the amount of rations of the current player, a new `PIRAT` (odd rations) or `LOSTS` (even rations) card is created with the `shark_direction_` matching that of the card at index `0` of the current player's hand cards, **or**, in the case that the current player does not have any hand cards left, `shark_direction_` should default to `NORTH`. This new card is added to their hand cards. |
| Island Calling | ISLND   | Moved forward and back again due to the island's calling! | The current player moves backward one space again. It is as if the player didn't move and the ocean card is placed on the current player's field on the board. |
| Kraken         | KRKEN   | Lost a ration to the Kraken! | The current player must discard one ration. |

</details>


## Action Cards

Action cards cause instantaneous effects before being discarded and can be played through the `action` command before a player ends their turn with the `float` or `swim` commands. The effects of these cards may **Target a player** or **Target a player's card**. The effect of an action card is executed right after playing it. Once the effect of the action card was executed through its `play()` method, the following text is printed:

```
[<UNICODE_ACTION_FIRE>] Played <CARD_NAME> - <PLAY_MESSAGE>\n
```

where

- `<UNICODE_ACTION_FIRE>` stands for the symbol `🔥` or the raw UTF-8 byte sequence `\xF0\x9F\x94\xA5`. A constant for this can be found in the `Utils.hpp` file.
- `<CARD_NAME>` is the full name of the action card listed in the table further below.
- `<PLAY_MESSAGE>` is the play message of the action card listed in the table further below.

The action card is removed from the player's hand cards afterwards.

Each action card also has a `shark_direction_`, which specifies a direction for the shark when this card is selected for the shark's movement after it was triggered by an ocean card (see also the [shark icon](#ocean-cards) description).

<details>
<summary><h4>Targeting Player's Hand Cards</h4></summary>

Action cards, depending on if they just target a player or one of their hand cards, need to have either `target_player_` or both the `target_player_` and `hand_target_index_` set before calling their `play()` method. The `target_player_` is already set as part of any valid action command. The `hand_target_index_` is determined through an additional prompt when necessary, which is specified in the [README](../README.md) (see Assignment Description > Program Loop and Player Turns > Command `action`).

</details>

<details>
<summary><h4>List of Action Cards</h4></summary>

In the following table, you will find the effects of all action cards. **Current player** refers to the player who played the action card.

| Card Name           | Card ID | Action Type            | Play Message | Effect |
|---------------------|---------|------------------------|-------------|----------------|
| Message in a Bottle | MSSGE   | Target a player        | Stole up to 2 rations! | The current player steals two rations from another player. If the targeted player only has 1 ration remaining, their rations are just reduced to 0 and the current player only gains 1 ration. |
| Pirate              | PIRAT   | Target a player's card | Stole another player's hand card! | The current player steals one hand card from another player, adding it to their own hand cards. |
| Rogue Wave          | RWAVE   | Target a player        | Moved back one space! | The current player moves another player backward one space. The card has no effect if the targeted player is already standing in the first row. If they are moved back, the ocean card lying on the field they moved back to stays but will be overwritten with the ocean card drawn when they move forward again. |
| Lost at Sea         | LOSTS   | Target a player's card | Discarded another player's hand card! | The current player selects one hand card from another player. The selected card is discarded from the other player's hand cards. |

</details>


