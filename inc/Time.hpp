/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Time
*/
#ifndef CPP_ARCADE_TIME_HPP
#define CPP_ARCADE_TIME_HPP

#include <chrono>

using ms = std::chrono::milliseconds;
using sc = std::chrono::steady_clock;

inline long	getCurrentTime() {return std::chrono::duration_cast<ms>(sc::now().time_since_epoch()).count();};

#endif //CPP_ARCADE_TIME_HPP
