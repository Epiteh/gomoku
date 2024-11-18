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

bool game_over(int *board, int size)
{
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            if (board[y * size + x] != 0) {
                if (
                    x <= size - 5
                    && board[y * size + x] == board[y * size + x + 1]
                    && board[y * size + x] == board[y * size + x + 2]
                    && board[y * size + x] == board[y * size + x + 3]
                    && board[y * size + x] == board[y * size + x + 4]
                ) {
                    return (true);
                }
                if (
                    y <= size - 5
                    && board[y * size + x] == board[(y + 1) * size + x]
                    && board[y * size + x] == board[(y + 2) * size + x]
                    && board[y * size + x] == board[(y + 3) * size + x]
                    && board[y * size + x] == board[(y + 4) * size + x]
                ) {
                    return (true);
                }
                if (
                    y <= size - 5 && x <= size - 5
                    && board[y * size + x] == board[(y + 1) * size + x + 1]
                    && board[y * size + x] == board[(y + 2) * size + x + 2]
                    && board[y * size + x] == board[(y + 3) * size + x + 3]
                    && board[y * size + x] == board[(y + 4) * size + x + 4]
                ) {
                    return (true);
                }
                if (
                    y >= 4 && x <= size - 5
                    && board[y * size + x] == board[(y - 1) * size + x + 1]
                    && board[y * size + x] == board[(y - 2) * size + x + 2]
                    && board[y * size + x] == board[(y - 3) * size + x + 3]
                    && board[y * size + x] == board[(y - 4) * size + x + 4]
                ) {
                    return (true);
                }
            }
        }
    }
    return (false);
}

Minimax::Minimax(int *board, unsigned int size)
    : _board(board), _size(size)
{
    this->_curTime = time(nullptr);
    this->_best_v = 0;
}

auto Minimax::get_best_move(int *board) -> br_move_t
{
    int size = (int)(this->_size);
    int value = -INF;
    br_move_t move = {-1, -1};

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i * size + j] == 0) {
                board[i * size + j] = -1;
                if (game_over(board, size)) {
                    board[i * size + j] = 0;
                    return {i, j};
                }
                board[i * size + j] = 0;
            }
        }
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i * size + j] == 0) {
                board[i * size + j] = 1;
                int move_value = alpha_beta(
                    board, 3,
                    -INF, INF, false
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

auto Minimax::check_pattern(
    int *board, int size,
    int row, int col,
    const std::vector<int>& pattern
) -> bool
{
    if (col <= size - (int)pattern.size()) {
        bool match = true;
        for (size_t k = 0; k < pattern.size(); k++) {
            if (board[row * size + col + k] != pattern[k]) {
                match = false;
                break;
            }
        }
        if (match) return (true);
    }

    if (row <= size - (int)pattern.size()) {
        bool match = true;
        for (size_t k = 0; k < pattern.size(); k++) {
            if (board[(row + k) * size + col] != pattern[k]) {
                match = false;
                break;
            }
        }
        if (match) return (true);
    }

    if (row <= size - (int)pattern.size() && col <= size - (int)pattern.size()) {
        bool match = true;
        for (size_t k = 0; k < pattern.size(); k++) {
            if (board[(row + k) * size + col + k] != pattern[k]) {
                match = false;
                break;
            }
        }
        if (match) return (true);
    }

    if (row >= (int)pattern.size() - 1 && col <= size - (int)pattern.size()) {
        bool match = true;
        for (size_t k = 0; k < pattern.size(); k++) {
            if (board[(row - k) * size + col + k] != pattern[k]) {
                match = false;
                break;
            }
        }
        if (match) return (true);
    }
    return (false);
}

int Minimax::_evaluate(int *board)
{
    int score = 0;
    int size = (int)(this->_size);

    const std::vector<std::pair<
        std::vector<int>, int>
    > patterns = {
        {{1, 1, 1, 0, 0}, 50},
        {{0, 1, 1, 1, 0}, 50},
        {{0, 0, 1, 1, 1}, 50},
        {{1, 1, 1, 1, 0}, 500},
        {{0, 1, 1, 1, 1}, 500},
        {{1, 1, 1, 1, 1}, 1000},
        {{1, 1, 1, 0}, 145},
        {{0, 1, 1, 1}, 145},
        {{0, 1, 1}, 25},
        {{1, 1, 0}, 25},
        {{-1, -1, -1, 0, 0}, 55},
        {{0, -1, -1, -1, 0}, 55},
        {{0, 0, -1, -1, -1}, 55},
        {{-1, -1, -1, -1, 0}, 500},
        {{0, -1, -1, -1, -1}, 500},
        {{-1, -1, -1, -1, -1}, 1000},
        {{-1, -1, -1, 0}, 150},
        {{0, -1, -1, -1}, 150}
    };

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i * size + j] == 1) {
                for (const auto& pattern : patterns) {
                    if (check_pattern(
                        board, size, i,
                        j, pattern.first
                    )) {
                        score += pattern.second;
                    }
                }
            } else if (board[i * size + j] == -1) {
                for (const auto& pattern : patterns) {
                    if (check_pattern(
                        board, size, i,
                        j, pattern.first
                    )) {
                        score -= pattern.second;
                    }
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
