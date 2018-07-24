//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// NibblerScene.hpp
//

#ifndef CPP_ARCADE_NIBBLERSCENE_HPP
#define CPP_ARCADE_NIBBLERSCENE_HPP

#include "../../../inc/IScene.hpp"
#include "../../../inc/Texture.hpp"
#include "Nibbler.hpp"

struct	Direction {
	Position	up = {0, -1};
	Position	left = {-1, 0};
	Position	down = {0, 1};
	Position	right = {1, 0};
};

static const size_t WIDTH_TEXTURE = 20;
static const size_t HEIGHT_TEXTURE = 20;

class NibblerScene : public IScene{
public:
	NibblerScene();
	~NibblerScene() override = default;
	void	sceneEvent(IDisplay *) override ;
	textureList	getTexture() const override ;
	textureList	getText() const override ;
	void	compute() override;
	void	eatAndGrow();
	mapChar	getMap() const override;
	void	showMap();
	void	snakeMove();
	void	createCandy();
	void	createMap();
	void	createSnake();
private:
	textureList	nibblerTexture;
	textureList	nibblerText;
	std::vector<Position>		nibblerBody;
	mapChar	nibblerMap;
	int				score;
	Direction			direction;
	Position			move;
	Position			candy;
	static const int		WIDTH = 30;
	static const int		HEIGHT = 20;
	long				currentTime;
	bool				keyOk;
	bool				play;
};

#endif //CPP_ARCADE_NIBBLERSCENE_HPP
