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

class Minimax
{
public:
    const int VOID = 0;
    const int MAX_PLAYER = 1;
    const int MIN_PLAYER = -1;
    const int DEPTH = 2;
    const int INF = INT_MAX;

    Minimax(int *board, unsigned int size);
    ~Minimax() = default;

    auto get_best_move() -> br_move_t;

    int _evaluate(int *board);
    int alpha_beta(int *board, int depth, int alpha, int beta, bool is_max);
    std::vector<int> generate_moves(int *board);

private:
    int *_board;
    unsigned int _size;

    std::chrono::time_point<std::chrono::steady_clock> _start;
};
