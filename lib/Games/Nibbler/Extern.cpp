/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by asianpw,
*/

#include "../../../inc/IGame.hpp"
#include "Nibbler.hpp"

extern "C" IGame	*init_game()
{
	return new Nibbler();
}

extern "C" void	destroy_game(IGame *game)
{
	delete(game);
}