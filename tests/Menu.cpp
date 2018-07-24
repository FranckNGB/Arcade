/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Menu
*/

#include <unistd.h>
#include <criterion/criterion.h>
#include "../inc/Menu.hpp"
#include "../inc/Time.hpp"
#include "../inc/Sfml.hpp"

Test(MENU_TEST, GET_MAP)
{
	std::unique_ptr<Menu>	menu = std::make_unique<Menu>("./lib/lib_arcade_sfml.so");

	cr_assert(menu->getMap().empty(), "Menu: Map isn't empty");
}

Test(MENU_TEST, GET_TEXTURE)
{
	std::unique_ptr<Menu>	menu = std::make_unique<Menu>("./lib/lib_arcade_sfml.so");

	cr_assert_not(menu->getTexture().empty(), "Menu: texture is empty");
}

Test(MENU_TEST, GET_TEXT)
{
	std::unique_ptr<Menu>	menu = std::make_unique<Menu>("./lib/lib_arcade_sfml.so");

	cr_assert_not(menu->getText().empty(), "Menu: text is empty");
}

Test(MENU_TEST, COMPUTE)
{
	std::unique_ptr<Menu>	menu = std::make_unique<Menu>("./lib/lib_arcade_sfml.so");
	size_t	count = 0;

	menu->compute();
	sleep(5);
	menu->compute();
	while ( count < (arcade::WIDTH / 2) + 50) {
		menu->compute();
		count++;
	}
	cr_assert(true, "Compute isn't working");
}

Test(MENU_TEST, MENU_LEFT)
{
	std::unique_ptr<Menu>	menu = std::make_unique<Menu>("./lib/lib_arcade_sfml.so");
	std::unique_ptr<SfmlDisplay>	display = std::make_unique<SfmlDisplay>(800, 600);
	sf::Event	tmp = {};

	tmp.type = sf::Event::KeyPressed;
	tmp.key.code = sf::Keyboard::Left;
	display->setEvent(tmp);
	menu->sceneEvent(display.get());
	display->destroyWindow();
}

Test(MENU_TEST, MENU_RIGHT)
{
	std::unique_ptr<Menu>	menu = std::make_unique<Menu>("./lib/lib_arcade_sfml.so");
	std::unique_ptr<SfmlDisplay>	display = std::make_unique<SfmlDisplay>(800, 600);
	sf::Event	tmp = {};

	tmp.type = sf::Event::KeyPressed;
	tmp.key.code = sf::Keyboard::Right;
	display->setEvent(tmp);
	menu->sceneEvent(display.get());
	display->destroyWindow();
}

Test(MENU_TEST, MENU_DOWN)
{
	std::unique_ptr<Menu>	menu = std::make_unique<Menu>("./lib/lib_arcade_sfml.so");
	std::unique_ptr<SfmlDisplay>	display = std::make_unique<SfmlDisplay>(800, 600);
	sf::Event	tmp = {};

	tmp.type = sf::Event::KeyPressed;
	tmp.key.code = sf::Keyboard::Down;
	display->setEvent(tmp);
	menu->sceneEvent(display.get());
	display->destroyWindow();
}

Test(MENU_TEST, MENU_UP)
{
	std::unique_ptr<Menu>	menu = std::make_unique<Menu>("./lib/lib_arcade_sfml.so");
	std::unique_ptr<SfmlDisplay>	display = std::make_unique<SfmlDisplay>(800, 600);
	sf::Event	tmp = {};

	tmp.type = sf::Event::KeyPressed;
	tmp.key.code = sf::Keyboard::Up;
	display->setEvent(tmp);
	menu->sceneEvent(display.get());
	display->destroyWindow();
}

Test(MENU_TEST, MENU_Q)
{
	std::unique_ptr<Menu>	menu = std::make_unique<Menu>("./lib/lib_arcade_sfml.so");
	std::unique_ptr<SfmlDisplay>	display = std::make_unique<SfmlDisplay>(800, 600);
	sf::Event	tmp = {};

	tmp.type = sf::Event::KeyPressed;
	tmp.key.code = sf::Keyboard::Q;
	display->setEvent(tmp);
	menu->sceneEvent(display.get());
	display->destroyWindow();
}

Test(MENU_TEST, MENU_ESCAPE)
{
	std::unique_ptr<Menu>	menu = std::make_unique<Menu>("./lib/lib_arcade_sfml.so");
	std::unique_ptr<SfmlDisplay>	display = std::make_unique<SfmlDisplay>(800, 600);
	sf::Event	tmp = {};

	tmp.type = sf::Event::KeyPressed;
	tmp.key.code = sf::Keyboard::Escape;
	display->setEvent(tmp);
	menu->sceneEvent(display.get());
	display->destroyWindow();
}

Test(MENU_TEST, MENU_ENTER)
{
	std::unique_ptr<Menu>	menu = std::make_unique<Menu>("./lib/lib_arcade_sfml.so");
	std::unique_ptr<SfmlDisplay>	display = std::make_unique<SfmlDisplay>(800, 600);
	sf::Event	tmp = {};

	tmp.type = sf::Event::KeyPressed;
	tmp.key.code = sf::Keyboard::Return;
	display->setEvent(tmp);
	menu->sceneEvent(display.get());
	display->destroyWindow();
}
