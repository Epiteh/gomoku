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
#include <limits.h>
#include <algorithm>
#include "Game.hpp"
#include "Minimax.hpp"

const int INF = INT_MAX;

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

            if (tile = Minimax::VOID) {
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

auto Minimax::get_best_move(int *board) -> br_move_t
{
    int size = (int)(this->_size);
    int value = -INF;
    br_move_t move = {-1, -1};

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i * size + j] == 0) {
                board[i * size + j] = 1;
                int move_value = alpha_beta(
                    board, 3, -INF, INF, false
                );
                board[i * size + j] = 0;

                if (move_value > value) {
                    move = {i, j};
                    value = move_value;
                }
            }
        }
    }
    return (move);
}

auto Minimax::_evaluate(int *board) -> int
{
    int score = 0;
    int size = (int)(this->_size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i * size + j] == 1) {
                if (
                    j <= size - 3
                    && board[i * size + j] == board[i * size + j + 1]
                    && board[i * size + j] == board[i * size + j + 2]
                ) {
                    score += 10;
                }
                if (
                    j <= size - 4
                    && board[i * size + j] == board[i * size + j + 1]
                    && board[i * size + j] == board[i * size + j + 2]
                    && board[i * size + j] == board[i * size + j + 3]
                ) {
                    score += 100;
                }
                if (
                    j <= size - 5
                    && board[i * size + j] == board[i * size + j + 1]
                    && board[i * size + j] == board[i * size + j + 2]
                    && board[i * size + j] == board[i * size + j + 3]
                    && board[i * size + j] == board[i * size + j + 4]
                ) {
                    score += 1000;
                }

                if (
                    i <= size - 3
                    && board[i * size + j] == board[(i + 1) * size + j]
                    && board[i * size + j] == board[(i + 2) * size + j]
                ) {
                    score += 10;
                }
                if (
                    i <= size - 4
                    && board[i * size + j] == board[(i + 1) * size + j]
                    && board[i * size + j] == board[(i + 2) * size + j]
                    && board[i * size + j] == board[(i + 3) * size + j]
                ) {
                    score += 100;
                }
                if (
                    i <= size - 5
                    && board[i * size + j] == board[(i + 1) * size + j]
                    && board[i * size + j] == board[(i + 2) * size + j]
                    && board[i * size + j] == board[(i + 3) * size + j]
                    && board[i * size + j] == board[(i + 4) * size + j]
                ) {
                    score += 1000;
                }

                if (
                    i <= size - 3 && j <= size - 3
                    && board[i * size + j] == board[(i + 1) * size + j + 1]
                    && board[i * size + j] == board[(i + 2) * size + j + 2]
                ) {
                    score += 10;
                }
                if (
                    i <= size - 4 && j <= size - 4
                    && board[i * size + j] == board[(i + 1) * size + j + 1]
                    && board[i * size + j] == board[(i + 2) * size + j + 2]
                    && board[i * size + j] == board[(i + 3) * size + j + 3]
                ) {
                    score += 100;
                }
                if (
                    i <= size - 5 && j <= size - 5
                    && board[i * size + j] == board[(i + 1) * size + j + 1]
                    && board[i * size + j] == board[(i + 2) * size + j + 2]
                    && board[i * size + j] == board[(i + 3) * size + j + 3]
                    && board[i * size + j] == board[(i + 4) * size + j + 4]
                ) {
                    score += 1000;
                }
            } else if (board[i * size + j] == -1) {
                if (
                    j <= size - 3
                    && board[i * size + j] == board[i * size + j + 1]
                    && board[i * size + j] == board[i * size + j + 2]
                ) {
                    score -= 10;
                }
                if (
                    j <= size - 4
                    && board[i * size + j] == board[i * size + j + 1]
                    && board[i * size + j] == board[i * size + j + 2]
                    && board[i * size + j] == board[i * size + j + 3]
                ) {
                    score -= 100;
                }
                if (
                    j <= size - 5
                    && board[i * size + j] == board[i * size + j + 1]
                    && board[i * size + j] == board[i * size + j + 2]
                    && board[i * size + j] == board[i * size + j + 3]
                    && board[i * size + j] == board[i * size + j + 4]
                ) {
                    score -= 1000;
                }

                if (
                    i <= size - 3
                    && board[i * size + j] == board[(i + 1) * size + j]
                    && board[i * size + j] == board[(i + 2) * size + j]
                ) {
                    score -= 10;
                }
                if (
                    i <= size - 4
                    && board[i * size + j] == board[(i + 1) * size + j]
                    && board[i * size + j] == board[(i + 2) * size + j]
                    && board[i * size + j] == board[(i + 3) * size + j]
                ) {
                    score -= 100;
                }
                if (
                    i <= size - 5
                    && board[i * size + j] == board[(i + 1) * size + j]
                    && board[i * size + j] == board[(i + 2) * size + j]
                    && board[i * size + j] == board[(i + 3) * size + j]
                    && board[i * size + j] == board[(i + 4) * size + j]
                ) {
                    score -= 1000;
                }

                if (
                    i <= size - 3 && j <= size - 3
                    && board[i * size + j] == board[(i + 1) * size + j + 1]
                    && board[i * size + j] == board[(i + 2) * size + j + 2]
                ) {
                    score -= 10;
                }
                if (
                    i <= size - 4 && j <= size - 4
                    && board[i * size + j] == board[(i + 1) * size + j + 1]
                    && board[i * size + j] == board[(i + 2) * size + j + 2]
                    && board[i * size + j] == board[(i + 3) * size + j + 3]
                ) {
                    score -= 100;
                }
                if (
                    i <= size - 5 && j <= size - 5
                    && board[i * size + j] == board[(i + 1) * size + j + 1]
                    && board[i * size + j] == board[(i + 2) * size + j + 2]
                    && board[i * size + j] == board[(i + 3) * size + j + 3]
                    && board[i * size + j] == board[(i + 4) * size + j + 4]
                ) {
                    score -= 1000;
                }

                if (
                    i >= 2 && j <= size - 3
                    && board[i * size + j] == board[(i - 1) * size + j + 1]
                    && board[i * size + j] == board[(i - 2) * size + j + 2]
                ) {
                    score -= 10;
                }
                if (
                    i >= 3 && j <= size - 4
                    && board[i * size + j] == board[(i - 1) * size + j + 1]
                    && board[i * size + j] == board[(i - 2) * size + j + 2]
                    && board[i * size + j] == board[(i - 3) * size + j + 3]
                ) {
                    score -= 100;
                }
                if (
                    i >= 4 && j <= size - 5
                    && board[i * size + j] == board[(i - 1) * size + j + 1]
                    && board[i * size + j] == board[(i - 2) * size + j + 2]
                    && board[i * size + j] == board[(i - 3) * size + j + 3]
                    && board[i * size + j] == board[(i - 4) * size + j + 4]
                ) {
                    score -= 1000;
                }
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
    int size = (int)(this->_size);
    int score = this->_evaluate(board);

    if (
        depth == 0
        || score == 1000
        || score == -1000
    ) {
        return (score);
    }

    if (is_max) {
        int max = -INF;

        for (int i = 0; i < size; i++) {
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
        int min = INF;

        for (int i = 0; i < size; i++) {
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
