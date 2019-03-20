##
## EPITECH PROJECT, 2018
## Arcade
## File description:
## Makefile for Compile all graphics library
##

WARN_COLOR	=	\033[0;33m
NO_COLOR	=	\033[m
COM_COLOR	=	\033[0;34m

all:
	@printf "\n$(WARN_COLOR)% 50s % 30s$(NO_COLOR)\n\n" "[BUILD] Graphics" "" | tr ' ' '-'
	@make --no-print-directory -C ./Sfml all
	@make --no-print-directory -C ./Sdl2 all
	@make --no-print-directory -C ./Ncurses all
	@printf "$(WARN_COLOR)% 50s % 30s$(NO_COLOR)\n\n" "[BUILD] Done" "" | tr ' ' '-'

clean:
	@make --no-print-directory -C ./Sfml clean
	@make --no-print-directory -C ./Sdl2 clean
	@make --no-print-directory -C ./Ncurses clean


fclean:
	@make --no-print-directory -C ./Sfml fclean
	@make --no-print-directory -C ./Sdl2 fclean
	@make --no-print-directory -C ./Ncurses fclean


re: fclean all

.PHONY: all re fclean clean