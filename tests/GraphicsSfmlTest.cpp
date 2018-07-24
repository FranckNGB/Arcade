//
// EPITECH PROJECT, 2021
// cpp_arcade
// File description:
// Created by asianpw,
//

#include <criterion/criterion.h>
#include <iostream>
#include "../inc/Sfml.hpp"
#include "../inc/Loader.hpp"
#include "../inc/ArcadeException.hpp"

Test(SFML_Library, ESCAPE_Key, .description = "Test of KEY_ESCAPE binding")
{
	std::unique_ptr<SfmlDisplay> sfml = std::make_unique<SfmlDisplay>(800, 600);
	sf::Event tmp = {};

	tmp.type = sf::Event::KeyPressed;
	tmp.key.code = sf::Keyboard::Escape;
	sfml->setEvent(tmp);
	cr_assert(sfml->GetKey(arcade::KEYBOARD, arcade::ESCAPE),
		"Test ESCAPE Key failed !\n");
}

Test(SFML_Library, UP_Key, .description = "Test of KEY_UP binding")
{
	std::unique_ptr<SfmlDisplay> sfml = std::make_unique<SfmlDisplay>(800, 600);
	sf::Event tmp = {};

	tmp.type = sf::Event::KeyPressed;
	tmp.key.code = sf::Keyboard::Up;
	sfml->setEvent(tmp);
	cr_assert(sfml->GetKey(arcade::KEYBOARD, arcade::UP),
		"Test UP Key failed !\n");
}

Test(SFML_Library, DOWN_Key, .description = "Test of KEY_DOWN binding")
{
	std::unique_ptr<SfmlDisplay> sfml = std::make_unique<SfmlDisplay>(800, 600);
	sf::Event tmp = {};

	tmp.type = sf::Event::KeyPressed;
	tmp.key.code = sf::Keyboard::Down;
	sfml->setEvent(tmp);
	cr_assert(sfml->GetKey(arcade::KEYBOARD, arcade::DOWN),
		"Test Down Key failed !\n");
}

Test(SFML_Library, CLOSE_Window, .description = "Simulate Close Window")
{
	std::unique_ptr<SfmlDisplay> sfml = std::make_unique<SfmlDisplay>(800, 600);
	sf::Event tmp = {};

	tmp.type = sf::Event::Closed;
	sfml->setEvent(tmp);
	cr_assert(sfml->GetKey(arcade::WINDOW, arcade::CLOSE),
		"Test Close Window failed !\n");
}

Test(SFML_Library, Check_isKey, .description = "Simulate Close Window")
{
	std::unique_ptr<SfmlDisplay> sfml = std::make_unique<SfmlDisplay>(800, 600);
	sf::Event tmp = {};

	tmp.type = sf::Event::Closed;
	sfml->setEvent(tmp);
	cr_assert(sfml->isKey(), "Test isKey initialize failed !\n");
}


Test(SFML_Library, INVALID_EVENT_TYPE, .description = "Send invalid event type")
{
	std::unique_ptr<SfmlDisplay> sfml = std::make_unique<SfmlDisplay>(800, 600);
	sf::Event tmp = {};

	tmp.type = sf::Event::Closed;
	sfml->setEvent(tmp);
	cr_assert_not(sfml->GetKey(arcade::KEYBOARD, arcade::CLOSE),
		"Send invalid event type failed !\n");
}

Test(SFML_Library, INVALID_KEY_CODE, .description = "Send invalid key code")
{
	std::unique_ptr<SfmlDisplay> sfml = std::make_unique<SfmlDisplay>(800, 600);
	sf::Event tmp = {};

	tmp.type = sf::Event::Closed;
	sfml->setEvent(tmp);
	cr_assert_not(sfml->GetKey(arcade::WINDOW, "a"),
		"Send invalid key code failed !\n");
}

Test(SFML_Library, isOpen, .description = "Check if window is open")
{
	std::unique_ptr<SfmlDisplay> sfml = std::make_unique<SfmlDisplay>(800, 600);

	cr_assert(sfml->isOpen(), "Test window is open failed !\n");
	sfml->Display();
	sfml->destroyWindow();
}

Test(SFML_LIBRARY, EXCEPTION_WINDOW)
{
	std::unique_ptr<SfmlDisplay>	sfml = nullptr;

	cr_assert_throw(sfml = std::make_unique<SfmlDisplay>(-1, -1), arcade::GraphicsLibraryError, "SFML doesn't crash");
}

Test(SFML_LIBRARY, Load_SFML_LIBRARY)
{
	std::unique_ptr<Loader>	loader = std::make_unique<Loader>((char *)"./lib/lib_arcade_sfml.so");
	std::unique_ptr<IDisplay>	display(loader->create(800, 600));

	cr_assert_not_null(display, "Loading SFML library failed !");
	loader->destroy(display.release());
}

Test(SFML_LIBRARY, LOAD_MAP)
{
	std::unique_ptr<SfmlDisplay> sfml = std::make_unique<SfmlDisplay>(800, 600);
	std::vector<std::vector<char>>	map;

	cr_assert_not(sfml->loadMap(map), "SFML Load map Failed");
	sfml->destroyWindow();
}

Test(SFML_LIBRARY, GAME_PATH)
{
	std::unique_ptr<SfmlDisplay> sfml = std::make_unique<SfmlDisplay>(800, 600);

	sfml->setNewGamePath("game_path");
	cr_assert(sfml->getNewGamePath() == "game_path", "SFML_GAME_PATH Failed");
	sfml->destroyWindow();
}

Test(SFML_LIBRARY, CHANGE)
{
	std::unique_ptr<SfmlDisplay> sfml = std::make_unique<SfmlDisplay>(800, 600);

	sfml->setChange(true);
	cr_assert(sfml->getChange(), "SFML_CHANGE Failed");
	sfml->destroyWindow();
}

Test(SFML_LIBRARY, SWITCH_SCENE)
{
	std::unique_ptr<SfmlDisplay> sfml = std::make_unique<SfmlDisplay>(800, 600);

	sfml->setSwitchScene(true);
	cr_assert(sfml->getSwitchScene(), "SFML_SWITCH_SCENE Failed");
	sfml->destroyWindow();
}

Test(SFML_LIBRARY, CHANGE_LIBRARY)
{
	std::unique_ptr<SfmlDisplay> sfml = std::make_unique<SfmlDisplay>(800, 600);

	sfml->changeLibrary("sdl");
	cr_assert(sfml->getLibraryPath() == "sdl", "SFML_LIBRARY_PATH Failed");
	cr_assert(sfml->getChange(), "SFML_CHANGE Failed");
	sfml->destroyWindow();
}

Test(SFML_LIBRARY, LOAD_TEXTURE)
{
	std::unique_ptr<SfmlDisplay> sfml = std::make_unique<SfmlDisplay>(800, 600);
	std::map<std::string, Texture>	texture;

	texture.insert({"texture", (Texture){"./res/wall_nibbler.png", ' ', true, true, {400, 300}}});
	texture.insert({"text", (Texture){"./res/wall_nibbler.png", ' ', false, true, {20, 300}}});
	cr_assert(sfml->loadTexture(texture), "SFML_LOAD_TEXTURE");
	sfml->Display();
	sfml->destroyWindow();
}

Test(SFML_LIBRARY, LOAD_TEXT)
{
	std::unique_ptr<SfmlDisplay> sfml = std::make_unique<SfmlDisplay>(800, 600);
	std::map<std::string, Texture>	texture;

	texture.insert({"texture", (Texture){"./res/wall_nibbler.png", ' ', true, true, {400, 300}}});
	texture.insert({"text", (Texture){"./res/wall_nibbler.png", ' ', false, true, {20, 300}}});
	cr_assert(sfml->loadText(texture), "SFML_LOAD_TEXT");
	sfml->Display();
	sfml->destroyWindow();
}