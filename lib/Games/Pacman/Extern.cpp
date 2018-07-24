/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by asianpw,
*/

#include "../../../inc/IGame.hpp"
#include "Pacman.hpp"

extern "C" IGame	*init_game()
{
	return new Pacman();
}

extern "C" void	destroy_game(IGame *game)
{
	delete(game);
}