/*

           d8b
           ?88
            88b
  88bd88b   888888b  d8888b
  88P' ?8b  88P `?8bd8P' `P
d88   88P d88,  d8888b
d88'   88bd88'`?88P'`?888P'

Author: hodos, 28/10/2024,
nbc signature powered by love.

*/

#include "ControlTow.hpp"

ControlTow::ControlTow(Game &game) : _game(game)
{
}

void ControlTow::handle_about([[maybe_unused]] std::string &cmd)
{
    constexpr std::string_view bot_name = "cpp_template";

    std::cout << "name=\"" << bot_name
        << "\", version=\"0.42\"" << std::endl;
}

void ControlTow::handle_start(std::string &cmd)
{
    std::vector<std::string> params = this->getCmdParams(cmd);
    unsigned long size;

    try {
        if (this->_game.getSize() > 0)
            throw std::invalid_argument("game already started");
        if (params.size() != 1)
            throw std::invalid_argument("invalid number of arguments");
        size = std::stoul(params[0]);
        if (size < 5 || size > 20) {
            throw std::invalid_argument("unsupported size");
        }
        this->_game.setSize(size);
    } catch (std::invalid_argument const& ex) {
        std::cout << "ERROR " << ex.what() << "\r" << std::endl;
        return;
    }
    std::cout << "OK\r" << std::endl;
}

void ControlTow::handle_end([[maybe_unused]] std::string &cmd)
{
    try {
        if (this->_game.getSize() <= 0) {
            throw std::invalid_argument("game not started");
        }
        this->SHOULD_STOP = true;
    } catch (std::invalid_argument const& ex) {
        std::cout << "ERROR " << ex.what() << "\r" << std::endl;
        return;
    }
}

void ControlTow::handle_info(std::string &cmd)
{
    (void) cmd;
    /// @todo Handle info
}

void ControlTow::handle_turn(std::string &cmd)
{
    std::vector<std::string> params = this->getCmdParams(cmd);
    unsigned long size = this->_game.getSize();

    try {
        if (size <= 0)
            throw std::invalid_argument("game not starte");
        if (params.size() != 2)
            throw std::invalid_argument("invalid number of arguments");

        unsigned int x = std::stoul(params[0]);
        unsigned int y = std::stoul(params[1]);

        int *board = this->_game.getBoard();
        board[x * size + y] = 2;

        if ((x > size) || (y > size)) {
            throw std::invalid_argument("invalid position");
        }
        br_move_t move = this->_game.playMove();

        std::cout << move.x << "," << move.y << "\r" << std::endl;
        return;
    } catch (std::invalid_argument const& ex) {
        std::cout << "ERROR " << ex.what() << "\r" << std::endl;
        return;
    }
}

void ControlTow::handle_board(std::string &cmd)
{
    int *board = this->_game.getBoard();
    unsigned int size = this->_game.getSize();
    std::vector<std::string> params;
    std::string line;
    unsigned int value;
    unsigned int x;
    unsigned int y;

    try {
        this->_game.clearBoard();
        for (line; std::getline(std::cin, line);) {
            if (line == "DONE") {
                break;
            }
            line = "BOARD " + line;
            params = this->getCmdParams(line);
            if (params.size() != 3) {
                throw std::invalid_argument("invalid number of arguments");
                return;
            }
            value = std::stoul(params[2]);
            if (value != 0 && value != 1 && value != 2 && value != 3) {
                throw std::invalid_argument("invalid value");
                return;
            }
            x = std::stoul(params[0]);
            y = std::stoul(params[1]);
            if (x >= size || y >= size) {
                throw std::invalid_argument("invalid position");
                return;
            }
            board[x * size + y] = value;
        }
    } catch (std::invalid_argument const& ex) {
        std::cout << "ERROR " << ex.what() << "\r" << std::endl;
        return;
    }
    br_move_t move = this->_game.playMove();
    std::cout << move.x << "," << move.y << "\r" << std::endl;
}

void ControlTow::handle_begin([[maybe_unused]] std::string &cmd)
{
    br_move_t move = this->_game.playMove();
    std::cout << move.x << "," << move.y << "\r" << std::endl;
}

std::vector<std::string> ControlTow::getCmdParams(std::string &cmd)
{
    std::vector<std::string> params;

    if (cmd.find(' ') == std::string::npos) {
        return params;
    }
    cmd = cmd.substr(cmd.find(' ') + 1);
    while (cmd.find(',') != std::string::npos) {
        std::string subParam = cmd.substr(0, cmd.find(','));
        params.push_back(subParam);
        cmd = cmd.substr(cmd.find(',') + 1);
    }
    params.push_back(cmd);
    return params;
}
