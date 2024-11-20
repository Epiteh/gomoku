#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <chrono>

#include "Game.hpp"
#include "Minimax.hpp"

Minimax::Minimax(int *board, unsigned int size)
    : _board(board), _size(size) {}

int Minimax::_evaluate(int *board) {
    int score = 0;
    int size = (int)this->_size;

    for (int i = 0; i < size * size; i++) {
        if (board[i] == 1) {
            score += 10;
        } else if (board[i] == -1) {
            score -= 10;
        }
    }

    return score;
}

int Minimax::alpha_beta(int *board, int depth, int alpha, int beta, bool is_max) {
    std::chrono::time_point<std::chrono::steady_clock> end =
        std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<
        std::chrono::milliseconds
    >(end - this->_start).count();

    if (elapsed >= 1500) {
        return (-50);
    }
    int size = (int)this->_size;
    int score = this->_evaluate(board);
    if (depth == 0 || score == 1000 || score == -1000) {
        return score;
    }

    if (is_max) {
        int max_eval = -INF;
        for (int i = 0; i < size * size; i++) {
            if (board[i] == 0) {
                board[i] = 1;
                int eval = alpha_beta(board, depth - 1, alpha, beta, false);
                board[i] = 0;
                max_eval = std::max(max_eval, eval);
                alpha = std::max(alpha, eval);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return max_eval;
    } else {
        int min_eval = INF;
        for (int i = 0; i < size * size; i++) {
            if (board[i] == 0) {
                board[i] = -1;
                int eval = alpha_beta(board, depth - 1, alpha, beta, true);
                board[i] = 0;
                min_eval = std::min(min_eval, eval);
                beta = std::min(beta, eval);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return min_eval;
    }
}

std::vector<int> Minimax::generate_moves(int *board) {
    std::vector<int> moves;
    int size = (int)this->_size;

    for (int i = 0; i < size * size; i++) {
        if (board[i] == 0) {
            moves.push_back(i);
        }
    }

    return moves;
}

auto Minimax::get_best_move() -> br_move_t {
    br_move_t best_move = {-1, -1};
    int value = -INF;
    int size = (int)this->_size;
    int mapSize = size * size;

    this->_start = std::chrono::steady_clock::now();

    for (int i = 0; i < mapSize; i++) {
        if (this->_board[i] == 0) {
            this->_board[i] = 1;
            int move_value = alpha_beta(this->_board, DEPTH, -INF, INF, false);
            this->_board[i] = 0;

            if (move_value == -50) {
                return (best_move);
            }
            if (move_value > value) {
                value = move_value;
                best_move = {i % size, i / size};
            }
        }
    }

    return best_move;
}