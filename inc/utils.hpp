//
// EPITECH PROJECT, 2021
// cpp_arcade
// File description:
// Created by asianpw,
//

#ifndef CPP_ARCADE_UTILS_HPP
#define CPP_ARCADE_UTILS_HPP

#include <cstdint>
#include <vector>
#include <string>

namespace arcade {
	enum TypeEvent {
		WINDOW,
		JOYSTICK,
		KEYBOARD,
		MOUSE
	};

	static const size_t	WIDTH = 800;
	static const size_t	HEIGHT = 600;

	static const char	ESCAPE[] = "ESCAPE";
	static const char	CLOSE[] = "CLOSE";
	static const char	UP[] = "UP";
	static const char	DOWN[] = "DOWN";
	static const char	LEFT[] = "LEFT";
	static const char	RIGHT[] = "RIGHT";
	static const char	ENTER[] = "ENTER";
	static const char	Q[] = "Q";
	static const char	M[] = "M";

	static const char	GRAPHICSDIR[] = "./lib/";
	static const char	GAMESDIR[] = "./games/";
}

bool checkFileExist(std::string const &) noexcept;

#endif //CPP_ARCADE_UTILS_HPP
