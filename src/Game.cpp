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
#include "Minimax.hpp"
#include <stdlib.h>

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
    for (unsigned int i = 0; i < this->_size * this->_size; i++) {
        this->_board[i] = 0;
    }
}

void Game::setSize(unsigned int size)
{
    this->_size = size;
    if (this->_board != nullptr) {
        delete[] this->_board;
    }
    this->_board = new int[size * size];
    for (unsigned int i = 0; i < size * size; i++) {
        this->_board[i] = 0;
    }
}

unsigned int Game::getSize() const
{
    return this->_size;
}

br_move_t Game::_getVictoryMove(int x, int y, int playerType)
{
    br_move_t moves[8] = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1},
        {-1, -1}, {-1, -1}, {-1, -1}};
    unsigned int counters[8] = {1, 1, 1, 1, 1, 1, 1, 1};
    int size = (int)(this->_size);
    int *board = this->_board;

    for (int i = 1; i < 5; i++) {
        if (x - i >= 0) {
            if (board[y * size + x - i] == playerType) {
                counters[0]++;
            } else if (board[y * size + x - i] == 0) {
                moves[0] = {x - i, y};
            }
        }
        if (x + i < size) {
            if (board[y * size + x + i] == playerType) {
                counters[1]++;
            } else if (board[y * size + x + i] == 0) {
                moves[1] = {x + i, y};
            }
        }
        if (y - i >= 0) {
            if (board[(y - i) * size + x] == playerType) {
                counters[2]++;
            } else if (board[(y - i) * size + x] == 0) {
                moves[2] = {x, y - i};
            }
        }
        if (y + i < size) {
            if (board[(y + i) * size + x] == playerType) {
                counters[3]++;
            } else if (board[(y + i) * size + x] == 0) {
                moves[3] = {x, y + i};
            }
        }
        if (x - i >= 0 && y - i >= 0) {
            if (board[(y - i) * size + x - i] == playerType) {
                counters[4]++;
            } else if (board[(y - i) * size + x - i] == 0) {
                moves[4] = {x - i, y - i};
            }
        }
        if (x + i < size && y + i < size) {
            if (board[(y + i) * size + x + i] == playerType) {
                counters[5]++;
            } else if (board[(y + i) * size + x + i] == 0) {
                moves[5] = {x + i, y + i};
            }
        }
        if (x - i >= 0 && y + i < size) {
            if (board[(y + i) * size + x - i] == playerType) {
                counters[6]++;
            } else if (board[(y + i) * size + x - i] == 0) {
                moves[6] = {x - i, y + i};
            }
        }
        if (x + i < size && y - i >= 0) {
            if (board[(y - i) * size + x + i] == playerType) {
                counters[7]++;
            } else if (board[(y - i) * size + x + i] == 0) {
                moves[7] = {x + i, y - i};
            }
        }
    }

    for (int i = 0; i < 8; i++) {
        if (counters[i] >= 4) {
            return moves[i];
        }
    }
    return {-1, -1};
}

br_move_t Game::victoryMove()
{
    br_move_t move = {-1, -1};
    int size = (int)(this->_size);
    int tile;

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            tile = this->_board[y * size + x];
            if (tile == -1) {
                move = this->_getVictoryMove(x, y, tile);
                if (move.x > -1) {
                    return move;
                }
            }
        }
    }
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            tile = this->_board[y * size + x];
            if (tile == 1) {
                move = this->_getVictoryMove(x, y, tile);
                if (move.x > -1) {
                    return move;
                }
            }
        }
    }
    return move;
}

br_move_t Game::playMove()
{
    Minimax minimax(this->_board, this->_size);
    std::pair<int, int> best_move;
    br_move_t move = {-1, -1};
    br_move_t ob_move = this->victoryMove();

    if (ob_move.x > -1) {
        this->_board[ob_move.y * this->_size + ob_move.x] = 1;
        return ob_move;
    }
    move = minimax.get_best_move(this->_board);
    if (move.x <= -1) {
        move.x = rand() % this->_size;
        move.y = rand() % this->_size;

        while (this->_board[move.y * this->_size + move.x] == 0) {
            move.x = rand() % this->_size;
            move.y = rand() % this->_size;
        }
    }
    this->_board[move.y * this->_size + move.x] = 1;

    return move;
}
