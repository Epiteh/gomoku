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

#include "Minimax.hpp"
#include <ctime>

Minimax::Minimax(Game &game)
    : _game(game)
{
    m_curTime = time(nullptr);
    best_v = 0;
}

auto Minimax::run(int *board, int depth, bool is_max) -> bool
{
    int size = (int)(_game.getSize());
    int tile = 0;

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            tile = _game.getBoard()[y * size + x];
        }
    }
    return (true);
}

auto Minimax::get_best_move(int *board) -> int
{
    return 0;
}

auto Minimax::get_best_score(int *board) -> int
{
    return 0;
}

auto Minimax::alpha_beta(
    int *board,
    int depth,
    int alpha,
    int beta,
    bool is_max
) -> int
{
    return 0;
}
