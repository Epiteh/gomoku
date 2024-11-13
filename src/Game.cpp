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
    br_move_t vh_move = {-1, -1};
    br_move_t vb_move = {-1, -1};
    br_move_t hr_move = {-1, -1};
    br_move_t hl_move = {-1, -1};
    br_move_t ldr_move = {-1, -1};
    br_move_t ldl_move = {-1, -1};
    br_move_t rdr_move = {-1, -1};
    br_move_t rdl_move = {-1, -1};
    unsigned int vh_counter = 1;
    unsigned int vb_counter = 1;
    unsigned int hr_counter = 1;
    unsigned int hl_counter = 1;
    unsigned int leftr_diag_counter = 1;
    unsigned int leftl_diag_counter = 1;
    unsigned int rightr_diag_counter = 1;
    unsigned int rightl_diag_counter = 1;
    int size = (int)(this->_size);

    for (int i = 1; i < 5; i++) {
        if (x - i > 0) {
            if (this->_board[y * size + x - i] == playerType) {
                hl_counter ++;
            } else if (this->_board[y * size + x - i] == 0) {
                hl_move = {(x - i), y};
            }
        }
        if (x + i < size) {
            if (this->_board[y * size + x + i] == playerType) {
                hr_counter ++;
            } else if (this->_board[y * size + x + i] == 0) {
                hr_move = {(x + i), y};
            }
        }
        if (y - i > 0) {
            if (this->_board[(y - i) * size + x] == playerType) {
                vb_counter ++;
            } else if (this->_board[(y - i) * size + x] == 0) {
                vb_move = {x, (y - i)};
            }
        }
        if (y + i < size) {
            if (this->_board[(y + i) * size + x] == playerType) {
                vh_counter ++;
            } else if (this->_board[(y + i) * size + x] == 0) {
                vh_move = {x, (y + i)};
            }
        }
        if (x - i > 0 && y - i > 0) {
            if (this->_board[(y - i) * size + x - i] == playerType) {
                leftl_diag_counter ++;
            } else if (this->_board[(y - i) * size + x - i] == 0) {
                ldl_move = {(x - i), (y - i)};
            }
        }
        if (x + i < size && y + i < size) {
            if (this->_board[(y + i) * size + x + i] == playerType) {
                rightr_diag_counter ++;
            } else if (this->_board[(y + i) * size + x + i] == 0) {
                rdr_move = {(x + i), (y + i)};
            }
        }
        if (x - i > 0 && y + i < size) {
            if (this->_board[(y + i) * size + x - i] == playerType) {
                leftr_diag_counter ++;
            } else if (this->_board[(y + i) * size + x - i] == 0) {
                rdl_move = {(x - i), (y + i)};
            }
        }
        if (x + i < size && y - i > 0) {
            if (this->_board[(y - i) * size + x + i] == playerType) {
                rightl_diag_counter ++;
            } else if (this->_board[(y - i) * size + x + i] == 0) {
                ldr_move = {(x + i), (y - i)};
            }
        }
    }

    if (vh_counter >= 4) {
        return vh_move;
    } else if (vb_counter >= 4) {
        return vb_move;
    } else if (hr_counter >= 4) {
        return hr_move;
    } else if (hl_counter >= 4) {
        return hl_move;
    } else if (leftr_diag_counter >= 4) {
        return ldl_move;
    } else if (leftl_diag_counter >= 4) {
        return ldr_move;
    } else if (rightr_diag_counter >= 4) {
        return rdr_move;
    } else if (rightl_diag_counter >= 4) {
        return rdl_move;
    } else {
        return {-1, -1};
    }
}

br_move_t Game::_victoryMove()
{
    br_move_t move = {-1, -1};
    int size = (int)(this->_size);
    int tile;

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
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            tile = this->_board[y * size + x];
            if (tile == 2) {
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
    br_move_t move = {0, 0};
    br_move_t ob_move = this->_victoryMove();

    if (ob_move.x > -1) {
        return ob_move;
    }

    move = minimax.get_best_move(this->_board);

    // move.x = rand() % this->_size;
    // move.y = rand() % this->_size;

    // while (this->_board[move.y * this->_size + move.x] == 0) {
    //     move.x = rand() % this->_size;
    //     move.y = rand() % this->_size;
    // }
    return move;
}
