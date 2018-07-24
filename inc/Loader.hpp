/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by asianpw,
*/

#ifndef CPP_ARCADE_LOADER_HPP
#define CPP_ARCADE_LOADER_HPP

#include <memory>
#include "IDisplay.hpp"

class Loader {
public:
	explicit Loader(std::string const &);
	~Loader();
public:
	IDisplay *(*create)(size_t, size_t);
	void (*destroy)(IDisplay *);
private:
	void *handle;
};

#endif //CPP_ARCADE_LOADER_HPP
