/*

           d8b
           ?88
            88b
  88bd88b   888888b  d8888b
  88P' ?8b  88P `?8bd8P' `P
d88   88P d88,  d8888b
d88'   88bd88'`?88P'`?888P'

Author: tilu, 05/11/2024,
nbc signature powered by love.

*/

#include "Game.hpp"

Game::Game() {
    this->_board = nullptr;
    this->_size = 0;
}

Game::~Game()
{
    if (this->_board != nullptr) {
        delete[] this->_board;
    }
}

int *Game::getBoard()
{
    return this->_board;
}

void Game::clearBoard()
{
    if (this->_board != nullptr) {
        delete[] this->_board;
    }
    this->_board = new int[this->_size * this->_size];
}

void Game::setSize(unsigned int size)
{
    this->_size = size;
    if (this->_board != nullptr) {
        delete[] this->_board;
    }
    this->_board = new int[size * size];
}

unsigned int Game::getSize() const
{
    return this->_size;
}

br_move_t Game::handleObviousMove()
{
    br_move_t move = {-1, -1};

    // TODO: Implement the logic

    return move;
}

br_move_t Game::playMove()
{
    br_move_t move = {0, 0};
    br_move_t ob_move = handleObviousMove();

    if (ob_move.x > -1) {
        return ob_move;
    }

    // TODO: Implement the logic

    return move;
}
