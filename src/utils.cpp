//
// EPITECH PROJECT, 2021
// cpp_arcade
// File description:
// Created by asianpw,
//

#include <cstddef>
#include <cstdint>
#include <vector>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include "../inc/Texture.hpp"

bool	checkFileExist(std::string const & file) noexcept
{
	if (!access(file.c_str(), F_OK))
		return true;
	return false;
}
