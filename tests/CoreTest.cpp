/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** CoreTest
*/

#include <signal.h>
#include <criterion/criterion.h>
#include <thread>
#include "../inc/Core.hpp"
#include "../inc/ArcadeException.hpp"

Test(CORE_TEST, CREATION_DESTRUCTION_CORE)
{
	std::unique_ptr<Core>	core;

	cr_assert_no_throw(core = std::make_unique<Core>("./lib/lib_arcade_sfml.so"), arcade::CoreError, "Core: An error occur while init");
}

Test(CORE_TEST, CREATION_DESTRUCTION_CORE_FAIL)
{
	std::unique_ptr<Core>	core;

	cr_assert_throw(core = std::make_unique<Core>("./lib/lib_arcade_ncurses.so"), arcade::CoreError, "Core: An error occur while init");
}

Test(CORE_TEST, SWITCH_GRAPHICS_LIBRARY_FAIL)
{
	std::unique_ptr<Core>	core = std::make_unique<Core>("./lib/lib_arcade_sfml.so");

	core->setChangeLibrary("failed");
	cr_assert_throw(core->loop(), arcade::CoreError, "Core: An error occur while loop");
}

Test(CORE_TEST, SWITCH_SCENE_FAIL)
{
	std::unique_ptr<Core>	core = std::make_unique<Core>("./lib/lib_arcade_sfml.so");

	core->setChangeScene("failed");
	cr_assert_throw(core->loop(), arcade::CoreError, "Core: An error occur while loop");
}

Test(GAME_LOADER_TEST, CONSTRUCT_AND_DESTROY)
{
	std::unique_ptr<GameLoader>	loader;

	cr_assert_no_throw(loader = std::make_unique<GameLoader>("./games/lib_arcade_nibbler.so"), arcade::LoaderError, "An unexpected exception catch")
}