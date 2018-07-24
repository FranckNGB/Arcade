//
// EPITECH PROJECT, 2021
// cpp_arcade
// File description:
// Created by asianpw,
//

#ifndef CPP_ARCADE_IDISPLAY_HPP
#define CPP_ARCADE_IDISPLAY_HPP

#include <string>
#include <map>
#include "utils.hpp"
#include "Texture.hpp"

class IDisplay {
public:
	virtual ~IDisplay() = default;
public:
	virtual bool	Display() = 0;
	virtual bool	isKey() = 0;
	virtual bool	isOpen() = 0;
	virtual bool	GetKey(arcade::TypeEvent, std::string const&) = 0;
	virtual bool	loadTexture(std::map<std::string, Texture> const&) = 0;
	virtual	bool	loadMap(std::vector<std::vector<char>> const&) = 0;
	virtual bool	loadText(std::map<std::string, Texture> const&) = 0;
	virtual void	destroyWindow() = 0;
	virtual void	changeLibrary(std::string const &path) = 0;
	virtual bool	getChange() const = 0;
	virtual std::string const	&getNewGamePath() const = 0;
	virtual void	setNewGamePath(std::string const &) = 0;
	virtual	bool	getSwitchScene() const = 0;
	virtual void	setSwitchScene(bool) = 0;
	virtual void	setChange(bool) = 0;
	virtual std::string const	&getLibraryPath() const = 0;
protected:
	bool	change;
	bool	switchScene;
	std::string	newGamePath;
	std::string	newLibraryPath;
};

#endif //CPP_ARCADE_IDISPLAY_HPP
