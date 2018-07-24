/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by asianpw,
*/

#ifndef CPP_ARCADE_MENU_HPP
#define CPP_ARCADE_MENU_HPP

#include "IScene.hpp"
#include "Loader.hpp"
#include "IGame.hpp"
#include "GameLoader.hpp"
#include "Alias.hpp"

static const char PRESS[] = "Press Enter";

class Menu : public IScene {
public:
	explicit Menu(std::string const &path);
	~Menu() override = default;
	void		sceneEvent(IDisplay *) override;
	textureList	getTexture() const override;
	textureList	getText() const override;
	mapChar 	getMap() const override;
	void		compute() override;
public:
	void	chooseGraphics(std::string const &);
	void	listFiles(const char* path, stringList &list);
	void	init_text(char const *, stringList &, textureList &, Position &);
private:
	textureList	menuTexture;
	textureList	menuText;
	mapChar		menuMap;
	stringList	*current;
	stringList	graphicLib;
	stringList	gamesLib;
	long	currentTime;
	long	marioTime;
};

#endif //CPP_ARCADE_MENU_HPP
