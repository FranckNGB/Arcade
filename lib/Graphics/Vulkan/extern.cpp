/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by asianpw,
*/

#include "Vulkan.hpp"
#include "../../../inc/IDisplay.hpp"

extern "C" {
	IDisplay	*create_object(size_t w, size_t h)
	{
		return new Vulkan(w, h);
	}

	void	destroy_object(IDisplay *object)
	{
		delete object;
	}
};
