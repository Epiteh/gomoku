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
    for (unsigned int i = 0; i < _size * _size; ++i) {
        if (_board[i] == 0) {
            return true;
        }
    }
    return false;
}

int Minimax::evaluate() {
    int score = 0;

    for (unsigned int row = 0; row < _size; ++row) {
        for (unsigned int col = 0; col <= _size - 5; ++col) {
            int sum = 0;
            for (unsigned int k = 0; k < 5; ++k) {
                sum += _board[row * _size + col + k];
            }
            score += evaluateLine(sum);
        }
    }
    for (unsigned int col = 0; col < _size; ++col) {
        for (unsigned int row = 0; row <= _size - 5; ++row) {
            int sum = 0;
            for (unsigned int k = 0; k < 5; ++k) {
                sum += _board[(row + k) * _size + col];
            }
            score += evaluateLine(sum);
        }
    }
    for (unsigned int row = 0; row <= _size - 5; ++row) {
        for (unsigned int col = 0; col <= _size - 5; ++col) {
            int sum = 0;
            for (unsigned int k = 0; k < 5; ++k) {
                sum += _board[(row + k) * _size + col + k];
            }
            score += evaluateLine(sum);
        }
    }
    for (unsigned int row = 4; row < _size; ++row) {
        for (unsigned int col = 0; col <= _size - 5; ++col) {
            int sum = 0;
            for (unsigned int k = 0; k < 5; ++k) {
                sum += _board[(row - k) * _size + col + k];
            }
            score += evaluateLine(sum);
        }
    }
    return score;
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
    int score = evaluate();

    if (depth == 0  || score == 10000 || score == -10000|| !isMovesLeft()) {
        return score;
    }

    if (isMax) {
        int best = INT_MIN;

        for (unsigned int i = 0; i < _size * _size; ++i) {
            if (_board[i] == 0) {
                _board[i] = 1;
                best = std::max(best, minimax(depth + 1, alpha, beta, !isMax));
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
            if (_board[i] == 0) {
                _board[i] = -1;
                best = std::min(best, minimax(depth + 1, alpha, beta, !isMax));
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