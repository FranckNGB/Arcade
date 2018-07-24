/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by asianpw,
*/

#include <criterion/criterion.h>
#include "../inc/Sdl2.hpp"
#include "../inc/ArcadeException.hpp"

using criterion::logging::warn;

Test(SDL2_TEST, ESCAPE_KEY)
{
	std::unique_ptr<Sdl2>	sdl = std::make_unique<Sdl2>(800, 600);
	SDL_Event	event;

	event.key.keysym.scancode = SDL_SCANCODE_ESCAPE;
	sdl->setEvent(event);
	cr_assert(sdl->GetKey(arcade::KEYBOARD, arcade::ESCAPE),
		"ESCAPE_KEY test Failed");
	sdl->destroyWindow();
}

Test(SDL2_TEST, UNKNOWN_KEY)
{
	std::unique_ptr<Sdl2>	sdl = std::make_unique<Sdl2>(800, 600);
	SDL_Event	event;

	event.key.keysym.scancode = SDL_SCANCODE_L;
	sdl->setEvent(event);
	cr_assert_not(sdl->GetKey(arcade::KEYBOARD, arcade::ESCAPE),
		"UNKNOWN_KEY test Failed");
	sdl->destroyWindow();
}

Test(SDL2_TEST, UNKNOWN_KEY2)
{
	std::unique_ptr<Sdl2>	sdl = std::make_unique<Sdl2>(800, 600);

	SDL_Event	event;
	event.key.keysym.scancode = SDL_SCANCODE_ESCAPE;
	sdl->setEvent(event);
	cr_assert_not(sdl->GetKey(arcade::KEYBOARD, "L"),
		"UNKNOWN_KEY2 test Failed");
	sdl->destroyWindow();
}

Test(SDL2_TEST, EVENT)
{
	std::unique_ptr<Sdl2>	sdl = std::make_unique<Sdl2>(800, 600);

	SDL_Event	event;
	event.window.event = SDL_WINDOWEVENT_CLOSE;
	sdl->setEvent(event);
	cr_assert(sdl->GetKey(arcade::WINDOW, arcade::CLOSE),
		"EVENT test Failed");
	sdl->destroyWindow();
}

Test(SDL2_TEST, WINDOW_IS_OPEN)
{
	std::unique_ptr<Sdl2>	sdl = std::make_unique<Sdl2>(800, 600);

	cr_assert(sdl->isOpen(), "IS_OPEN test Failed");
	sdl->destroyWindow();
}

Test(SDL2_TEST, KEY_PRESSED)
{
	std::unique_ptr<Sdl2>	sdl = std::make_unique<Sdl2>(800, 600);

	cr_assert(sdl->isKey(), "KEY_PRESSED test Failed");
	sdl->destroyWindow();
	cr_assert_not(sdl->isKey(), "KEY_PRESS after window destroy");
}

Test(SDL2_TEST, DISPLAY)
{
	std::unique_ptr<Sdl2>	sdl = std::make_unique<Sdl2>(800, 600);

	cr_assert(sdl->Display(), "DISPLAY test Failed");
	sdl->destroyWindow();
	sdl->destroyWindow();
}

Test(SDL2_TEST, FAILED_WINDOW_CREATION)
{
	std::unique_ptr<Sdl2>	sdl = nullptr;

	warn << "An Exception must be catch for this test" << std::flush;
	cr_assert_throw(sdl = std::make_unique<Sdl2>(Sdl2(-1, -1)), arcade::GraphicsLibraryError, "SDL2 throw error");
}

Test(SDL2_TEST, LOAD_MAP)
{
	std::unique_ptr<Sdl2> sdl = std::make_unique<Sdl2>(800, 600);
	std::vector<std::vector<char>>	map;

	cr_assert_not(sdl->loadMap(map), "sdl Load map Failed");
	sdl->destroyWindow();
}

Test(SDL2_TEST, GAME_PATH)
{
	std::unique_ptr<Sdl2> sdl = std::make_unique<Sdl2>(800, 600);

	sdl->setNewGamePath("game_path");
	cr_assert(sdl->getNewGamePath() == "game_path", "SDL_GAME_PATH Failed");
	sdl->destroyWindow();
}

Test(SDL2_TEST, CHANGE)
{
	std::unique_ptr<Sdl2> sdl = std::make_unique<Sdl2>(800, 600);

	sdl->setChange(true);
	cr_assert(sdl->getChange(), "SDL_CHANGE Failed");
	sdl->destroyWindow();
}

Test(SDL2_TEST, SWITCH_SCENE)
{
	std::unique_ptr<Sdl2> sdl = std::make_unique<Sdl2>(800, 600);

	sdl->setSwitchScene(true);
	cr_assert(sdl->getSwitchScene(), "SDL_SWITCH_SCENE Failed");
	sdl->destroyWindow();
}

Test(SDL2_TEST, CHANGE_LIBRARY)
{
	std::unique_ptr<Sdl2> sdl = std::make_unique<Sdl2>(800, 600);

	sdl->changeLibrary("sdl");
	cr_assert(sdl->getLibraryPath() == "sdl", "SDL_LIBRARY_PATH Failed");
	cr_assert(sdl->getChange(), "SDL_CHANGE Failed");
	sdl->destroyWindow();
}

Test(SDL2_TEST, LOAD_TEXTURE)
{
	std::unique_ptr<Sdl2> sdl = std::make_unique<Sdl2>(800, 600);
	std::map<std::string, Texture>	texture;

	texture.insert({"texture", (Texture){"./res/wall_nibbler.png", ' ', true, true, {400, 300}}});
	texture.insert({"img_not_exist", (Texture){"./res/wall_.png", ' ', true, true, {400, 300}}});
	texture.insert({"text", (Texture){"./res/wall_nibbler.png", ' ', false, true, {20, 300}}});
	texture.insert({"text1", (Texture){"dlksqj:", ' ', false, true, {20, 30}}});
	texture.insert({"text2", (Texture){"dsqdjsq", ' ', false, true, {20, 300}}});
	cr_assert(sdl->loadTexture(texture), "SDL_LOAD_TEXTURE");
	sdl->Display();
	sdl->loadTexture(texture);
	sdl->destroyWindow();
}

Test(SDL2_TEST, LOAD_TEXT)
{
	std::unique_ptr<Sdl2>	sdl = std::make_unique<Sdl2>(800, 600);
	std::map<std::string, Texture>	texture;

	texture.insert({"texture", (Texture){"./res/wall_nibbler.png", ' ', true, true, {400, 300}}});
	texture.insert({"img_not_exist", (Texture){"./res/wall_.png", ' ', true, true, {400, 300}}});
	texture.insert({"text", (Texture){"./res/wall_nibbler.png", ' ', false, true, {20, 300}}});
	texture.insert({"text1", (Texture){"dlksqj:", ' ', false, true, {20, 30}}});
	texture.insert({"text2", (Texture){"dsqdjsq", ' ', false, true, {20, 300}}});
	cr_assert(sdl->loadText(texture), "SDL_LOAD_TEXT");
	sdl->Display();
	sdl->loadText(texture);
	sdl->destroyWindow();
}