//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// IPlayer.hpp
//
#ifndef CPP_ARCADE_IPLAYER_HPP
#define CPP_ARCADE_IPLAYER_HPP

#include <cstdio>

class IPlayer {
public:
	virtual IPlayer() = 0;
	virtual ~IPlayer() = 0;

protected:
	size_t	posX;
	size_t	posY;
	size_t	life;
};

#endif //CPP_ARCADE_IPLAYER_HPP
