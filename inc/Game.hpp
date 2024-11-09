/*

           d8b
           ?88
            88b
  88bd88b   888888b  d8888b
  88P' ?8b  88P `?8bd8P' `P
d88   88P d88,  d8888b
d88'   88bd88'`?88P'`?888P'

Author: tilu, 05/11/2024,
nbc signature powered by love.

*/

#pragma once

/// @brief Move structure
/// @details This structure is used to represent a move
typedef struct br_move {
    int x;
    int y;
} br_move_t;

/// @brief Game class
/// @details This class is used to represent a game of gomoku
class Game {
public:
  Game();
  ~Game();

  /// @brief Set the size of the board
  /// @param size The size of the board
  void setSize(unsigned int size);

  /// @brief Get the size of the board
  /// @return The size of the board
  unsigned int getSize() const;


  /// @brief Play a move
  /// @return The move to play
  br_move_t playMove();

  /// @brief Get the board content
  /// @return The board
  int *getBoard();

  /// @brief Clear the board
  void clearBoard();


private:

    /// @brief Handle the victory move (from player 1 or player 2)
    /// @return The move to play
    br_move_t _victoryMove();

    /// @brief Get the victory move
    /// @param x The x position
    /// @param y The y position
    /// @param playerType The player type
    /// @return The move to play
    br_move_t _getVictoryMove(int x, int y, int playerType);

    unsigned int _size;
    int *_board;
};
