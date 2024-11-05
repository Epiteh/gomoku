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

#pragma once

typedef struct br_move {
    int x;
    int y;
} br_move_t;

class Game {
public:
  Game();
  ~Game();

  void setSize(unsigned int size);
  unsigned int getSize() const;

  br_move_t playMove();

  int *getBoard();

  void clearBoard();

private:
    unsigned int _size;
    int *_board;
};
