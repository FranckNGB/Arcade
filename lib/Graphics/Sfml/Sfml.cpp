/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by asianpw,
*/

#include <SFML/Window.hpp>
#include <iostream>
#include "../../../inc/Sfml.hpp"
#include "../../../inc/Alias.hpp"
#include "../../../inc/ArcadeException.hpp"

SfmlDisplay::SfmlDisplay(size_t w, size_t h) : width(w), height(h), alreadyLoad(false)
{
	if (w > 1920 || h > 1080)
		throw arcade::GraphicsLibraryError("SFML: Size are too big");
	window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width,height), "SFML");
	if (window == nullptr) {
		throw arcade::GraphicsLibraryError("SFML: Unable to init window");
	}
	allEvent.insert({arcade::CLOSE, sf::Event::Closed});
	allEvent.insert({arcade::ESCAPE,sf::Keyboard::Escape});
	allEvent.insert({arcade::UP,sf::Keyboard::Up});
	allEvent.insert({arcade::DOWN,sf::Keyboard::Down});
	allEvent.insert({arcade::LEFT,sf::Keyboard::Left});
	allEvent.insert({arcade::RIGHT,sf::Keyboard::Right});
	allEvent.insert({arcade::ENTER, sf::Keyboard::Return});
	allEvent.insert({arcade::Q, sf::Keyboard::Q});
	allEvent.insert({arcade::M, sf::Keyboard::M});
	change = false;
	switchScene = false;
}

SfmlDisplay::~SfmlDisplay()
{
}

bool	SfmlDisplay::Display()
{
	window->clear();
	for (auto const &it : sprites)
		window->draw(it.second);
	for (auto const &it : texts)
		window->draw(it);
	window->display();
	return true;
}

bool	SfmlDisplay::isKey()
{
	return window->pollEvent(event);
}

bool	SfmlDisplay::isOpen()
{
	return window->isOpen();
}

bool	SfmlDisplay::GetKey(arcade::TypeEvent typeEvent, std::string const &currentEvent)
{
	auto	search = allEvent.find(currentEvent);

	if (search == allEvent.end())
		return false;
	if (typeEvent == arcade::WINDOW && event.type == search->second)
		return true;
	if (event.type == sf::Event::KeyPressed && event.key.code == search->second)
		return true;
	return false;
}

void	SfmlDisplay::destroyWindow()
{
	window->close();
}

void	SfmlDisplay::setEvent(sf::Event &newEvent)
{
	event = newEvent;
}

bool SfmlDisplay::loadTexture(textureList const &texture)
{
	sf::Texture	newTexture;

	textures.clear();
	sprites.clear();
	for (auto const &it : texture) {
		if (it.second.isFile && it.second.display && newTexture.loadFromFile(it.second.path)) {
			sf::Sprite	newSprite;

			textures.emplace_back(newTexture);
			newSprite.setTexture(textures.back());
			newSprite.setPosition(it.second.position.x, it.second.position.y);
			sprites.emplace(std::make_pair(it.first, newSprite));
		}
	}
	return true;
}

bool SfmlDisplay::loadText(textureList const &text)
{
	sf::Text	newText;

	texts.clear();
	if (!font.loadFromFile("./res/Walk-Around-the-Block.ttf"))
		return false;
	for (auto const &it : text) {
		if (!it.second.isFile && it.second.display) {
			newText.setString(it.second.path);
			newText.setFont(font);
			newText.setPosition(it.second.position.x, it.second.position.y);
			texts.emplace_back(newText);
		}
	}
	return true;
}

void SfmlDisplay::changeLibrary(std::string const &path)
{
	change = true;
	newLibraryPath = path;
}

bool SfmlDisplay::getChange() const
{
	return change;
}

std::string const& SfmlDisplay::getLibraryPath() const
{
	return newLibraryPath;
}

void SfmlDisplay::setChange(bool state)
{
	change = state;
}

bool SfmlDisplay::getSwitchScene() const
{
	return switchScene;
}

void SfmlDisplay::setSwitchScene(bool state)
{
	switchScene = state;
}

void SfmlDisplay::setNewGamePath(std::string const &gamePath)
{
	newGamePath = gamePath;
}

std::string const	&SfmlDisplay::getNewGamePath() const
{
	return newGamePath;
}

bool SfmlDisplay::loadMap(mapChar const &map)
{
	(void)map;
	return false;
}
