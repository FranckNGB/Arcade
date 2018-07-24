##
## EPITECH PROJECT, 2018
## arcade
## File description:
## Makefile for Arcade
##

DEBUG		=	no

NAME		=	arcade

UNIT_TEST	=	unit_test

CXX		=	g++

RM		=	rm -f

SRCS_SHARED =	./src/utils.cpp	\
				./src/Loader.cpp	\
				./src/GameLoader.cpp	\
				./src/Menu.cpp	\
				./src/Core.cpp	\
				./src/Arcade.cpp	\

UNIT_SRCS	=	./tests/ArcadeTest.cpp	\
				./tests/CoreTest.cpp	\
				./tests/Menu.cpp	\
				./tests/GraphicsSfmlTest.cpp	\
				./tests/GraphicsSdl2Test.cpp	\
				./tests/LoaderTest.cpp	\
				./lib/Graphics/Sfml/Sfml.cpp	\
				./lib/Graphics/Sdl2/Sdl2.cpp	\
				$(SRCS_SHARED)	\

SRCS		=	./src/main.cpp	\
				$(SRCS_SHARED)	\


OBJS		=	$(SRCS:.cpp=.o)

UNIT_FLAGS	=	-lcriterion -lsfml-graphics -lsfml-window -lsfml-system -lSDL2 -lSDL2_image -lSDL2_ttf

LDFLAGS		=	-ldl
CXXFLAGS	=	-W -Wall -Wextra -std=c++14
CPPFLAGS	=	-I ./inc/

ifeq ($(DEBUG), y)
CXXFLAGS	+=	-g3
endif

WARN_COLOR	=	\033[0;33m
COM_COLOR	=	\033[0;34m
OBJ_COLOR	=	\033[0;36m
OK_COLOR	=	\033[0;32m
ERROR_COLOR	=	\033[0;31m
NO_COLOR	=	\033[m
OK_STRING	=	"[OK]"
WARN_STRING	=	"[WARNING]"

all: $(NAME)

install:
	sudo apt update
	sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
	sudo apt install libsfml-dev
	sudo apt install libglfw3
	sudo apt install libglfw3-dev
	sudo apt install mesa-vulkan-drivers vulkan-utils

%.o: %.cpp
	@printf "[\033[0;32mcompiled\033[0m] % 70s\n" $< | tr ' ' '.'
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

$(NAME): core games graphicals

core: $(OBJS)
	@printf "$(COM_COLOR)% 50s % 30s$(NO_COLOR)\n" "[BUILD $(NAME)]" "" | tr ' ' '-'
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ -o $(NAME) $(LDFLAGS)


graphicals:
	@make --no-print-directory -C ./lib/Graphics all

games:
	@make --no-print-directory -C ./lib/Games all

generate_coverage: tests_run
	@lcov --directory . -c -o rapport.info
	@genhtml -o ../rapport -t "Coverage of tests" rapport.info

tests_run: re
	@printf "$(COM_COLOR)% 50s % 30s$(NO_COLOR)\n" "[BUILD] $(UNIT_TEST)" "" | tr ' ' '-'
	$(CXX) $(CXXFLAGS) $(UNIT_SRCS) --coverage -o $(UNIT_TEST) $(UNIT_FLAGS) $(LDFLAGS)
	@printf "$(COM_COLOR)% 50s % 30s$(NO_COLOR)\n" "LAUNCH UNIT TEST" "" | tr ' ' '-'
	./$(UNIT_TEST) -j1 --always-succeed

clean:
	@make --no-print-directory -C ./lib/Graphics clean
	@make --no-print-directory -C ./lib/Games clean
ifneq ($(shell find -name '*~'),)
	@printf "[$(ERROR_COLOR)REMOVE$(NO_COLOR)] % 70s\n" "TEMPORARY FILES" | tr ' ' '.'
	@find -name '*~' -delete
endif
ifneq ($(shell find -name '*.gcda' -o -name '*.gcno' -o -name '*.gcov'),)
	@printf "[$(ERROR_COLOR)REMOVE$(NO_COLOR)] % 70s\n" "COVERAGE FILE" | tr ' ' '.'
	@find -name '*.gcda' -delete -o -name '*.gcno' -delete -o -name '*.gcov' -delete
endif
ifneq ($(shell find -name '*.info'),)
	@printf "[$(ERROR_COLOR)REMOVE$(NO_COLOR)] % 70s\n" "INFO FILES" | tr ' ' '.'
	@find -name '*.info' -delete
endif
ifneq ($(shell find -name '*.o'),)
	@printf "[$(ERROR_COLOR)REMOVE$(NO_COLOR)] % 70s\n" "OBJECT FILE ($(NAME))" | tr ' ' '.'
	@$(RM) $(OBJS)
else
	@printf "[$(WARN_COLOR)NONE$(NO_COLOR)] % 72s\n" "OBJECT FILE ($(NAME))" | tr ' ' '.'
endif

fclean: clean
	@make --no-print-directory -C ./lib/Graphics fclean
	@make --no-print-directory -C ./lib/Games fclean
ifneq ($(shell find -name '$(UNIT_TEST)'),)
	@printf "[$(ERROR_COLOR)REMOVE$(NO_COLOR)] % 70s\n" "$(UNIT_TEST)" | tr ' ' '.'
	@$(RM) $(UNIT_TEST)
else
	@printf "[$(WARN_COLOR)NONE$(NO_COLOR)] % 72s\n" "$(UNIT_TEST)" | tr ' ' '.'
endif
ifneq ($(shell find -name '$(NAME)'),)
	@printf "[$(ERROR_COLOR)REMOVE$(NO_COLOR)] % 70s\n" "$(NAME)" | tr ' ' '.'
	@$(RM) $(NAME)
else
	@printf "[$(WARN_COLOR)NONE$(NO_COLOR)] % 72s\n" "$(NAME)" | tr ' ' '.'
endif

re: fclean all

.PHONY: all clean fclean re tests_run generate_coverage install
