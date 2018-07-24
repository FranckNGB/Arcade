/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by asianpw,
*/

#include <iostream>
#include <dirent.h>
#include <cstring>
#include <algorithm>
#include "../inc/utils.hpp"
#include "../inc/Menu.hpp"
#include "../inc/Texture.hpp"
#include "../inc/GameLoader.hpp"
#include "../inc/ArcadeException.hpp"
#include "../inc/Time.hpp"

Menu::Menu(std::string const &path) : currentTime(getCurrentTime()), marioTime(getCurrentTime())
{
	Position	pos = {arcade::WIDTH / 2 - 100, 100};

	pos.x += 150;
	init_text(arcade::GRAPHICSDIR, graphicLib, menuText, pos);
	chooseGraphics(path);
	pos.x -= 150;
	menuText.insert({"graph", {"choose your graphic library:", ' ', false, true, {pos.x - 280, pos.y - 50}}});
	menuText.insert({"game", {"choose your game:", ' ', false, true, {pos.x - 280, pos.y + 50}}});
	pos.y = 200;
	pos.x += 150;
	init_text(arcade::GAMESDIR, gamesLib, menuText, pos);
	menuText.insert({"press", {PRESS, ' ', false, true, {arcade::WIDTH / 2, 500} } });
	menuTexture.insert({"cursor", {"./res/menu_cursor.png", '>', true, true, {280, 100}}});
	menuTexture.insert({"0", {"./res/menu_back.png", ' ', true, true, {0, 0}}});
	menuTexture.insert({"champi", {"./res/menu_champi.png", ' ', true, true, {-20, 550}}});
	menuTexture.insert({"mario", {"./res/menu_mario.png", ' ', true, true, {-100, 520}}});
	menuTexture.insert({"mariorun", {"./res/menu_mario_run.png", ' ', true, false, {-100, 520}}});
	current = &graphicLib;
}

void	Menu::sceneEvent(IDisplay *display)
{
	auto	it = current->begin();

	if (display->GetKey(arcade::WINDOW, arcade::CLOSE))
		display->destroyWindow();
	if (display->GetKey(arcade::KEYBOARD, arcade::ESCAPE))
		display->destroyWindow();
	if (display->GetKey(arcade::KEYBOARD, arcade::Q))
		display->destroyWindow();
	if (display->GetKey(arcade::KEYBOARD, arcade::UP)) {
		if (menuTexture["cursor"].position.y == 200) {
			menuTexture["cursor"].position.y = 100;
			current = &graphicLib;
		}
	}
	if (display->GetKey(arcade::KEYBOARD, arcade::DOWN)) {
		if (menuTexture["cursor"].position.y == 100) {
			menuTexture["cursor"].position.y = 200;
			current = &gamesLib;
		}
	}
	if (display->GetKey(arcade::KEYBOARD, arcade::LEFT)) {
		while (it != current->end()) {
			if (it != current->begin() && menuText[*it].display) {
				menuText[*it].display = false;
				menuText[*--it].display = true;
				if (current == &graphicLib)
					display->changeLibrary(*it);
				break;
			}
			it++;
		}
	}
	if (display->GetKey(arcade::KEYBOARD, arcade::RIGHT)) {
		while (it != current->end()) {
			if (it != current->end() - 1 && menuText[*it].display) {
				menuText[*it].display = false;
				menuText[*++it].display = true;
				if (current == &graphicLib)
					display->changeLibrary(*it);
				break;
			}
			it++;
		}
	}
	if (display->GetKey(arcade::KEYBOARD, arcade::ENTER)) {
		for (auto const &game : gamesLib) {
			if (menuText[game].display) {
				display->setSwitchScene(true);
				display->setNewGamePath(arcade::GAMESDIR + game);
			}
		}
	}
}

void	Menu::listFiles(const char* path, stringList &list)
{
	DIR		*dirFile = opendir(path);
	struct dirent	*hFile;

	if (dirFile)
	{
		while ((hFile = readdir( dirFile )) != nullptr) {
			if ((hFile->d_name[0] == '.')) continue;
			if (strstr(hFile->d_name, ".so"))
				list.emplace_back(hFile->d_name);
		}
		closedir(dirFile);
	}
}

void	Menu::init_text(char const *dir, stringList &list, textureList &text, Position &pos)
{
	size_t	count = 0;
	unsigned long	subPos;
	std::string	currentPath;
	std::string	toErase;

	listFiles(dir, list);
	for (auto const &current : list) {
		currentPath = current;
		toErase = "lib_arcade_";
		subPos = current.find(toErase);
		if (subPos != std::string::npos)
			currentPath.erase(subPos, toErase.size());
		currentPath.erase(currentPath.size() - 3);
		text.insert({current, {currentPath, ' ', checkFileExist(current), count == 0, {pos.x, pos.y}}});
		count += 1;
	}
}

void	Menu::chooseGraphics(std::string const &path)
{
	std::string	tmp;
	std::string	tmpPath(path);
	size_t	pos;

	pos = path.find("./");
	if (pos != std::string::npos)
		tmpPath.erase(pos, 2);
	for (auto &it : menuText) {
		tmp = arcade::GRAPHICSDIR + it.first;
		pos = tmp.find("./");
		if (pos != std::string::npos)
			tmp.erase(pos, 2);
		it.second.display = (tmpPath == tmp);
	}
}

void	Menu::compute()
{
	long	now = getCurrentTime();

	if (now - currentTime > 250) {
		menuText["press"].display = !menuText["press"].display;
		currentTime = now;
	}
	if (now - marioTime > 150) {
		menuTexture["mario"].display = !menuTexture["mario"].display;
		menuTexture["mariorun"].display = !menuTexture["mariorun"].display;
		marioTime = now;
	}
	menuTexture["champi"].position.x += 2;
	menuTexture["mario"].position.x += 2;
	menuTexture["mariorun"].position.x += 2;
	if (menuTexture["champi"].position.x > (int)(arcade::WIDTH + 20))
		menuTexture["champi"].position.x = -40;
	if (menuTexture["mario"].position.x > (int)(arcade::WIDTH + 20)) {
		menuTexture["mario"].position.x = -40;
		menuTexture["mariorun"].position.x = -40;
	}
}

textureList	Menu::getText() const
{
	return menuText;
}

textureList	Menu::getTexture() const
{
	return menuTexture;
}

mapChar	Menu::getMap() const
{
	return menuMap;
}
