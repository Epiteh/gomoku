/*

           d8b
           ?88
            88b
  88bd88b   888888b  d8888b
  88P' ?8b  88P `?8bd8P' `P
d88   88P d88,  d8888b
d88'   88bd88'`?88P'`?888P'

Author: tilu, 22/09/2024,
nbc signature powered by love.

*/

#pragma once

/**
 * @mainpage Gomoku
 * # Gomoku
 *
 * ## How we implemented Minimax algorithm in Gomoku
 *
 * ### Minimax algorithm
 *
 * The Minimax algorithm is a decision rule used in artificial intelligence for minimizing the possible loss for a worst case scenario. It is used in two-player games, such as Gomoku, to determine the best move for a player, assuming that the opponent will also play optimally.
 *
 * ### Our implementation
 *
 * The implementation provided is a C++ class named Minimax that is designed to perform the Minimax algorithm with alpha-beta pruning for a board game. The Minimax algorithm is a decision-making algorithm used in two-player games to minimize the possible loss for a worst-case scenario. Here is a detailed explanation of the l
 *
 * #### Class Initialization
 * - The Minimax class is initialized with a pointer to the game board and the size of the board. The board is represented as a one-dimensional array, and the size is the length of one side of the square board.
 *
 * #### Checking for Available Moves
 * - The isMovesLeft method checks if there are any available moves left on the board. It iterates through the board and returns true if it finds any empty cell (represented by 0), otherwise returns false.
 *
 * #### Evaluating the Board
 * - The evaluate method calculates a score for the current state of the board. It checks all possible lines of five consecutive cells (rows, columns, and diagonals) and sums up their values. The evaluateLine method is used to assign scores to these lines based on the sum of their values:
 *  - A line with a sum of 5 (all cells occupied by the maximizing player) gets a high positive score.
 *  - A line with a sum of -5 (all cells occupied by the minimizing player) gets a high negative score.
 *  - Partial lines (with sums of 4, 3, 2, etc.) get progressively smaller scores.
 *
 * #### Minimax Algorithm with Alpha-Beta Pruning
 * - The minimax method implements the Minimax algorithm with alpha-beta pruning. It recursively evaluates the possible moves up to a certain depth:
 *  - If the depth is 0 or there are no moves left, it returns the evaluated score of the board.
 *  - If it is the maximizing player's turn, it tries to maximize the score by exploring all possible moves, updating the alpha value, and pruning branches where beta is less than or equal to alpha.
 *  - If it is the minimizing player's turn, it tries to minimize the score by exploring all possible moves, updating the beta value, and pruning branches where beta is less than or equal to alpha.
 *
 * #### Checking Move Scope
 * - The isInScope method checks if a move is within the scope of the current game state. It ensures that the move is adjacent to an already occupied cell, making the algorithm more efficient by focusing on relevant moves.
 *
 * #### Finding the Best Move
 * - The get_best_move method finds the best possible move for the maximizing player. It iterates through all possible moves, uses the minimax method to evaluate each move, and keeps track of the move with the highest score.
 *
 * This implementation efficiently evaluates the game board and determines the best move using the Minimax algorithm with alpha-beta pruning, ensuring optimal decision-making in a two-player game scenario.
 *
 * ### Conclusion
 *
 * #### Why we chose Minimax algorithm
 *
 * The Minimax algorithm is a widely used decision rule in two-player games due to its ability to minimize the possible loss for a worst-case scenario. By exploring all possible moves and their outcomes, the algorithm ensures that the player makes the best move based on the assumption that the opponent will also play optimally.
 *
 */
