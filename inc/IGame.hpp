/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by asianpw,
*/

#ifndef CPP_ARCADE_IGAME_HPP
#define CPP_ARCADE_IGAME_HPP

#include <string>
#include "IScene.hpp"

class IGame {
public:
	virtual ~IGame() = default;
	virtual	std::string	const &getName() const = 0;
	virtual	std::string	const &getDescription() const = 0;
	virtual	IScene	*start() = 0;
protected:
	std::string	name;
	std::string	description;
};

#endif //CPP_ARCADE_IGAME_HPP
