/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Core
*/
#include <iostream>
#include "../inc/Core.hpp"
#include "../inc/Menu.hpp"
#include "../inc/ArcadeException.hpp"

Core::Core(std::string const &path) : scene(std::make_unique<Menu>(path)), loader(nullptr), gameLoader(nullptr), game(nullptr), display(nullptr), path(path)
{
	try {
		loader = std::make_unique<Loader>(path);
	} catch (arcade::LoaderError const& e) {
		throw arcade::CoreError(e.what());
	}
	try {
		display = loader->create(arcade::WIDTH, arcade::HEIGHT);
	} catch (arcade::GraphicsLibraryError const &e) {
		throw arcade::CoreError(e.what());
	}
}

void	Core::loop()
{
	while (display->isOpen()) {
		while (display->isKey())
			scene->sceneEvent(display);
		try {
			if (display->getChange())
				switchGraphicsLibrary();
			if (display->getSwitchScene())
				switchScene();
		} catch (arcade::CoreError const &e) {
			throw arcade::CoreError(e);
		}
		scene->compute();
		display->loadTexture(scene->getTexture());
		display->loadMap(scene->getMap());
		display->loadText(scene->getText());
		display->Display();
	}
}

Core::~Core()
{
	if (scene != nullptr)
		scene.reset();
	if (gameLoader != nullptr && game != nullptr)
		gameLoader->destroy(game.release());
	if (loader != nullptr && display != nullptr)
		loader->destroy(display);
}

void	Core::switchGraphicsLibrary()
{
	std::string	tmpPath = arcade::GRAPHICSDIR + display->getLibraryPath();

	display->setChange(false);
	if (display->getLibraryPath().empty())
		return;
	if (display->isOpen())
		display->destroyWindow();
	loader->destroy(display);
	display = nullptr;
	try {
		loader.reset();
		loader = std::make_unique<Loader>(tmpPath);
	} catch (arcade::LoaderError const& e) {
		loader = nullptr;
		throw arcade::CoreError(e.what());
	}
	try {
		display = loader->create(arcade::WIDTH, arcade::HEIGHT);
	} catch (arcade::GraphicsLibraryError const &e) {
		throw arcade::CoreError(e.what());
	}
	path = tmpPath;
}

void Core::switchScene()
{
	display->setSwitchScene(false);
	if (display->getNewGamePath() == "menu") {
		scene.reset();
		game.reset();
		gameLoader.reset();
		scene = std::make_unique<Menu>(path);
		return ;
	}
	try {
		gameLoader.reset();
		gameLoader = std::make_unique<GameLoader>(display->getNewGamePath());
		game.reset(gameLoader->create());
		scene.reset(game->start());
	} catch (arcade::LoaderError const& e) {
		throw arcade::CoreError(e.what());
	}
}

void	Core::setChangeLibrary(std::string const &path)
{
	display->changeLibrary(path);
}

void	Core::setChangeScene(std::string const &path)
{
	display->setSwitchScene(true);
	display->setNewGamePath(path);
}