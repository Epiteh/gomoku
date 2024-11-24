/*

           d8b
           ?88
            88b
  88bd88b   888888b  d8888b
  88P' ?8b  88P `?8bd8P' `P
d88   88P d88,  d8888b
d88'   88bd88'`?88P'`?888P'

Author: hodos, 12/11/2024,
nbc signature powered by love.

*/

#pragma once

#include <chrono>
#include <vector>
#include <iostream>
#include <climits>
#include "Game.hpp"

/// @class Minimax
/// @brief Implements the Minimax algorithm for the Gomoku game.
/// This class provides methods to evaluate the game board
/// and determine the best move using the Minimax algorithm
/// with alpha-beta pruning.
class Minimax
{
public:
    const int VOID = 0;
    const int MAX_PLAYER = 1;
    const int MIN_PLAYER = -1;
    const int DEPTH = 1;
    const int INF = INT_MAX;

    /// @brief Constructs a Minimax object.
    /// @param board Pointer to the game board.
    /// @param size Size of the game board.
    Minimax(int *board, unsigned int size);

    /// @brief Destructor for the Minimax object.
    ~Minimax() = default;

    /// @brief Gets the best move for the current player.
    /// @return The best move as a br_move_t structure.
    auto get_best_move() -> br_move_t;

    /// @brief Implements the Minimax
    /// algorithm with alpha-beta pruning.
    /// @param depth Current depth in the game tree.
    /// @param alpha Alpha value for alpha-beta pruning.
    /// @param beta Beta value for alpha-beta pruning.
    /// @param isMax Boolean indicating if the current
    /// move is for the maximizing player.
    /// @return The evaluation score of the board.
    int minimax(int depth, int alpha, int beta, bool isMax);

private:
    /// @brief Evaluates the current state of the game board.
    /// @return The evaluation score of the board.
    int evaluate();

    /// @brief Checks if there are any moves left on the board.
    /// @return True if there are moves left, false otherwise.
    bool isMovesLeft();

    /// @brief Evaluates a line on the game board.
    /// @param sum The sum of the line to be evaluated.
    /// @return The evaluation score of the line.
    int evaluateLine(int sum);

    /// @brief Checks if a given index is
    /// within the scope of the board.
    /// @param index The index to be checked.
    /// @return True if the index is
    /// within scope, false otherwise.
    bool isInScope(int index);

    int *_board;
    unsigned int _size;

    std::chrono::time_point<std::chrono::steady_clock> _start;
};
