/*

           d8b
           ?88
            88b
  88bd88b   888888b  d8888b
  88P' ?8b  88P `?8bd8P' `P
d88   88P d88,  d8888b
d88'   88bd88'`?88P'`?888P'

Author: tilu, 13/11/2024,
nbc signature powered by love.

*/

#include <criterion/criterion.h>
#include "Game.hpp"
#include <iostream>


// BRAIN victory
Test(victoryMove, test_victoryMove_vectical)
{

    Game game;
    int *board;

    game.setSize(5);
    board = game.getBoard();
    board[0] = 1;
    board[5] = 1;
    board[15] = 1;
    board[20] = 1;

    br_move_t move = game.victoryMove();
    cr_assert_eq(move.x, 0);
    cr_assert_eq(move.y, 2);
}

Test(victoryMove, test_victoryMove_horizontal)
{

    Game game;
    int *board;

    game.setSize(5);
    board = game.getBoard();
    board[0] = 1;
    board[1] = 1;
    board[3] = 1;
    board[4] = 1;

    br_move_t move = game.victoryMove();
    cr_assert_eq(move.x, 2);
    cr_assert_eq(move.y, 0);
}

Test(victoryMove, test_victoryMove_left_diagonal)
{

    Game game;
    int *board;

    game.setSize(5);
    board = game.getBoard();
    board[0] = 1;
    board[6] = 1;
    board[18] = 1;
    board[24] = 1;

    br_move_t move = game.victoryMove();
    cr_assert_eq(move.x, 2);
    cr_assert_eq(move.y, 2);
}

Test(victoryMove, test_victoryMove_right_diagonal)
{

    Game game;
    int *board;

    game.setSize(5);
    board = game.getBoard();
    board[4] = 1;
    board[8] = 1;
    board[16] = 1;
    board[20] = 1;

    br_move_t move = game.victoryMove();
    cr_assert_eq(move.x, 2);
    cr_assert_eq(move.y, 2);
}


// Block player victory

Test(victoryMove, test_player_victoryMove_vectical)
{

    Game game;
    int *board;

    game.setSize(5);
    board = game.getBoard();
    board[0] = -1;
    board[5] = -1;
    board[15] = -1;
    board[20] = -1;

    br_move_t move = game.victoryMove();
    cr_assert_eq(move.x, 0);
    cr_assert_eq(move.y, 2);
}

Test(victoryMove, test_player_victoryMove_horizontal)
{

    Game game;
    int *board;

    game.setSize(5);
    board = game.getBoard();
    board[0] = -1;
    board[1] = -1;
    board[3] = -1;
    board[4] = -1;

    br_move_t move = game.victoryMove();
    cr_assert_eq(move.x, 2);
    cr_assert_eq(move.y, 0);
}

Test(victoryMove, test_player_victoryMove_left_diagonal)
{

    Game game;
    int *board;

    game.setSize(5);
    board = game.getBoard();
    board[0] = -1;
    board[6] = -1;
    board[18] = -1;
    board[24] = -1;

    br_move_t move = game.victoryMove();
    cr_assert_eq(move.x, 2);
    cr_assert_eq(move.y, 2);
}

Test(victoryMove, test_player_victoryMove_right_diagonal)
{

    Game game;
    int *board;

    game.setSize(5);
    board = game.getBoard();
    board[4] = -1;
    board[8] = -1;
    board[16] = -1;
    board[20] = -1;

    br_move_t move = game.victoryMove();
    cr_assert_eq(move.x, 2);
    cr_assert_eq(move.y, 2);
}

// Priorise victory move instead of blocking player

Test(victoryMove, test_victoryMove_vectical_over_block)
{

    Game game;
    int *board;

    game.setSize(5);
    board = game.getBoard();
    board[0] = 1;
    board[5] = 1;
    board[15] = 1;
    board[20] = 1;
    board[1] = -1;
    board[6] = -1;
    board[11] = -1;
    board[21] = -1;

    br_move_t move = game.victoryMove();
    cr_assert_eq(move.x, 0);
    cr_assert_eq(move.y, 2);
}

Test(victoryMove, test_victoryMove_vectical_tests_block)
{

    Game game;
    int *board;

    game.setSize(6);
    board = game.getBoard();
    board[5] = 1;
    board[7] = -1;
    board[10] = -1;
    board[12] = 1;
    board[13] = -1;
    board[14] = -1;
    board[15] = -1;
    board[16] = -1;
    board[17] = 1;
    board[19] = -1;
    board[20] = -1;
    board[21] = 1;
    board[25] = -1;
    board[30] = -1;

    br_move_t move = game.victoryMove();
    cr_assert_eq(move.x, 1);
    cr_assert_eq(move.y, 5);
}
