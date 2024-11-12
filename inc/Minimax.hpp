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

#include "Game.hpp"

class Minimax
{
public:
    Minimax(Game &game);
    ~Minimax() = default;

    auto run(int *board, int depth, bool is_max) -> bool;

    auto get_best_move(int *board) -> int;
    auto get_best_score(int *board) -> int;

    auto alpha_beta(
        int *board,
        int depth,
        int alpha,
        int beta,
        bool is_max
    ) -> int;

private:
    int m_curTime;
    int best_v;

    Game &_game;
};
