//
// EPITECH PROJECT, 2021
// cpp_arcade
// File description:
// Created by asianpw,
//

#include <string>
#include <iostream>
#include "../inc/Texture.hpp"
#include "../inc/utils.hpp"
#include "../inc/Arcade.hpp"

void	printHelp(const char *binaryName)
{
	std::cerr << "USAGE:" << std::endl
		<< binaryName << " path_to_graphic_library" << std::endl;
}

int	main(int ac, char **av)
{
	int	exitValue;

	if (ac == 2) {
		exitValue = startArcade(av[1]);
	} else {
		printHelp(av[0]);
		exitValue = 84;
	}
	return exitValue;
}