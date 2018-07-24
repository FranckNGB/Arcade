/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by asianpw,
*/

#ifndef CPP_ARCADE_GAMELOADER_HPP
#define CPP_ARCADE_GAMELOADER_HPP

#include "IGame.hpp"

class GameLoader {
public:
	explicit	GameLoader(std::string const &);
	~GameLoader();
public:
	IGame	*(*create)();
	void	(*destroy)(IGame *);
private:
	void *handle;

};

#endif //CPP_ARCADE_GAMELOADER_HPP
