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

#include <ctime>
#include <algorithm>
#include "Minimax.hpp"

Minimax::Minimax(int *board, unsigned int size)
    : _board(board), _size(size)
{
    this->_curTime = time(nullptr);
    this->_best_v = 0;
}

auto Minimax::run(int *board, int depth, bool is_max) -> bool
{
    int size = (int)(this->_size);
    int tile = 0;

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            tile = this->_board[y * size + x];

            if (tile == Minimax::VOID) {
                this->_board[y * size + x] = is_max
                    ? Minimax::MAX_PLAYER
                    : Minimax::MIN_PLAYER;
                if (depth == 0) {
                    _best_v = std::max(_best_v, _evaluate(board));
                } else {
                    run(board, (depth - 1), !is_max);
                }
                this->_board[y * size + x] = Minimax::VOID;
            }
        }
    }
    return (true);
}

br_move_t Minimax::get_best_move(int *board)
{
    br_move_t best_move = {-1, -1};
    int best_value = -10000;
    int board_size = (int)(this->_size);
    int max_depth = 3;

    for (int y = 0; y < board_size; y++) {
        for (int x = 0; x < board_size; x++) {
            if (board[y * board_size + x] == VOID) {
                board[y * board_size + x] = MAX_PLAYER;
                int move_value = alpha_beta(
                    board, max_depth,
                    -10000, 10000, false
                );
                board[y * board_size + x] = VOID;

                if (move_value > best_value) {
                    best_move = {x, y};
                    best_value = move_value;
                }
            }
        }
    }
    return (best_move);
}

auto Minimax::_evaluate(int *board) -> int
{
    int size = (int)(this->_size);
    int score = 0;

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            int tile = board[y * size + x];

            if (tile == MAX_PLAYER) {
                score += 1;
            } else if (tile == MIN_PLAYER) {
                score -= 1;
            }
        }
    }
    return (score);
}

auto Minimax::alpha_beta(
    int *board,
    int depth,
    int alpha,
    int beta,
    bool is_max
) -> int
{
    int score = this->_evaluate(board);
    int board_size = (int)(this->_size);

    if (
        depth == 0
        || score == 1000
        || score == -1000
    ) {
        return (score);
    }

    if (is_max) {
        int max = -10000;

        for (int i = 0; i < board_size; i++) {
            if (board[i] == VOID) {
                board[i] = MAX_PLAYER;

                int eval = alpha_beta(
                    board, (depth - 1),
                    alpha, beta, false
                );

                board[i] = VOID;
                max = std::max(max, eval);
                alpha = std::max(alpha, eval);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return (max);
    } else {
        int min = 10000;

        for (int i = 0; i < board_size; i++) {
            if (board[i] == VOID) {
                board[i] = MIN_PLAYER;

                int eval = alpha_beta(
                    board, (depth - 1),
                    alpha, beta, true
                );

                board[i] = VOID;
                min = std::min(min, eval);
                beta = std::min(beta, eval);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return (min);
    }
}
