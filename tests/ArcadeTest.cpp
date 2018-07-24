/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** ArcadeTest
*/

#include <criterion/criterion.h>
#include "../inc/Arcade.hpp"
#include "../inc/ArcadeException.hpp"
#include "../inc/utils.hpp"

Test(START_ARCADE, TEST_EXCEPTION)
{
	char	path[] = "just_a_library_path";

	cr_assert_throw(startArcade(path), arcade::CoreError, "StartArcade Exception not catch");
}

Test(UTILS, FILE_EXIST, .description = "Check if file exist")
{
	cr_expect(checkFileExist("Makefile"),
		"Test for check existing file failed !");
	cr_expect_not(checkFileExist("dsqjlkdsq"),
		"Test for a file doesn't exist failed !");
}