/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by asianpw,
*/

#ifndef CPP_ARCADE_NCURSES_HPP
#define CPP_ARCADE_NCURSES_HPP

#include <string>
#include <map>
#include <ncurses.h>
#include "IDisplay.hpp"
#include "Alias.hpp"

static const int KEY_Q = 113;
static const int KEY_RETURN = 10;

class NcursesDisplay : public IDisplay {
public:
	NcursesDisplay(size_t, size_t);
	~NcursesDisplay() override;
public:
	bool	Display() override;
	bool	isOpen() override;
	bool	GetKey(arcade::TypeEvent, std::string const &) override;
	bool	isKey() override;
	bool	loadTexture(textureList const&) override;
	bool	loadText(textureList const&) override;
	void	changeLibrary(std::string const &) override;
	bool	getChange() const override;
	void	setChange(bool) override;
	const std::string	&getLibraryPath() const override;
	void	destroyWindow() override;
	const std::string	&getNewGamePath() const override;
	void	setNewGamePath(std::string const &) override;
	bool	loadMap(mapChar const &) override;
	bool	getSwitchScene() const override;
	void	setSwitchScene(bool) override;
private:
	eventList	allEvent;
	int		currentKey;
	WINDOW		*window;
};

#endif //CPP_ARCADE_NCURSES_HPP
