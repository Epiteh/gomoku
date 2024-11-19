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
}

auto Minimax::get_best_move() -> br_move_t
{
    int value = -INF;
    br_move_t move = {-1, -1};

    for (
            int index = 0;
            index < (int)(this->_size) * (int)(this->_size);
            index++
        ) {
        int i = index / (int)(this->_size);
        int j = index % (int)(this->_size);

        if (this->_board[index] == 0) {
            this->_board[index] = MAX_PLAYER;

            int move_value = alpha_beta(DEPTH, -INF, INF, false);

            this->_board[index] = VOID;
            if (move_value > value) {
                move = {j, i};
                value = move_value;
            }
        }
    }
    return (move);
}

auto Minimax::check_pattern(
    int row, int col, const std::vector<int>& pattern
) -> bool
{
    if (col <= (int)(this->_size) - (int)pattern.size()) {
        bool match = true;

        for (size_t k = 0; k < pattern.size(); k++) {
            if (
                this->_board[
                    row * (int)(this->_size) + col + k
                ] != pattern[k]
            ) {
                match = false;
                break;
            }
        }
        if (match) return (true);
    }

    if (row <= (int)(this->_size) - (int)pattern.size()) {
        bool match = true;

        for (size_t k = 0; k < pattern.size(); k++) {
            if (
                this->_board[
                    (row + k) * (int)(this->_size) + col
                ] != pattern[k]
            ) {
                match = false;
                break;
            }
        }
        if (match) return (true);
    }

    if (
        row <= (int)(this->_size) - (int)pattern.size()
        && col <= (int)(this->_size) - (int)pattern.size()
    ) {
        bool match = true;

        for (size_t k = 0; k < pattern.size(); k++) {
            if (
                this->_board[
                    (row + k) * (int)(this->_size) + col + k
                ] != pattern[k]) {
                match = false;
                break;
            }
        }
        if (match) return (true);
    }

    if (
        row >= (int)pattern.size() - 1
        && col <= (int)(this->_size) - (int)pattern.size()
    ) {
        bool match = true;

        for (size_t k = 0; k < pattern.size(); k++) {
            if (
                this->_board[
                    (row - k) * (int)(this->_size) + col + k
                ] != pattern[k]) {
                match = false;
                break;
            }
        }
        if (match) return (true);
    }
    return (false);
}

int Minimax::_evaluate()
{
    int score = 0;

    const std::vector<std::pair<
        std::vector<int>, int>
    > patterns = {
        {{1, 1, 1, 0, 0}, 50},
        {{0, 1, 1, 1, 0}, 50},
        {{0, 0, 1, 1, 1}, 50},
        {{1, 1, 1, 1, 0}, 750},
        {{0, 1, 1, 1, 1}, 750},
        {{1, 1, 1, 1, 1}, 1000},
        {{1, 1, 1, 0}, 150},
        {{0, 1, 1, 1}, 150},
        {{0, 1, 1, 1}, 150},
        {{0, 1, 1, 0, 1}, 750},
        {{0, 1, 1}, 25},
        {{1, 1, 0}, 25},
        {{-1, -1, -1, 0, 0}, 50},
        {{0, -1, -1, -1, 0}, 50},
        {{0, 0, -1, -1, -1}, 50},
        {{-1, -1, -1, -1, 0}, 750},
        {{0, -1, -1, -1, -1}, 750},
        {{-1, -1, -1, -1, -1}, 1000},
        {{-1, -1, -1, 0}, 150},
        {{0, -1, -1, -1}, 150},
        {{0, -1, -1, -1, 0}, 150},
        {{-1, -1, 0, -1}, 750},
        {{0, -1, -1}, 25},
        {{-1, -1, 0}, 25}
    };

    for (
        int index = 0;
        index < (int)(this->_size) * (int)(this->_size);
        index++
    ) {
        int i = index / (int)(this->_size);
        int j = index % (int)(this->_size);

        if (this->_board[index] == 1) {
            for (const auto& pattern : patterns) {
                if (check_pattern(i, j, pattern.first)) {
                    score += pattern.second;
                }
            }
        } else if (this->_board[index] == -1) {
            for (const auto& pattern : patterns) {
                if (check_pattern(i, j, pattern.first)) {
                    score -= pattern.second;
                }
            }
        }
    }
    return (score);
}

auto Minimax::alpha_beta(
    int depth,
    int alpha,
    int beta,
    bool is_max
) -> int
{
    int score = this->_evaluate();

    if (
        depth == 0
        || score == 1000
        || score == -1000
    ) {
        return (score);
    }

    if (is_max) {
        int max = -INF;

        for (int i = 0; i < (int)(this->_size); i++) {
            if (this->_board[i] == VOID) {
                this->_board[i] = MAX_PLAYER;

                int eval = alpha_beta(
                    (depth - 1), alpha, beta, false
                );

                this->_board[i] = VOID;
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

        for (int i = 0; i < (int)(this->_size); i++) {
            if (this->_board[i] == VOID) {
                this->_board[i] = MIN_PLAYER;

                int eval = alpha_beta(
                    (depth - 1), alpha, beta, true
                );

                this->_board[i] = VOID;
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
