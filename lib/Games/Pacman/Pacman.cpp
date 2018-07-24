/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by asianpw,
*/

#include <vector>
#include <iostream>
#include "Pacman.hpp"
#include "PacmanScene.hpp"

Pacman::Pacman()
{
	this->name = "Pacman";
	this->description = "Eat a maximun of Pac-Dots in this maze. But watch out for ghosts.";
}

std::string	const&Pacman::getDescription() const
{
	return description;
}

std::string	const&Pacman::getName() const
{
	return name;
}

IScene	*Pacman::start()
{
	return new PacmanScene();
}
