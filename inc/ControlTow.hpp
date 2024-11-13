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

#pragma once

#include <array>
#include <string>
#include <iostream>
#include <functional>
#include <string_view>
#include <unordered_map>

#include "Game.hpp"

struct CommandMapping {
    std::string command;
    std::function<void(std::string&)> handler;
};

enum log_type
{
    UNKNOWN,
    ERROR,
    MESSAGE,
    DEBUG
};

const std::unordered_map<
    log_type,
    std::string_view
> LOG_TYPE_MAPPINGS{
    {UNKNOWN, "UNKNOWN"},
    {ERROR, "ERROR"},
    {MESSAGE, "MESSAGE"},
    {DEBUG, "DEBUG"},
};

class ControlTow {
public:
    void handle_about([[maybe_unused]] std::string &cmd);
    void handle_start(std::string &cmd);
    void handle_end([[maybe_unused]] std::string &cmd);
    void handle_info(std::string &cmd);
    void handle_turn(std::string &cmd);
    void handle_board(std::string &cmd);
    void handle_begin(std::string &cmd);

    const std::array<CommandMapping, 7> COMMAND_MAPPINGS{{
        {
            "ABOUT", std::bind(
                &ControlTow::handle_about,
                this, std::placeholders::_1
            )
        },
        {
            "START", std::bind(
                &ControlTow::handle_start,
                this, std::placeholders::_1
            )
        },
        {
            "END", std::bind(
                &ControlTow::handle_end,
                this, std::placeholders::_1
            )
        },
        {
            "INFO", std::bind(
                &ControlTow::handle_info,
                this, std::placeholders::_1
            )
        },
        {
            "TURN", std::bind(
                &ControlTow::handle_turn,
                this, std::placeholders::_1
            )
        },
        {
            "BOARD", std::bind(
                &ControlTow::handle_board,
                this, std::placeholders::_1
            )
        },
        {
            "BEGIN", std::bind(
                &ControlTow::handle_begin,
                this, std::placeholders::_1
            )
        },
    }};

    auto handle_cmd(std::string &cmd) -> void
    {
        for (const auto &i : COMMAND_MAPPINGS) {
            if (cmd.rfind(i.command, 0) == 0) {
                i.handler(cmd);
                return;
            }
        }
        this->send_log(UNKNOWN, "command is not implemented");
    }

    std::vector<std::string> getCmdParams(std::string &cmd);

    auto send_log(log_type t, const std::string &msg) -> void
    {
        std::cout << LOG_TYPE_MAPPINGS.at(t) << " " << msg << std::endl;
    }

    auto get_should_stop() -> bool
    {
        return (this->SHOULD_STOP);
    }

private:
    bool SHOULD_STOP = false;
    Game _game;
};
