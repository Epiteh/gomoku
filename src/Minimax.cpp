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
#include <chrono>
#include <iostream>
#include <thread>
#include <future>
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
    br_move_t best_move = {-1, -1};
    int value = -INF;
    int size = (int)this->_size;
    int mapSize = size * size;

    this->_start = std::chrono::steady_clock::now();
    for (int index = 0; index < mapSize; index++) {
        int i = index / size;
        int j = index % size;

        if (this->_board[index] == 0) {
            this->_board[index] = MAX_PLAYER;

                int move_value = alpha_beta(
                    j - 4 < 0 ? 0 : j - 4,
                    j + 4 > size ? size : j + 4,
                    i - 4 < 0 ? 0 : i - 4,
                    i + 4 > size ? size : i + 4,
                    DEPTH, -INF, INF, false);

            this->_board[index] = VOID;
            if (move_value == -50) {
                return (best_move);
            }
            if (move_value > value) {
                best_move = {j, i};
                value = move_value;
            }
        }
    }
    return (best_move);
}

auto Minimax::check_pattern(
    int row, int col, const std::vector<int>& pattern
) -> bool
{
    int size = (int)this->_size;

    if (col <= size - (int)pattern.size()) {
        bool match = true;

        for (size_t k = 0; k < pattern.size(); k++) {
            if (
                this->_board[
                    row * size + col + k
                ] != pattern[k]
            ) {
                match = false;
                break;
            }
        }
        if (match) return (true);
    }

    if (row <= size - (int)pattern.size()) {
        bool match = true;

        for (size_t k = 0; k < pattern.size(); k++) {
            if (
                this->_board[
                    (row + k) * size + col
                ] != pattern[k]
            ) {
                match = false;
                break;
            }
        }
        if (match) return (true);
    }

    if (
        row <= size - (int)pattern.size()
        && col <= size - (int)pattern.size()
    ) {
        bool match = true;

        for (size_t k = 0; k < pattern.size(); k++) {
            if (
                this->_board[
                    (row + k) * size + col + k
                ] != pattern[k]) {
                match = false;
                break;
            }
        }
        if (match) return (true);
    }

    if (
        row >= (int)pattern.size() - 1
        && col <= size - (int)pattern.size()
    ) {
        bool match = true;

        for (size_t k = 0; k < pattern.size(); k++) {
            if (
                this->_board[
                    (row - k) * size + col + k
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
    int size = (int)this->_size;
    int boardSize = size * size;

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

    for (int index = 0; index < boardSize; index++) {
        int i = index / size;
        int j = index % size;

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
    int x_min,
    int x_max,
    int y_min,
    int y_max,

    int depth,
    int alpha,
    int beta,
    bool is_max
) -> int
{
    std::chrono::time_point<std::chrono::steady_clock> end =
        std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<
        std::chrono::milliseconds
    >(end - this->_start).count();

    if (elapsed >= 1500) {
        return (-50);
    }

    int score = this->_evaluate();
    int size = (int)this->_size;
    int boardSize = size * size;
    int y;
    int x;

    if (
        depth == 0
        || score == 1000
        || score == -1000
    ) {
        return (score);
    }

    if (is_max) {
        int max = -INF;

        for (int i = y_min * size + x_min; i < ((y_max * size) + x_max); i++) {
            y = i / size;
            x = i % size;

            if (y < y_min || y >= y_max) {
                continue;
            }
            if (x < x_min || x >= x_max) {
                continue;
            }
            if (this->_board[i] == VOID) {
                this->_board[i] = MAX_PLAYER;

                int eval = alpha_beta(
                    x - 4 < 0 ? 0 : x - 4,
                    x + 4 > size ? size : x + 4,
                    y - 4 < 0 ? 0 : y - 4,
                    y + 4 > size ? size : y + 4,
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

        for (int i = y_min * size + x_min; i < ((y_max * size) + x_max); i++) {
            y = i / size;
            x = i % size;

            if (y < y_min || y >= y_max) {
                continue;
            }
            if (x < x_min || x >= x_max) {
                continue;
            }
            if (this->_board[i] == VOID) {
                this->_board[i] = MIN_PLAYER;

                int eval = alpha_beta(
                    x - 4 < 0 ? 0 : x - 4,
                    x + 4 > size ? size : x + 4,
                    y - 4 < 0 ? 0 : y - 4,
                    y + 4 > size ? size : y + 4,
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
