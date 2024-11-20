#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <chrono>

#include "Game.hpp"
#include "Minimax.hpp"

Minimax::Minimax(int *board, unsigned int size)
    : _board(board), _size(size) {}

bool Minimax::isMovesLeft() {
    int size = (int) _size;
    int boardSize = size * size;

    for (int i = 0; i < boardSize; ++i) {
        if (_board[i] == 0) {
            return true;
        }
    }
    return false;
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

int Minimax::evaluate()
{
    int score = 0;
    int size = (int)this->_size;
    int boardSize = size * size;
    int x;
    int y;

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
        y = index / size;
        x = index % size;

        if (this->_board[index] == 1) {
            for (const auto& pattern : patterns) {
                if (check_pattern(y, x, pattern.first)) {
                    score += pattern.second;
                }
            }
        } else if (this->_board[index] == -1) {
            for (const auto& pattern : patterns) {
                if (check_pattern(y, x, pattern.first)) {
                    score -= pattern.second;
                }
            }
        }
    }
    return (score);
}

int Minimax::evaluateLine(int sum) {
    switch (sum) {
        case 5:
            return 10000;
        case -5:
            return -10000;
        case 4:
            return 100;
        case -4:
            return -100;
        case 3:
            return 10;
        case -3:
            return -10;
        case 2:
            return 1;
        case -2:
            return -1;
        default:
            return 0;
    }
}

int Minimax::minimax(int depth, int alpha, int beta, bool isMax) {
    if (depth == 0 || !isMovesLeft()) {
        return evaluate();
    }

    if (isMax) {
        int best = INT_MIN;

        for (unsigned int i = 0; i < _size * _size; ++i) {
            if (_board[i] == 0 && checkNeighbours(i)) {
                _board[i] = 1;
                best = std::max(best, minimax(depth - 1, alpha, beta, !isMax));
                _board[i] = 0;
                alpha = std::max(alpha, best);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return best;
    } else {
        int best = INT_MAX;

        for (unsigned int i = 0; i < _size * _size; ++i) {
            if (_board[i] == 0 && checkNeighbours(i)) {
                _board[i] = -1;
                best = std::min(best, minimax(depth - 1, alpha, beta, !isMax));
                _board[i] = 0;
                beta = std::min(beta, best);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return best;
    }
}

bool Minimax::checkNeighbours(int index) {
    int size = (int) _size;
    int y = index / size;
    int x = index % size;

    if (x > 0 && _board[y * size + (x - 1)] != 0) {
        return true;
    }
    if (y > 0 && _board[(y - 1) * size + x] != 0) {
        return true;
    }
    if (x < size - 1 && _board[y * size + (x + 1)] != 0) {
        return true;
    }
    if (y < size - 1 && _board[(y + 1) * size + x] != 0) {
        return true;
    }
    if (x > 0 && y > 0 && _board[(y - 1) * size + (x - 1)] != 0) {
        return true;
    }
    if (x > 0 && y < size - 1 && _board[(y + 1) * size + (x - 1)] != 0) {
        return true;
    }
    if (x < size - 1 && y < size - 1 && _board[(y + 1) * size + (x + 1)] != 0) {
        return true;
    }
    if (x < size - 1 && y > 0 && _board[(y - 1) * size + (x + 1)] != 0) {
        return true;
    }
    return false;
}

auto Minimax::get_best_move() -> br_move_t {
    int bestVal = INT_MIN;
    br_move_t bestMove = {-1, -1};
    int size = (int) this->_size;
    int boardSize = size * size;

    for (int i = 0; i < boardSize; ++i) {
        if (_board[i] == 0) {
            _board[i] = 1;
            int moveVal = minimax(DEPTH, INT_MIN, INT_MAX, false);
            _board[i] = 0;
            if (moveVal > bestVal) {
                bestMove = {i / size, i % size};
                bestVal = moveVal;
            }
        }
    }
    return bestMove;
}