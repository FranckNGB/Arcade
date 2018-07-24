/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by asianpw,
*/

#include <dlfcn.h>
#include "../inc/GameLoader.hpp"
#include "../inc/ArcadeException.hpp"

GameLoader::GameLoader(std::string const &libraryPath)
{
	handle = dlopen(libraryPath.c_str(), RTLD_LAZY);
	if (handle == nullptr) {
		throw arcade::LoaderError(dlerror());
	}
	create = (IGame *(*)())dlsym(handle, "init_game");
	if (!create) {
		throw arcade::LoaderError(dlerror());
	}
	destroy = (void (*)(IGame *))dlsym(handle, "destroy_game");
	if (!destroy) {
		throw arcade::LoaderError(dlerror());
	}
}

GameLoader::~GameLoader()
{
	dlclose(handle);
}