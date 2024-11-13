#            d8b
#            ?88
#             88b
#   88bd88b   888888b  d8888b
#   88P' ?8b  88P `?8bd8P' `P
# d88   88P d88,  d8888b
# d88'   88bd88'`?88P'`?888P'

# Author: hodos, 28/10/2024,
# nbc signature powered by love.

name = pbrain-gomoku-ai

tests_name = 	unit_tests

src := $(shell find src -wholename 'src/*.cpp')

test_files 	=	$(shell find tests -wholename 'tests/*.cpp')

src_test 	=	src/Game.cpp \
				src/Minimax.cpp

obj = $(src:.cpp=.o)

obj_test = 	$(src_test:%.c=%.o)

inc = -I./inc

cflags = $(inc) -I -Wall -Wextra -std=c++17

test_flags = --coverage -lcriterion -lm -fprofile-arcs -ftest-coverage -std=c++17

.cpp.o:
	@g++ -g -c $< -o $(<:.cpp=.o) $(cflags)
	@printf " 📦 \033[36m%s\n\033[39m" $(<:.cpp=.o)

all: $(obj)
	@g++ -g -o $(name) $(obj) $(cflags)
	@printf " 📦 \033[32m$(name) is ready\033[0m\n"

clean:
	@rm -f $(obj)
	@printf " 📦 \033[31mclean is done\033[0m\n"

fclean: clean
	@rm -f $(name)
	@rm -f ./plugins/*.so

tests_run: fclean $(obj_test)
	@rm -rf unit_tests*
	@g++ -o $(tests_name) $(test_files) $(obj_test) $(inc) $(test_flags)
	@gcovr --exclude tests/
	@gcovr --exclude tests/ --branches

re: fclean all
