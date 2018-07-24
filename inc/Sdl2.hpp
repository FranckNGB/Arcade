/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by asianpw,
*/

#ifndef CPP_ARCADE_SDL2_HPP
#define CPP_ARCADE_SDL2_HPP

#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "utils.hpp"
#include "IDisplay.hpp"
#include "Alias.hpp"

class Sdl2 : public IDisplay {
public:
	Sdl2(size_t, size_t);
	~Sdl2() override;
public:
	bool	Display() override;
	bool	isOpen() override;
	bool	GetKey(arcade::TypeEvent, std::string const &) override;
	bool	isKey() override;
	bool	loadTexture(textureList const&) override;
	bool	loadText(textureList const&) override;
	void	destroyWindow() override;
	void	changeLibrary(std::string const &) override;
	bool	getChange() const override;
	bool	getSwitchScene() const override;
	void	setSwitchScene(bool) override;
	void	setNewGamePath(std::string const &string) override;
	const std::string	&getNewGamePath() const override;
	void	setChange(bool) override;
	bool	loadMap(mapChar const &vector) override;
	std::string const	&getLibraryPath() const override;
	void	setEvent(const SDL_Event &event);
private:
	size_t		width;
	size_t		height;
	bool		finish;
	TTF_Font	*font;
	eventList	allEvent;
	std::map<SDL_Surface*, Position>	texts;
	std::map<SDL_Surface*, Position>	textures;
	SDL_Surface	*windowSurface;
	SDL_Window	*window;
	SDL_Event	event;
};

#endif //CPP_ARCADE_SDL2_HPP
