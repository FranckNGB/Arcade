/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by asianpw,
*/

#ifndef CPP_ARCADE_PACMAN_HPP
#define CPP_ARCADE_PACMAN_HPP

#include "../../../inc/IGame.hpp"
#include "time.h"

class Pacman : public IGame {
public:
	Pacman();
	~Pacman() override = default;
	IScene	*start() override;

public:
	std::string	const &getName() const override;
	std::string	const &getDescription() const override;
};

#endif //CPP_ARCADE_PACMAN_HPP
