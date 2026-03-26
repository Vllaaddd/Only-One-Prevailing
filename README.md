# Assignment 1 - Only One Prevailing

- Assignment 1 - Only One Prevailing
- [Commands](./description/Command.md)
- [Cards](./description/Card.md)
- [Board](./description/Board.md)
- [Entities](./description/Entity.md)
- [Game](./description/Game.md)

This assignment involves implementing a small card game for 2-5 players, where each player aims to be the first castaway to leave the shark-infested waters. Players can use action cards to influence the game but must also carefully manage their rations to survive.

## Introduction

In Assignment 1 (A1) of the OOP1 practicals (KU) you will implement a small card game loosely based on
[Selfish: Shipwrecked Edition](https://en.wikibooks.org/wiki/Selfish/Shipwrecked_Edition).

This document describes the structure of the assignment and the expected functionality of the program.

## Learning Goals

- Foundations of classes:
    - attributes, methods
    - constructor, copy constructor, destructor
    - inheritance, virtual functions
- Strings & streams:
    - `std::string`
    - files
- Some data structures of the standard library:
    - e.g. `std::vector`

## Specification

Some general specifications must be followed for every assignment in this course. A list of these specifications can be
found
here: [Assessment of Assignments - Deductions](https://coding-tugraz.notion.site/Assessment-of-Assignments-How-do-you-get-your-points-00d2624846f4491391b389e6a48fa180#0af0c923deff4c4bb8740f5698aca451)

Please follow these specifications to avoid point deductions.

Additionally, the following specifications must be followed for this assignment (A1) as well:

- You **must** implement and use all described classes in your assignment. The required classes are described in detail
  in the [description directory](./description).
- The provided `main.cpp` **must not** be changed and is replaced with the original version in our test system. The
  existing functionalities in `Utils.hpp/cpp` and `CommandLine.hpp/cpp` should not be changed,
  however, you are allowed to extend these classes. They will not be replaced in the test system.

If any of these specifications are not followed, this may result in a deduction **of up to 25%** per specification.

In this assignment (but only in this one), you do not have to check if memory was allocated successfully.

## Grading

Assignment 1 is worth **20 points**.

> **Attention:** If you pass **less than half of the public test cases for A1** you will be deregistered from the OOP1 KU without a grade.

Information on how your assignment submission will be assessed can be found
here: [Assessment of Assignments](https://coding-tugraz.notion.site/Assessment-of-Assignments-How-do-you-get-your-points-00d2624846f4491391b389e6a48fa180)

Here you can find an overview of how your total grade for the KU will be
calculated: [Procedure and Grading](https://coding-tugraz.notion.site/Practicals-structure-grading-and-plagiarism-76127221ed43451abc7ffba7852595e3)

There will be a mandatory **in-person coding task** for A1 in the week following the A1 deadline.

## Submission

- Push to your repository
- The last commit on the main branch before the deadline will be graded
- Deliverables: all `.cpp` and `.hpp` files needed to run your program
- **Deadline: 15.04.2026, 18:00 (Austrian time)**
- **Assignment 1 is solo work!** See
  our [Guidelines on Plagiarism](https://coding-tugraz.notion.site/Practicals-structure-grading-and-plagiarism-76127221ed43451abc7ffba7852595e3#93a62cfe219949929fa2fc41f2f1ff37)

> **Note:** Please also pay attention to the section on how to use and cite ChatGPT or similar!

## General Notes

The notes given in this section are important for the entire assignment description:

- `\n` should not be printed as separate characters, instead they represent the newline character.
- Note the leading and trailing spaces in the text fields! You can make them visible by selecting the text field.
- Words in angle brackets (such as `<PLAYER_ID>`) should be replaced by calculated or given data. They are **not** part of the output itself! For a better understanding, you can look at the [example outputs](#example-outputs) at the very bottom of this document.
- The user input is **case-insensitive**. This means that `quit`, `qUiT` and `QUIT` would all be valid inputs.
- All additional whitespaces (leading, trailing, or additional whitespaces between command and parameters or between
  two parameters) in the input should be ignored.
- EOF (End of File, not the string "EOF") does not need to be specifically handled for inputs in this assignment.
- The program must correctly handle arbitrary user input, including incorrect data types (e.g., strings instead of integers) and inputs of varying length.

> **Note:** Any changes made to the upstream repository will be announced on our Discord server. Please make sure to [join the server](https://discord.gg/j9akDMy4HQ) and then join the OOP1 group in the `#roles` channel.

## Framework

We provide a `main.cpp` file that must be used as the starting point of your program. This file must not be modified, as it will be replaced by the test system with the original version. Your program must therefore remain fully compatible with it.

Additionally, we provide the class `Utils` (`Utils.hpp/cpp`), which contains functions for safely converting strings to numeric values and for trimming whitespace from strings. We also provide the class `CommandLine` (`CommandLine.hpp/cpp`), which should be used to convert user input into `Command` objects. The existing functionality should not be changed, but you can extend these classes if needed.


## Custom Data Types / Classes

After reading the assignment description below, it is recommended to begin by defining the custom data types (i.e., classes) used in this program. Detailed descriptions of all required classes can be found in the [description directory](./description).

At this stage, you are not required to fully implement the described methods. However, all methods need to be declared in order for your program to successfully compile.

All data members (member variables) of every class must be declared as `private` or `protected`. You may add additional member variables and methods to any class if necessary.

## Assignment Description

**Only One Prevailing** is a turn-based survival card game for 2-5 players. Each player controls a castaway trying to survive and reach the top of a board while managing their rations. The game is played on a **vertical board** with one column per player and five rows. The bottom row (row 1) is the starting point for all players, and the top row (row 5) is the goal.

This is an example of how the board may look like after two turns.

```
\n
 5 |   |   |   |   |   |\n
 4 |   |🦈 |   |   |   |\n
 3 |   |P02|   |   |P05|\n
 2 |   | D |   |P04| W |\n
 1 |P01| K |P03| W | K |\n
     1   2   3   4   5  \n
    009 005 012 009 007 rations\n
\n
```
For further details on the structure of the board, see Assignment Description > Board.

Players have **rations** (see bottom of the board aligned with each player) that are spent to either move forward (`swim`) or stay in place (`float`). They also have [**action cards**](./description/Card.md#action-cards) that can be used to influence themselves and other players. Additionally, [**ocean cards**](./description/Card.md#ocean-cards) drawn when swimming introduce hazards or events that may help or hinder players and represent their path on the board (e.g. see the letters `D`, `K` and `W`, above).

A **shark**(`🦈`) is present on the board and represents a major threat. It can consume players’ rations and move depending on the effects of ocean or action cards.

**Objective:** Be the first player to reach the top row.

Detailed information about the game mechanics, gameplay behavior, cards, and entities is provided both in this document and in the [description directory](./description).

<details>
<summary><h3>Starting the Game</h3></summary>

The program is executed with two command-line arguments:

```
./a1 <PLAYER_COUNT> <CONFIG_PATH>
```

The first argument, `<PLAYER_COUNT>`, specifies the number of players. The second argument, `<CONFIG_PATH>`, specifies the path to the game configuration file.

For example, a valid program execution is:

```
./a1 4 configs/game_config.txt
```

If the program is executed

- with the wrong number of arguments,
- with an invalid number of players (must be an integer greater or equal to 2 and smaller or equal to 5), or
- with a game configuration file that cannot be opened or does not start with the correct magic number `OOP\n`,

the corresponding error message should be printed and the program should terminate with the correct return
value (see [Return Values and Error Messages](#return-values-and-error-messages)).

<details>
<summary><h4>Parsing the Game Config File</h4></summary>

The game reads its initial data from the provided configuration file. The file must be parsed as follows:

The first line of every configuration file contains a magic number (`OOP\n`). This string must be checked for correctness. If the magic number is valid, you may assume that the remainder of the file is correctly formatted and no further validation of its contents is required.

Following the first line, the ocean cards are listed.

After all ocean cards, the action cards are listed.

Each subsequent line represents a single card and consists of:

- its type (`O` for ocean card, `A` for action card)
- its card ID (see also [Card Overview](./description/Card.md#card-overview))
- either `TRUE`/`FALSE` indicating the presence of a shark icon (for ocean cards)
- `NORTH`/`SOUTH`/`EAST`/`WEST` indicating the shark direction (for action cards)

These values are separated by the character `;`.

Cards must be added to their respective decks in the order in which they appear in the configuration file. For example, the ocean card in line 2 of the file will be stored at index `0` of the member `Game::ocean_deck_`, the ocean card in line 3 at index `1`, and so on.

For example, a valid configuration file containing 20 cards looks as follows:

```
OOP\n
O;WATER;FALSE\n
O;DBRIS;FALSE\n
O;ISLND;FALSE\n
O;KRKEN;FALSE\n
O;WATER;TRUE\n
O;DBRIS;FALSE\n
O;ISLND;TRUE\n
O;KRKEN;FALSE\n
O;WATER;FALSE\n
O;DBRIS;FALSE\n
A;MSSGE;NORTH\n
A;PIRAT;SOUTH\n
A;RWAVE;EAST\n
A;LOSTS;WEST\n
A;MSSGE;NORTH\n
A;PIRAT;SOUTH\n
A;RWAVE;EAST\n
A;LOSTS;WEST\n
A;MSSGE;NORTH\n
A;PIRAT;SOUTH\n
```

After parsing the configuration file, each player is dealt three action cards in ascending order of player IDs (i.e., player 1 receives three cards first, followed by player 2, and so on). You may assume that the configuration file always contains enough action cards to distribute the initial three cards to every player.

</details>
</details>

<details>
<summary><h3>Welcome Message</h3></summary>

Next, the players should be greeted with the output:

```
Welcome to Only One Prevailing!\n
```

After the welcome message, the current board should be printed once as described below (see Assignment Description > Board). Then, the players can start
entering commands (see Assignment Description > Program Loop and Player Turns).

</details>

<details>
<summary><h3>Board</h3></summary>

At the beginning of the game, and each time the board (stored in member `Game::board_`) is updated as a result of a `swim` or `float` command (if the board print is active), it should be printed in the following format:

```
\n
 5 |   |   |   |   |   |\n
 4 |   |   |   |   |   |\n
 3 |   |   |   |   |   |\n
 2 |   |   |   |   |   |\n
 1 |P01|P02|P03|P04|P05|\n
     1   2   3   4   5  \n
    012 012 012 012 012 rations\n
\n
```

- Empty fields are printed as <code>|&nbsp;&nbsp;&nbsp;|</code>.
- When a [player](./description/Entity.md#player) occupies a field, it is printed as `|P<PLAYER_ID>|`, where `<PLAYER_ID>` is the player's ID (an integer from 1 to 5), **zero-padded to two digits**.
- After a player has traversed a field, it will contain the ocean card that was drawn when the player moved past it. It is then printed as `| <FIRST_LETTER_OCEAN_CARD_ID |`. Valid letters are `W`, `D`, `I`, and `K` according to the ocean card IDs found in the [card](./description/Card.md#ocean-cards) descriptions.
- When the [shark](./description/Entity.md#shark) occupies a field, it is always printed as `|<UNICODE_SHARK> |`, even if a player is also on the same field. `<UNICODE_SHARK>` stands for the symbol 🦈 or the raw UTF-8 byte sequence `\xF0\x9F\xA6\x88`. A constant for this can be found in the `Utils.hpp` file.
- The last row displays the rations of each player **zero-padded to three digits** and should be aligned with the respective player's column as shown above.

> **Note:** The number of columns on the board varies depending on the number of players.

Example of the board during a game with three players:

```
\n
 5 |   |   |   |\n
 4 |   |   |   |\n
 3 |P01|   |   |\n
 2 | W | K |🦈 |\n
 1 | W |P02| W |\n
     1   2   3  \n
    008 007 009 rations\n
\n
```

In this example, the shark currently occupies the same field as player 3. There is an ocean card in front of player 2 as they swam forward twice before being pushed back 2 spaces again by the action card(s) of another player.

</details>

<details>
<summary><h3>Program Loop and Player Turns</h3></summary>

At the beginning of a player's turn, the top card from the action card deck is drawn and added to the player's hand. If the drawn card was the last remaining card in the action deck, the game ends immediately in a draw (see Assignment Description > Ending the Game > Draw).

The player may then play any number of action cards from their hand using the `action` command. The turn ends when the player executes either:

- the `float` command, to remain in place while spending 1 ration, or
- the `swim` command, to move one space forward while spending 2 rations.

Whenever a player is asked to input a command before ending their turn, the following prompt must be printed:

<pre><code>P&lt;PLAYER_ID&gt;&nbsp;&gt;&nbsp;</code></pre>

where `<PLAYER_ID>` is the ID of the current player, i.e., an integer from 1 to 5. **Note the leading and trailing spaces.**

If a player enters an unknown command, it is treated as an error. Additionally, all commands must be checked for errors as specified in their descriptions. If a command is invalid, print the appropriate error message (see [Return Values and Error Messages](#return-values-and-error-messages)) and prompt the current player to enter a command again.

After a command is successfully executed, prompt the current player (which may have changed) again with the command prompt, except in the case of the `quit` command.

All possible commands are listed below:

<details>
<summary><h4>Command <code>quit</code></h4></summary>

Syntax: `quit`

This command allows the program to be terminated early. As with normal game termination (see Assignment Description > Ending the Game), the program must release all resources and terminate with a return value of `0`.

**Error Handling**

The following errors must be handled (see [Return Values and Error Messages](#return-values-and-error-messages)):

- The command was called with too many or too few parameters.

</details>

<details>
<summary><h4>Command <code>board</code></h4></summary>

Syntax: `board`

This command should toggle the output of the game board, i.e., deactivate it when it is active and vice versa. Whenever the output of the game board is activated, it should be printed once. By
default, when the game is started, the output of the game board is active.

**Error Handling**

The following errors must be handled (see [Return Values and Error Messages](#return-values-and-error-messages)):

- The command was called with too many or too few parameters.

</details>

<details>
<summary><h4>Command <code>deck</code></h4></summary>

> **Attention:** This command is only used to test your program, in the actual game itself, players would not be able to view which cards they will draw next.

Syntax: `deck <DECK_TYPE>`

where

- `<DECK_TYPE>` is the type of the card deck to view (`action` or `ocean`).

This command should print the cards of the referenced card deck as a list of the following format:

```
Cards of the <DECK_TYPE> deck:\n
- <CARD_NAME_1> - <COMPASS_DIRECTION_1/SHARK_ICON_1>\n
- <CARD_NAME_2> - <COMPASS_DIRECTION_2/SHARK_ICON_2>\n
...
- <CARD_NAME_N> - <COMPASS_DIRECTION_N/SHARK_ICON_N>\n
```

where

- `<DECK_TYPE>` is the type of the card deck to view (`action` or `ocean`), and
- `<CARD_NAME_1>` up to `<CARD_NAME_N>` are the names of all cards included in the given deck, 
in the order that they were added to the deck, from the card that was added first (`1`) to the card that was added last (`N`), and
- `<COMPASS_DIRECTION_1/SHARK_ICON_1>` up to `<COMPASS_DIRECTION_N/SHARK_ICON_N>` are, for action cards, the compass directions and, for ocean cards, the shark icons of all cards included in the given deck, in the order that they were added to the deck, from the card that was added first (`1`) to the card that was added last (`N`). Compass directions for action cards should be printed as `NORTH`, `SOUTH`, `EAST` or `WEST`. Shark icons for ocean cards should be printed as `SHARK` or `NO SHARK`.

The ellipsis (`...`) should **not** be printed!

> **Note:** As the game ends as soon as a deck of cards becomes empty, the case of printing an empty deck does **not** need to be handled.

**Error Handling**

The following errors must be handled (see [Return Values and Error Messages](#return-values-and-error-messages)):

- The command was called with too many or too few parameters.
- The given `<DECK_TYPE>` is invalid.

</details>

<details>
<summary><h4>Command <code>hand</code></h4></summary>

Syntax: `hand`

This command should print the cards of the current player as a list of the following format:

```
Hand cards:\n
- <CARD_ID_1> - <CARD_NAME_1> - <COMPASS_DIRECTION_1>\n
- <CARD_ID_2> - <CARD_NAME_2> - <COMPASS_DIRECTION_2>\n
...
- <CARD_ID_N> - <CARD_NAME_N> - <COMPASS_DIRECTION_N>\n
```

where

- `<CARD_ID_1>` up to `<CARD_ID_N>` are the IDs of all cards of the current player, in the order that they were drawn from the deck, from the earliest (`1`) to the last drawn card (`N`), and
- `<CARD_NAME_1>` up to `<CARD_NAME_N>` are the names of all cards of the current player, in the order that they were drawn from the deck, from the earliest (`1`) to the last drawn card (`N`), and
- `<COMPASS_DIRECTION_1>` up to `<COMPASS_DIRECTION_N>` are the compass directions of all cards of the current player, in the order that they were drawn from the deck, from the earliest (`1`) to the last drawn card (`N`). They should be printed as `NORTH`, `SOUTH`, `EAST` or `WEST`.

The ellipsis (`...`) should **not** be printed!

If the current player does not have any cards in their hand, the following message should be printed instead:

```
No hand cards to display.\n
```

**Error Handling**

The following errors must be handled (see [Return Values and Error Messages](#return-values-and-error-messages)):

- The command was called with too many or too few parameters.

</details>

<details>
<summary><h4>Command <code>action</code></h4></summary>

Syntax: `action <ACTION_NAME> <TARGET_PLAYER_ID>`

where

- `<ACTION_NAME>` must be replaced by the exact ID of an action card.
- `<TARGET_PLAYER_ID>` must be replaced with the ID of **a player other than the current player** that should be targeted by the chosen action card.

This command allows the player to select an action card from their hand cards to play. The `<TARGET_PLAYER_ID>` should be used to set the respective attribute of the action card. Some cards may also need a target hand card index to be selected and set. The effect of the selected action card is executed immediately and the card is removed from the player's hand cards afterwards. A detailed description of all action card effects can be found in the [Card](./description/Card.md) descriptions.

**Error Handling**

The following errors must be handled (see [Return Values and Error Messages](#return-values-and-error-messages)):

- The command was called with too many or too few parameters.
- The given `<ACTION_NAME>` does not exist.
- A valid `<ACTION_NAME>` card is not part of the player's hand cards.
- The `<TARGET_PLAYER_ID>` is out of range.
- The `<TARGET_PLAYER_ID>` is equal to the the current player's ID.
- The player with `<TARGET_PLAYER_ID>` is not part of the game anymore since their rations are at 0.
- Targeted player has no hand cards to target. (Only applicable if the selected action card targets a player's card)

Some action cards may also target a specific [hand card](./description/Card.md#action-cards) of the targeted player. The following command prompt should be printed every time a player enters a valid action command for an action card that **targets a player's card** and **repeated** until a valid input is entered:

<pre><code>Select target hand card:\n
P&lt;PLAYER_ID&gt;&nbsp;&gt;&nbsp;</code></pre>

Valid indices are `1` to `<NUMBER_HAND_CARDS>` of the targeted player. The following errors must be handled (see [Return Values and Error Messages](../README.md#return-values-and-error-messages)):

- The card index is out of range.

</details>

<details>
<summary><h4>Command <code>swim</code></h4></summary>

Syntax: `swim`

This command ends a player's turn by spending 2 rations to move one space forward on the board. Once a valid `swim` command was entered, the following message should be printed:

```
Player <PLAYER_ID> swims closer to safety.\n
```
where

- `<PLAYER_ID>` must be replaced by the ID of the player executing the command.

The following actions need to happen in order:
- The player moves forward on the board. If this moves them to row 5 they have won and the game ends (see Assignment Description > Ending the Game > Winning The Game).
- An ocean card is drawn from the ocean card deck. If the drawn card was the last remaining card in the ocean deck, the game ends immediately in a draw (see Assignment Description > Ending the Game > Draw).
- The current player is set as the owner of the ocean card and its effect is executed on the player before placing the card on the field behind the player. A detailed description of all ocean card effects can be found in the [Card](./description/Card.md) descriptions.
- The current player's rations are decreased by 2 for the `swim` command.
- If the ocean card had a shark icon, the shark's trigger/movement has to be handled (see also in the [Card](./description/Card.md) descriptions).
- Finally, the board is printed if the print is active.

**Error Handling**

The following errors must be handled (see [Return Values and Error Messages](#return-values-and-error-messages)):

- The command was called with too many or too few parameters.
- The player has fewer than 2 rations available to spend.

</details>

<details>
<summary><h4>Command <code>float</code></h4></summary>

Syntax: `float`

This command ends a player's turn by spending 1 ration to stay where they are on the board without drawing an ocean card. Once a valid `float` command was entered, the following message should be printed:

```
Player <PLAYER_ID> floats in place.\n
```
where

- `<PLAYER_ID>` must be replaced by the ID of the player executing the command.

Afterwards, the player's rations are decreased by 1 and the board is printed if the print is active.

**Error Handling**

The following errors must be handled (see [Return Values and Error Messages](#return-values-and-error-messages)):

- The command was called with too many or too few parameters.

</details>

</details>

<details>
<summary><h3>Ending the Game</h3></summary>

#### Winning the Game

The goal of each player is to be the first to reach the top row of the board (row 5). When a player executes the `swim` command in row 4, the command ends early after just the movement, the player does not need to draw an ocean card anymore and their rations are not decreased. They have won the game. After the board has been printed for one final time (if the print is active), the following message should be displayed:

```
\n
Congratulations player <PLAYER_ID>, you are the Only One Prevailing!\n
```

where

- `<PLAYER_ID>` is the ID of the current player, i.e., an integer from 1 to 5.

After printing the message, the program must release all resources and terminate with a return value of `0`.

#### Draw

In the **special case** that a deck (`action` or `ocean`) becomes empty while a player needs to draw a card:
- If the last card from the `action` deck is drawn, the game ends immediately in a draw.
- If the last card from the `ocean` deck is drawn, the game ends immediately in a draw **without executing its effect**.

A draw also occurs when **all players starve (their rations reach 0) before reaching the top row of the board (row 5)**.

When a draw occurs, the board should be printed one final time (if the print is active) and the following message should be printed:

```
\n
Beaten by the whims of the sea, the game ends in a draw... Better luck next time.\n
```

After printing the message, the program must release all resources and terminate with a return value of `0`.

> **Note:** For example, if a deck has only one card remaining and a player is required to draw this card, the game ends in a draw immediately after this last available card is drawn from the deck.

</details>

## Return Values and Error Messages

The program has to react to errors during its runtime and print the corresponding error messages and/or return the
correct return values. You can find all error messages that should be printed and all return values in the table below.

Only one error should be printed at once. If multiple errors occur at the same time,
only the highest message in the below table should be printed.

`<UNICODE_CROSS>` stands for the symbol `❌` or the raw UTF-8 byte sequence `\xE2\x9D\x8C`. A constant for this can be found in the `Utils.hpp` file.

| Return Value | Error Message                                            | Meaning                                                                              | Program Phase                            |
|--------------|----------------------------------------------------------|--------------------------------------------------------------------------------------|------------------------------------------|
| `0`          | -                                                        | The program terminated successfully.                                                 | -                                        |
| `1`          | `[<UNICODE_CROSS>] Wrong number of arguments!\n`                  | The wrong number of command line arguments was entered.                             | Starting the Game                        |
| `2`          | `[<UNICODE_CROSS>] Invalid number of players!\n`                   | The number of players is invalid (not in range 2-5, both inclusive).                 | Starting the Game                        |
| `3`          | `[<UNICODE_CROSS>] Invalid file!\n`                                | The configuration file could not be opened or does not start with the correct magic number. | Starting the Game                        |
| -            | `[<UNICODE_CROSS>] Entered command not found!\n`                   | The entered command was not found.                                                   | All Commands                             |
| -            | `[<UNICODE_CROSS>] Wrong number of parameters for this command!\n` | The wrong number of parameters was entered for the given command.                 | All Commands                             |
| -            | `[<UNICODE_CROSS>] Invalid card deck type!\n`                      | The entered card deck type was neither `action` nor `ocean`.                         | Command `deck`                           |
| -            | `[<UNICODE_CROSS>] Action card does not exist!\n`                      | The given `<ACTION_NAME>` does not exist.                          | Command `action`                           |
| -            | `[<UNICODE_CROSS>] Action card not found in hand cards!\n`                      | A valid `<ACTION_NAME>` card is not part of the player's hand cards.                          | Command `action`                           |
| -            | `[<UNICODE_CROSS>] Player ID is out of range!\n`                      | The given player ID is out of range of all players.                          | Command `action`                           |
| -            | `[<UNICODE_CROSS>] You cannot target yourself!\n`                      | The given player ID is equal to the ID of the current player.                          | Command `action`                           |
| -            | `[<UNICODE_CROSS>] Targeted player has starved!\n`                      | The given player is not part of the game anymore since their rations reached 0.                          | Command `action`                           |
| -            | `[<UNICODE_CROSS>] Targeted player has no hand cards to target!\n`                      | The targeted player's hand cards are empty.                          | Command `action` - action cards that **target a player's card**                          |
| -            | `[<UNICODE_CROSS>] Card index is out of range for the targeted player!\n`                      | The given card index is out of range for the targeted player.                          | Command `action` - action cards that **target a player's card**                           |
| -            | `[<UNICODE_CROSS>] Insufficient amount of rations!\n`                      | The `swim` command was called when the current player had fewer than 2 rations available.                          | Command `swim`                           |

## Example Outputs

<details>
<summary><h3>Example Output 1</h3></summary>

The following example output was created using `./a1 2 configs/example_config.txt` to start the program.
```
Welcome to Only One Prevailing!

 5 |   |   |
 4 |   |   |
 3 |   |   |
 2 |   |   |
 1 |P01|P02|
     1   2  
    012 012 rations

P1 > hand
Hand cards:
- PIRAT - Pirate - SOUTH
- MSSGE - Message in a Bottle - NORTH
- LOSTS - Lost at Sea - WEST
- LOSTS - Lost at Sea - WEST
P1 > deck ocean
Cards of the ocean deck:
- Calm Waters - NO SHARK
- Ocean Debris - NO SHARK
- Island Calling - NO SHARK
- Kraken - NO SHARK
- Calm Waters - SHARK
- Ocean Debris - NO SHARK
- Island Calling - SHARK
- Kraken - NO SHARK
- Calm Waters - NO SHARK
- Ocean Debris - NO SHARK
P1 > deck action
Cards of the action deck:
- Message in a Bottle - NORTH
- Pirate - SOUTH
- Rogue Wave - EAST
P1 > float
Player 1 floats in place.

 5 |   |   |
 4 |   |   |
 3 |   |   |
 2 |   |   |
 1 |P01|P02|
     1   2  
    011 012 rations

P2 > hand
Hand cards:
- RWAVE - Rogue Wave - EAST
- PIRAT - Pirate - SOUTH
- MSSGE - Message in a Bottle - NORTH
- RWAVE - Rogue Wave - EAST
P2 > action pirat 1
Select target hand card:
P2 > 2
[🔥] Played Pirate - Stole another player's hand card!
P2 > hand
Hand cards:
- RWAVE - Rogue Wave - EAST
- MSSGE - Message in a Bottle - NORTH
- RWAVE - Rogue Wave - EAST
- MSSGE - Message in a Bottle - NORTH
P2 > action mssge 1
[🔥] Played Message in a Bottle - Stole up to 2 rations!
P2 > swim
Player 2 swims closer to safety.
[🌊] Drew Ocean Debris - Gained a new action card!

 5 |   |   |
 4 |   |   |
 3 |   |   |
 2 |   |P02|
 1 |P01| D |
     1   2  
    009 012 rations

P1 > swim
Player 1 swims closer to safety.
[🌊] Drew Calm Waters - The sea is calm, nothing happened.

 5 |   |   |
 4 |   |   |
 3 |   |   |
 2 |P01|P02|
 1 | W | D |
     1   2  
    007 012 rations


 5 |   |   |
 4 |   |   |
 3 |   |   |
 2 |P01|P02|
 1 | W | D |
     1   2  
    007 012 rations


Beaten by the whims of the sea, the game ends in a draw... Better luck next time.
```

</details>

<details>
<summary><h3>Example Output 2</h3></summary>

The following example output was created using `./a1 3 configs/game_config.txt` to start the program.

```
Welcome to Only One Prevailing!

 5 |   |   |   |
 4 |   |   |   |
 3 |   |   |   |
 2 |   |   |   |
 1 |P01|P02|P03|
     1   2   3  
    012 012 012 rations

P1 > hand
Hand cards:
- LOSTS - Lost at Sea - NORTH
- RWAVE - Rogue Wave - EAST
- PIRAT - Pirate - SOUTH
- RWAVE - Rogue Wave - EAST
P1 > action losts 3
Select target hand card:
P1 > 1
[🔥] Played Lost at Sea - Discarded another player's hand card!
P1 > swim
Player 1 swims closer to safety.
[🌊] Drew Kraken - Lost a ration to the Kraken!

 5 |   |   |   |
 4 |   |   |   |
 3 |   |   |   |
 2 |P01|   |   |
 1 | K |P02|P03|
     1   2   3  
    009 012 012 rations

P2 > hand
Hand cards:
- MSSGE - Message in a Bottle - NORTH
- LOSTS - Lost at Sea - NORTH
- RWAVE - Rogue Wave - EAST
- PIRAT - Pirate - SOUTH
P2 > action mssge 1
[🔥] Played Message in a Bottle - Stole up to 2 rations!
P2 > float
Player 2 floats in place.

 5 |   |   |   |
 4 |   |   |   |
 3 |   |   |   |
 2 |P01|   |   |
 1 | K |P02|P03|
     1   2   3  
    007 013 012 rations

P3 > hand
Hand cards:
- MSSGE - Message in a Bottle - NORTH
- LOSTS - Lost at Sea - NORTH
- MSSGE - Message in a Bottle - NORTH
P3 > action losts 2
Select target hand card:
P3 > 1
[🔥] Played Lost at Sea - Discarded another player's hand card!
P3 > action mssge 1
[🔥] Played Message in a Bottle - Stole up to 2 rations!
P3 > float
Player 3 floats in place.

 5 |   |   |   |
 4 |   |   |   |
 3 |   |   |   |
 2 |P01|   |   |
 1 | K |P02|P03|
     1   2   3  
    005 013 013 rations

P1 > hand
Hand cards:
- RWAVE - Rogue Wave - EAST
- PIRAT - Pirate - SOUTH
- RWAVE - Rogue Wave - EAST
- LOSTS - Lost at Sea - NORTH
P1 > swim
Player 1 swims closer to safety.
[🌊] Drew Island Calling - Moved forward and back again due to the island's calling!
[🦈] The shark smells food and approaches the players...

 5 |   |   |   |
 4 |   |   |   |
 3 |   |   |   |
 2 |P01|   |   |
 1 |🦈 |P02|P03|
     1   2   3  
    003 013 013 rations

P2 > hand
Hand cards:
- RWAVE - Rogue Wave - EAST
- PIRAT - Pirate - SOUTH
- RWAVE - Rogue Wave - EAST
P2 > swim
Player 2 swims closer to safety.
[🌊] Drew Ocean Debris - Gained a new action card!

 5 |   |   |   |
 4 |   |   |   |
 3 |   |   |   |
 2 |P01|P02|   |
 1 |🦈 | D |P03|
     1   2   3  
    003 011 013 rations

P3 > swim
Player 3 swims closer to safety.
[🌊] Drew Calm Waters - The sea is calm, nothing happened.
[🦈] Oh no, the shark is looking for food!
Select target hand card:
P1 > 4
Select target hand card:
P2 > 1
Select target hand card:
P3 > 1
[🦈] The shark will move along the path [ N E N ] swiftly!
[🦈] Yum, the shark was given a ration to eat!
[🦈] Yum, the shark was given a ration to eat!

 5 |   |   |   |
 4 |   |   |   |
 3 |   |🦈 |   |
 2 |P01|P02|P03|
 1 | K | D | W |
     1   2   3  
    002 010 011 rations

P1 > swim
Player 1 swims closer to safety.
[🌊] Drew Kraken - Lost a ration to the Kraken!
Oh no, Player 1 has starved!

 5 |   |   |   |
 4 |   |   |   |
 3 |   |🦈 |   |
 2 | K |P02|P03|
 1 | K | D | W |
     1   2   3  
    000 010 011 rations

P2 > swim
Player 2 swims closer to safety.
[🌊] Drew Island Calling - Moved forward and back again due to the island's calling!
[🦈] Oh no, the shark is looking for food!
Select target hand card:
P2 > 2
Select target hand card:
P3 > 1
[🦈] The shark will move along the path [ E S ] swiftly!
[🦈] Yum, the shark was given a ration to eat!

 5 |   |   |   |
 4 |   |   |   |
 3 |   |   |   |
 2 | K |P02|🦈 |
 1 | K | D | W |
     1   2   3  
    000 008 010 rations

P3 > float
Player 3 floats in place.

 5 |   |   |   |
 4 |   |   |   |
 3 |   |   |   |
 2 | K |P02|🦈 |
 1 | K | D | W |
     1   2   3  
    000 008 009 rations

P2 > swim
Player 2 swims closer to safety.
[🌊] Drew Ocean Debris - Gained a new action card!

 5 |   |   |   |
 4 |   |   |   |
 3 |   |P02|   |
 2 | K | D |🦈 |
 1 | K | D | W |
     1   2   3  
    000 006 009 rations

P3 > float
Player 3 floats in place.

 5 |   |   |   |
 4 |   |   |   |
 3 |   |P02|   |
 2 | K | D |🦈 |
 1 | K | D | W |
     1   2   3  
    000 006 008 rations

P2 > swim
Player 2 swims closer to safety.
[🌊] Drew Calm Waters - The sea is calm, nothing happened.
[🦈] Oh no, the shark is looking for food!
Select target hand card:
P2 > 1
Select target hand card:
P3 > 1
[🦈] The shark will move along the path [ S E ] swiftly!

 5 |   |   |   |
 4 |   |P02|   |
 3 |   | W |   |
 2 | K | D |P03|
 1 | K | D |🦈 |
     1   2   3  
    000 004 008 rations

P3 > float
Player 3 floats in place.

 5 |   |   |   |
 4 |   |P02|   |
 3 |   | W |   |
 2 | K | D |P03|
 1 | K | D |🦈 |
     1   2   3  
    000 004 007 rations

P2 > swim
Player 2 swims closer to safety.

 5 |   |P02|   |
 4 |   |   |   |
 3 |   | W |   |
 2 | K | D |P03|
 1 | K | D |🦈 |
     1   2   3  
    000 004 007 rations


Congratulations player 2, you are the Only One Prevailing!
```

</details>
