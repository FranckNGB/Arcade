/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Arcade
*/

#include <iostream>
#include "../inc/Core.hpp"
#include "../inc/ArcadeException.hpp"

int	startArcade(char *libraryPath)
{
	std::unique_ptr<Core>	arcade = nullptr;
	int	exit_value = EXIT_SUCCESS;

	try {
		arcade = std::make_unique<Core>(libraryPath);
		arcade->loop();
	} catch (arcade::CoreError const &error) {
		std::cerr << error.what() << std::endl;
		exit_value = 84;
	}
	return (exit_value);
}