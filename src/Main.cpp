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

#include <time.h>
#include <stdlib.h>
#include "ControlTow.hpp"
#include <memory>
#include "Game.hpp"

auto main() -> int
{
    Game game;
    std::shared_ptr<ControlTow> ct =
        std::make_shared<ControlTow>(game);

    srand(time(NULL));
    for (
        std::string line;
        !ct->get_should_stop()
        && std::getline(std::cin, line);
    ) {
        ct->handle_cmd(line);
    }
    return 0;
}
