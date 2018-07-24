/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by asianpw,
*/

#include <iostream>
#include "../../../inc/Sdl2.hpp"
#include "../../../inc/ArcadeException.hpp"

Sdl2::Sdl2(size_t w, size_t h) : width(w), height(h), finish(true), window(nullptr)
{
	allEvent.insert({arcade::CLOSE, SDL_WINDOWEVENT_CLOSE});
	allEvent.insert({arcade::ESCAPE, SDL_SCANCODE_ESCAPE});
	allEvent.insert({arcade::UP, SDL_SCANCODE_UP});
	allEvent.insert({arcade::DOWN, SDL_SCANCODE_DOWN});
	allEvent.insert({arcade::LEFT, SDL_SCANCODE_LEFT});
	allEvent.insert({arcade::RIGHT, SDL_SCANCODE_RIGHT});
	allEvent.insert({arcade::ENTER, SDL_SCANCODE_RETURN});
	allEvent.insert({arcade::Q, 4});
	allEvent.insert({arcade::M, 51});
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Quit();
		throw arcade::GraphicsLibraryError(SDL_GetError());
	}
	window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		SDL_Quit();
		throw arcade::GraphicsLibraryError(SDL_GetError());
	}
	windowSurface = SDL_GetWindowSurface(window);
	if (windowSurface == nullptr) {
		SDL_Quit();
		throw arcade::GraphicsLibraryError(SDL_GetError());
	}
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	TTF_Init();
	font = TTF_OpenFont("./res/Walk-Around-the-Block.ttf", 30);
	if (font == nullptr) {
		SDL_Quit();
		throw arcade::GraphicsLibraryError(SDL_GetError());
	}
	change = false;
	switchScene = false;
}

Sdl2::~Sdl2()
{
	for (auto &it : textures) {
		SDL_FreeSurface(it.first);
	}
	textures.clear();
	for (auto &it : texts) {
		SDL_FreeSurface(it.first);
	}
	texts.clear();
	TTF_Quit();
	if (window != nullptr)
		SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

bool	Sdl2::GetKey(arcade::TypeEvent typeEvent, std::string const &currentEvent)
{
	auto	search = allEvent.find(currentEvent);

	if (search == allEvent.end())
		return false;
	if (typeEvent == arcade::WINDOW && search->second == event.window.event)
		return true;
	return search->second == event.key.keysym.scancode;
}

bool	Sdl2::isKey()
{
	if (!finish)
		return false;
	return SDL_PollEvent(&event) != 0;
}

bool	Sdl2::isOpen()
{
	return finish;
}

bool	Sdl2::Display()
{
	SDL_Rect	rect;

	SDL_FillRect(windowSurface, nullptr, SDL_MapRGB(windowSurface->format, 0, 0, 0));
	for (auto const &it : textures) {
		rect.x = it.second.x;
		rect.y = it.second.y;
		rect.w = it.first->w;
		rect.h = it.first->h;
		SDL_BlitSurface(it.first, nullptr, windowSurface, &rect);
	}
	for (auto const &text : texts) {
		rect.x = text.second.x;
		rect.y = text.second.y;
		rect.w = text.first->w;
		rect.h = text.first->h;
		SDL_BlitSurface(text.first, nullptr, windowSurface, &rect);
	}
	SDL_UpdateWindowSurface(window);
	return true;
}

void	Sdl2::destroyWindow()
{
	if (!finish)
		return;
	finish = false;
}

void Sdl2::setEvent(const SDL_Event &event)
{
	Sdl2::event = event;
}

bool Sdl2::loadText(textureList const&text)
{
	SDL_Color	black = {255, 255, 255, 0};
	SDL_Surface	*tmpText;

	if (font == nullptr)
		return false;
	for (auto const &currentText : texts)
		SDL_FreeSurface(currentText.first);
	texts.clear();
	for (auto const &it : text) {
		if (it.second.isFile || !it.second.display)
			continue;
		tmpText = TTF_RenderText_Blended(font, it.second.path.c_str(), black);
		if (tmpText == nullptr)
			continue;
		texts.emplace(std::make_pair(tmpText, (Position){it.second.position.x, it.second.position.y}));
	}
	return true;
}

bool Sdl2::loadTexture(textureList const&toLoad)
{
	SDL_Surface	*tmpTexture;

	for (auto const &it : textures)
		SDL_FreeSurface(it.first);
	textures.clear();
	for (auto const &it : toLoad) {
		if (!it.second.isFile || !it.second.display)
			continue;
		tmpTexture = IMG_Load(it.second.path.c_str());
		if (tmpTexture == nullptr) {
			std::cerr << "Can't load " << it.second.path << std::endl;
			continue;
		}
		textures.emplace(std::make_pair(tmpTexture, (Position){it.second.position.x, it.second.position.y}));
	}
	return true;
}

void Sdl2::changeLibrary(std::string const &path)
{
	change = true;
	newLibraryPath = path;
}

std::string const&	Sdl2::getLibraryPath() const
{
	return newLibraryPath;
}

bool	Sdl2::getChange() const
{
	return change;
}

void	Sdl2::setChange(bool state)
{
	change = state;
}

bool Sdl2::getSwitchScene() const
{
	return switchScene;
}

void	Sdl2::setSwitchScene(bool state)
{
	switchScene = state;
}

std::string const	&Sdl2::getNewGamePath() const
{
	return newGamePath;
}

void Sdl2::setNewGamePath(std::string const &gamePath)
{
	newGamePath = gamePath;
}

bool Sdl2::loadMap(mapChar const &map)
{
	(void)map;
	return false;
}
