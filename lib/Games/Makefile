##
## EPITECH PROJECT, 2018
## Arcade
## File description:
## Makefile for Compile all games library
##

WARN_COLOR	=	\033[0;33m
NO_COLOR	=	\033[m
COM_COLOR	=	\033[0;34m

all:
	@printf "\n$(WARN_COLOR)% 50s % 30s$(NO_COLOR)\n\n" "[BUILD] Graphics" "" | tr ' ' '-'
	mkdir ../../games
	@make --no-print-directory -C ./Pacman all
	@make --no-print-directory -C ./Nibbler all
	@printf "$(WARN_COLOR)% 50s % 30s$(NO_COLOR)\n\n" "[BUILD] Done" "" | tr ' ' '-'

clean:
	@make --no-print-directory -C ./Pacman clean
	@make --no-print-directory -C ./Nibbler clean

fclean:
	@make --no-print-directory -C ./Pacman fclean
	@make --no-print-directory -C ./Nibbler fclean
	rm -fr ../../games


re: fclean all

.PHONY: all re fclean clean