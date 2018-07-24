/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by asianpw,
*/

#include <dlfcn.h>
#include <iostream>
#include "../inc/Loader.hpp"
#include "../inc/ArcadeException.hpp"
#include "../inc/IDisplay.hpp"

Loader::Loader(std::string const &libraryPath)
{
	handle = dlopen(libraryPath.c_str(), RTLD_LAZY);
	if (handle == nullptr) {
		throw arcade::LoaderError(dlerror());
	}
	create = (IDisplay *(*)(size_t, size_t))dlsym(handle, "create_object");
	if (!create) {
		throw arcade::LoaderError(dlerror());
	}
	destroy = (void (*)(IDisplay *))dlsym(handle, "destroy_object");
	if (!destroy) {
		throw arcade::LoaderError(dlerror());
	}
}

Loader::~Loader()
{
	dlclose(handle);
}