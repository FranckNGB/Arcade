//
// EPITECH PROJECT, 2018
// PacmanScene
// File description:
// source file
//

#include "PacmanScene.hpp"
#include <chrono>
#include <iostream>
#include <fstream>
#include <cstring>
#include "../../../inc/Time.hpp"

void    PacmanScene::print_map()
{
	std::cout<<"*******************************************************"<<std::endl;
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 29; j++)
			std::cout<<pacmanMap[i][j];
	std::cout<<std::endl<<"*******************************************************"<<std::endl;
}

void    PacmanScene::createMap(void)
{
	pacmanMap.resize(HEIGHT, std::vector<char>(WIDTH));
	pacmanMap = {
            {'\n','k','-','-','-','-','-','-','-','-','-','-','-','-','!','-','-','-','-','-','-','-','-','-','-','-','-','-','m'},
            {'\n','|','b','o','o','o','o','o','o','o','o','o','o','o','|','o','o','o','o','o','o','o','o','o','o','o','o','b','|'},
            {'\n','|','o','1','5','2','o','<','-','!','-','%','o','o','$','o','o','<','-','!','-','%','o','o','1','5','2','o','|'},
            {'\n','|','o','3','6','4','o','o','o','$','o','o','o','o','o','o','o','o','o','$','o','o','o','o','3','6','4','o','|'},
            {'\n','|','o','o','o','o','o','.','o','o','o','<','-','-','!','-','-','%','o','o','o','.','o','o','o','o','o','o','|'},
            {'\n','l','-','-','m','b','o','|','o','o','o','o','o','o','$','o','o','o','o','o','o','|','o','o','o','k','-','-','n'},
            {'\n',' ',' ',' ','|','o','o','*','-','%',' ',' ',' ',' ',' ',' ',' ',' ',' ','<','-','=','o','o','o','|',' ',' ',' '},
            {'\n',' ',' ',' ','|','o','o','|','o','o',' ','k','-','%',' ','<','-','m',' ','o','o','|','o','o','o','|',' ',' ',' '},
            {'\n','-','-','-','n','o','o','$','o','o',' ','|',' ',' ',' ',' ',' ','|',' ','o','o','$','o','o','o','l','-','-','-'},
            {'\n',' ','o','o','o','o','o','o','o','o',' ','|',' ',' ',' ',' ',' ','|',' ','o','o','o','o','o','o','o','o','o',' '},
            {'\n','-','-','-','m','o','o','.','o','o',' ','l','-','-','-','-','-','n',' ','o','o','.','o','o','o','k','-','-','-'},
            {'\n',' ',' ',' ','|','o','o','|','o','o',' ',' ',' ',' ',' ',' ',' ',' ',' ','o','o','|','o','o','o','|',' ',' ',' '},
            {'\n',' ',' ',' ','|','o','o','|','o','o',' ','<','-','-','!','-','-','%',' ','o','o','|','o','o','o','|',' ',' ',' '},
            {'\n','k','-','-','n','o','o','$','o','o',' ',' ',' ',' ','|',' ',' ',' ',' ','o','o','$','o','o','o','l','-','-','m'},
            {'\n','|','b','o','o','o','o','o','o','o','o','o','o','o','$','o','o','o','o','o','o','o','o','o','o','o','o','b','|'},
            {'\n','|','o','o','<','m','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','k','%','o','o','|'},
            {'\n','*','%','o','o','$','o','o','o','.','o','<','-','-','!','-','-','%','o','o','o','.','o','o','$',' ','o','<','='},
            {'\n','|','o','o','o','o','o','o','o','|','o','o','o','o','|','o','o','o','o','o','o','|','o','o','o','o','o','o','|'},
            {'\n','|','o','o','o','<','-','-','-','?','-','%','o','o','$','o','o','<','-','-','-','?','-','-','%',' ','o','o','|'},
            {'\n','|','b','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','b','|'},
            {'\n','l','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','n'}
	};
}

PacmanScene::PacmanScene() : pacmanMap(WIDTH, std::vector<char>(HEIGHT))
{
	size_t  x = 0;
	size_t  y = 0;

	createMap();
	SetCharacters();
	score = 0;
	nbr_food = get_nbrfood();
	PacmanText.insert({"score_value", {std::to_string(score), ' ', false, true, {150, 565}}});
	PacmanText.insert({"title", {"Score :", ' ', false, true, {20, 565}}});
	PacmanText.insert({"food_value", {std::to_string(nbr_food), ' ', false, true, {540, 565}}});
	PacmanText.insert({"title_food", {"Remaining food :", ' ', false, true, {240, 565}}});
    PacmanText.insert({"title_life", {"Life : ", ' ', false, true, {610, 565}}});
    PacmanText.insert({"life_value", {std::to_string(life), ' ', false, true, {690, 565}}});
    print_map();
	for (auto const &line : pacmanMap) {
		x = 0;
		for (auto const &block : line) {
			if (block == 'k')
				PacmanTexture.insert({"wall" + std::to_string(y) + std::to_string(x), (Texture){"./res/Wall/Default/003.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == 'l')
				PacmanTexture.insert({"wall" + std::to_string(y) + std::to_string(x), (Texture){"./res/Wall/Default/021.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == 'm')
				PacmanTexture.insert({"wall" + std::to_string(y) + std::to_string(x), (Texture){"./res/Wall/Default/005.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == 'n')
				PacmanTexture.insert({"wall" + std::to_string(y) + std::to_string(x), (Texture){"./res/Wall/Default/023.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == '-')
				PacmanTexture.insert({"wall" + std::to_string(y) + std::to_string(x), (Texture){"./res/Wall/Default/008.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == '|')
				PacmanTexture.insert({"wall" + std::to_string(y) + std::to_string(x), (Texture){"./res/Wall/Default/016.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == '!')
                PacmanTexture.insert({"wall" + std::to_string(y) + std::to_string(x), (Texture){"./res/Wall/Default/004.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == '$')
                PacmanTexture.insert({"wall" + std::to_string(y) + std::to_string(x), (Texture){"./res/Wall/Default/024.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == '*')
                PacmanTexture.insert({"wall" + std::to_string(y) + std::to_string(x), (Texture){"./res/Wall/Default/013.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == '%')
                PacmanTexture.insert({"wall" + std::to_string(y) + std::to_string(x), (Texture){"./res/Wall/Default/009.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == '=')
                PacmanTexture.insert({"wall" + std::to_string(y) + std::to_string(x), (Texture){"./res/Wall/Default/015.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == '<')
                PacmanTexture.insert({"wall" + std::to_string(y) + std::to_string(x), (Texture){"./res/Wall/Default/007.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == '?')
                PacmanTexture.insert({"wall" + std::to_string(y) + std::to_string(x), (Texture){"./res/Wall/Default/022.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == '.')
                PacmanTexture.insert({"wall" + std::to_string(y) + std::to_string(x), (Texture){"./res/Wall/Default/006.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == 'O')
                PacmanTexture.insert({"wall" + std::to_string(y) + std::to_string(x), (Texture){"./res/Wall/Default/017.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == '1')
                PacmanTexture.insert({"wall" + std::to_string(y) + std::to_string(x), (Texture){"./res/Wall/Default/000.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == '2')
                PacmanTexture.insert({"wall" + std::to_string(y) + std::to_string(x), (Texture){"./res/Wall/Default/002.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == '3')
                PacmanTexture.insert({"wall" + std::to_string(y) + std::to_string(x), (Texture){"./res/Wall/Default/018.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == '4')
                PacmanTexture.insert({"wall" + std::to_string(y) + std::to_string(x), (Texture){"./res/Wall/Default/020.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == '5')
                PacmanTexture.insert({"wall" + std::to_string(y) + std::to_string(x), (Texture){"./res/Wall/Default/001.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == '6')
                PacmanTexture.insert({"wall" + std::to_string(y) + std::to_string(x), (Texture){"./res/Wall/Default/019.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
            else if (block == '_')
                PacmanTexture.insert({"wall" + std::to_string(y) + std::to_string(x), (Texture){"./res/barre.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
            else if (block == 'G')
				PacmanTexture.insert({"player", {"./res/PacMan/Default/000.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == 'o')
				PacmanTexture.insert({"food" + std::to_string(y) + std::to_string(x), (Texture){"./res/Food/Dot/Default/000.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == 'b')
                PacmanTexture.insert({"bigfood" + std::to_string(y) + std::to_string(x), (Texture){"./res/Food/BigDot/Default/000.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
            else if (block == 'B')
				PacmanTexture.insert({"gosht2", {"./res/Ghost/Inky0/000.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == 'C')
				PacmanTexture.insert({"gosht3", {"./res/Ghost/Blinky0/000.png", ' ', true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
            else if (block == 'P')
                PacmanTexture.insert({"gosht4", {"./res/Ghost/Pinky0/000.png", ' ', true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
            else if (block == 'Y')
                PacmanTexture.insert({"gosht5", {"./res/Ghost/Clyde90/000.png", ' ', true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			x = x + 1;
		}
		y = y + 1;
	}
}

void    PacmanScene::SetCharacters(void)
{
	player.x = 11;
	player.y = 14;
	gosht2.x = 9;
	gosht2.y = 13;
	gosht3.x = 9;
	gosht3.y = 14;
	gosht4.x = 9;
	gosht4.y = 15;
	gosht5.x = 8;
	gosht5.y = 14;
	pacmanMap[gosht2.x][gosht2.y] = 'B';
	pacmanMap[gosht3.x][gosht3.y] = 'C';
    pacmanMap[gosht4.x][gosht4.y] = 'P';
    pacmanMap[gosht5.x][gosht5.y] = 'Y';
    pacmanMap[player.x][player.y] = 'G';
}

std::map<std::string, Texture>  PacmanScene::getTexture() const
{
	return PacmanTexture;
}

std::map<std::string, Texture>  PacmanScene::getText() const
{
	return PacmanText;
}

void    PacmanScene::sceneEvent(IDisplay *display)
{
	if (display->GetKey(arcade::KEYBOARD, arcade::CLOSE)) {
		display->destroyWindow();
	}
	if (display->GetKey(arcade::KEYBOARD, arcade::ESCAPE)) {
		display->destroyWindow();
	}
	if (display->GetKey(arcade::KEYBOARD, arcade::LEFT)) {
		way = 0;
		if (loose == true || win == true) {
			PacmanText.insert({"goMenu", {"Press Enter to go to the menu", ' ', false, true, {200, 340}}});
			exit(0);
		}
		Move_left();
		PacmanTexture.erase("player");
		PacmanTexture.insert({"player", {"./res/PacMan/A180/000.png", ' ',  true, true, {(int)(player.y * WIDTH_TEXTURE), (int)(player.x * HEIGHT_TEXTURE)}}});
	}
	if (display->GetKey(arcade::KEYBOARD, arcade::RIGHT)) {
		way = 1;
		if (loose == true || win == true) {
		    PacmanText.insert({"goMenu", {"Press Enter to go to the menu", ' ', false, true, {200, 340}}});
		    exit(0);
		}
		Move_right();
		PacmanTexture.erase("player");
		PacmanTexture.insert({"player", {"./res/PacMan/A0/000.png", ' ',  true, true, {(int)(player.y * WIDTH_TEXTURE), (int)(player.x * HEIGHT_TEXTURE)}}});
	}
	if (display->GetKey(arcade::KEYBOARD, arcade::UP)) {
		way = 2;
		if (loose == true || win == true) {
			exit(0);
		}
		Move_up();
		PacmanTexture.erase("player");
		PacmanTexture.insert({"player", {"./res/PacMan/A270/000.png", ' ',  true, true, {(int)(player.y * WIDTH_TEXTURE), (int)(player.x * HEIGHT_TEXTURE)}}});
	}
	if (display->GetKey(arcade::KEYBOARD, arcade::DOWN)) {
		way = 3;
		Move_down();
		PacmanTexture.erase("player");
		PacmanTexture.insert({"player", {"./res/PacMan/A90/000.png", ' ',  true, true, {(int)(player.y * WIDTH_TEXTURE), (int)(player.x * HEIGHT_TEXTURE)}}});
	}
}

void    PacmanScene::Move_right(void)
{
	if (isWall(player.x, player.y + 1))
		return;
	if (pacmanMap[player.x][player.y + 1] == 'o') {
		score += 10;
		nbr_food--;
		PacmanTexture.erase("food" + std::to_string(player.x) + std::to_string(player.y + 1));
		PacmanText["score_value"].path = std::to_string(score);
		PacmanText["food_value"].path = std::to_string(nbr_food);
	}
    if (pacmanMap[player.x][player.y + 1] == 'b') {
        score += 50;
        nbr_food--;
        PacmanTexture.erase("bigfood" + std::to_string(player.x) + std::to_string(player.y + 1));
        PacmanText["score_value"].path = std::to_string(score);
        PacmanText["food_value"].path = std::to_string(nbr_food);
    }
	player.y++;
	PacmanTexture["player"].position.x += WIDTH_TEXTURE;
	if (pacmanMap[player.x][player.y] == 'B' || pacmanMap[player.x][player.y] == 'C'
	|| pacmanMap[player.x][player.y] == 'Y' || pacmanMap[player.x][player.y] == 'P') {
        life--;
		pacmanMap[player.x][player.y] = ' ';
		player.x = 11;
		player.y = 14;
		pacmanMap[player.x][player.y] = 'G';
        PacmanTexture.erase("player");
        PacmanTexture.insert({"player", {"./res/PacMan/A0/001.png", ' ',  true, true, {(int)(player.y * WIDTH_TEXTURE), (int)(player.x * HEIGHT_TEXTURE)}}});
	}
    if (player.y == 29) {
        player.y = 1;
        PacmanTexture.erase("player");
        PacmanTexture.insert({"player", {"./res/PacMan/A0/001.png", ' ',  true, true, {(int)(player.y * WIDTH_TEXTURE), (int)(player.x * HEIGHT_TEXTURE)}}});
    }
	if (nbr_food == 0) {
		PacmanText.insert({"lost", {"You Won", ' ', false, true, {300, 280}}});
		win = true;
	}
	pacmanMap[player.x][player.y] = 'G';
	pacmanMap[player.x][player.y - 1] = ' ';
}

void    PacmanScene::Move_left(void)
{
	if (isWall(player.x, player.y - 1))
		return;
	if (pacmanMap[player.x][player.y - 1] == 'o') {
		score += 10;
		nbr_food--;
		PacmanTexture.erase("food" + std::to_string(player.x) + std::to_string(player.y - 1));
		PacmanText["score_value"].path = std::to_string(score);
		PacmanText["food_value"].path = std::to_string(nbr_food);
	}
    if (pacmanMap[player.x][player.y - 1] == 'b') {
        score += 50;
        nbr_food--;
        PacmanTexture.erase("bigfood" + std::to_string(player.x) + std::to_string(player.y - 1));
        PacmanText["score_value"].path = std::to_string(score);
        PacmanText["food_value"].path = std::to_string(nbr_food);
    }
	player.y--;
	PacmanTexture["player"].position.x -= WIDTH_TEXTURE;
	if (pacmanMap[player.x][player.y] == 'C' || pacmanMap[player.x][player.y] == 'B'
	|| pacmanMap[player.x][player.y] == 'Y' || pacmanMap[player.x][player.y] == 'P') {
		life--;
		pacmanMap[player.x][player.y] = ' ';
		player.x = 11;
		player.y = 14;
		pacmanMap[player.x][player.y] = 'G';
        PacmanTexture.erase("player");
        PacmanTexture.insert({"player", {"./res/PacMan/A180/001.png", ' ',  true, true, {(int)(player.y * WIDTH_TEXTURE), (int)(player.x * HEIGHT_TEXTURE)}}});
	}
	if (player.y == 0) {
        player.y = 28;
        pacmanMap[player.x][player.y] = 'G';
        PacmanTexture.erase("player");
        PacmanTexture.insert({"player", {"./res/PacMan/A180/001.png", ' ',  true, true, {(int)(player.y * WIDTH_TEXTURE), (int)(player.x * HEIGHT_TEXTURE)}}});
	}
	if (nbr_food == 0) {
		PacmanText.insert({"lost", {"You Won", ' ', false, true, {300, 280}}});
		win = true;
	}
	pacmanMap[player.x][player.y] = 'G';
	pacmanMap[player.x][player.y + 1] = ' ';
}

void    PacmanScene::Move_up(void)
{
	if (isWall(player.x - 1, player.y))
		return;
	if (pacmanMap[player.x - 1][player.y] == 'o') {
		score += 10;
		nbr_food--;
		PacmanTexture.erase("food" + std::to_string(player.x - 1) + std::to_string(player.y));
		PacmanText["score_value"].path = std::to_string(score);
		PacmanText["food_value"].path = std::to_string(nbr_food);
	}
    if (pacmanMap[player.x - 1][player.y] == 'b') {
        score += 50;
        nbr_food--;
        PacmanTexture.erase("bigfood" + std::to_string(player.x - 1) + std::to_string(player.y));
        PacmanText["score_value"].path = std::to_string(score);
        PacmanText["food_value"].path = std::to_string(nbr_food);
    }
	player.x--;

	PacmanTexture["player"].position.y -= HEIGHT_TEXTURE;
	if (pacmanMap[player.x][player.y] == 'C' || pacmanMap[player.x][player.y] == 'B'
	|| pacmanMap[player.x][player.y] == 'Y' || pacmanMap[player.x][player.y] == 'P') {
        life--;
		pacmanMap[player.x][player.y] = ' ';
		player.x = 11;
		player.y = 14;
		pacmanMap[player.x][player.y] = 'G';
        PacmanTexture.erase("player");
        PacmanTexture.insert({"player", {"./res/PacMan/A270/001.png", ' ',  true, true, {(int)(player.y * WIDTH_TEXTURE), (int)(player.x * HEIGHT_TEXTURE)}}});
	}
	if (nbr_food == 0) {
		PacmanText.insert({"lost", {"You Won", ' ', false, true, {300, 280}}});
		win = true;
	}
	pacmanMap[player.x][player.y] = 'G';
	pacmanMap[player.x + 1][player.y] = ' ';
}

void    PacmanScene::Move_down(void)
{
	if (isWall(player.x + 1, player.y) || player.x > 21)
		return;
	if (pacmanMap[player.x + 1][player.y] == 'o') {
		score += 10;
		nbr_food--;
		PacmanTexture.erase("food" + std::to_string(player.x + 1) + std::to_string(player.y));
		PacmanText["score_value"].path = std::to_string(score);
		PacmanText["food_value"].path = std::to_string(nbr_food);
	}
    if (pacmanMap[player.x + 1][player.y] == 'b') {
        score += 50;
        nbr_food--;
        PacmanTexture.erase("bigfood" + std::to_string(player.x + 1) + std::to_string(player.y));
        PacmanText["score_value"].path = std::to_string(score);
        PacmanText["food_value"].path = std::to_string(nbr_food);
    }
	player.x++;

	PacmanTexture["player"].position.y += HEIGHT_TEXTURE;
	if (pacmanMap[player.x][player.y] == 'C' || pacmanMap[player.x][player.y] == 'B'
	|| pacmanMap[player.x][player.y] == 'Y' || pacmanMap[player.x][player.y] == 'P') {
        life--;
		pacmanMap[player.x][player.y] = ' ';
		player.x = 11;
		player.y = 14;
		pacmanMap[player.x][player.y] = 'G';
        PacmanTexture.erase("player");
        PacmanTexture.insert({"player", {"./res/PacMan/A90/001.png", ' ',  true, true, {(int)(player.y * WIDTH_TEXTURE), (int)(player.x * HEIGHT_TEXTURE)}}});
	}
	if (nbr_food == 0) {
		PacmanText.insert({"lost", {"You Won", ' ', false, true, {300, 280}}});
		win = true;
	}
	pacmanMap[player.x][player.y] = 'G';
	pacmanMap[player.x - 1][player.y] = ' ';
}

int PacmanScene::get_nbrfood(void)
{
	nbr_food = 0;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 26; j++) {
			if (pacmanMap[i][j] == 'o' || pacmanMap[i][j] == 'b')
				nbr_food++;
		}
	}
	return nbr_food;
}

bool PacmanScene::isWall(int x, int y) {
    if (pacmanMap[x][y] == '|' || pacmanMap[x][y] == '-' || pacmanMap[x][y] == '*' || pacmanMap[x][y] == 'k' || pacmanMap[x][y] == 'l'
    || pacmanMap[x][y] == 'm' || pacmanMap[x][y] == 'n' || pacmanMap[x][y] == '?' || pacmanMap[x][y] == '!' || pacmanMap[x][y] == '$'
    || pacmanMap[x][y] == '1' || pacmanMap[x][y] == '2' || pacmanMap[x][y] == '3' || pacmanMap[x][y] == '4' || pacmanMap[x][y] == '5'
    || pacmanMap[x][y] == '6' || pacmanMap[x][y] == 'O' || pacmanMap[x][y] == '=' || pacmanMap[x][y] == '%' || pacmanMap[x][y] == '<'
    || pacmanMap[x][y] == '_' || pacmanMap[x][y] == '.') {
        return true;
    }
    return false;
}

void    PacmanScene::compute(void)
{
	long now = getCurrentTime();

	if (now - currentTime > 250) {
		GoshtMove2();
		GoshtMove3();
		if (way == 0) {
            Move_left();
            PacmanTexture.insert({"player", {"./res/PacMan/A180/001.png", ' ',  true, true, {(int)(player.y * WIDTH_TEXTURE), (int)(player.x * HEIGHT_TEXTURE)}}});
        }
		else if (way == 1) {
            Move_right();
            PacmanTexture.insert({"player", {"./res/PacMan/A0/001.png", ' ',  true, true, {(int)(player.y * WIDTH_TEXTURE), (int)(player.x * HEIGHT_TEXTURE)}}});
        }
		else if (way == 2) {
            Move_up();
            PacmanTexture.insert({"player", {"./res/PacMan/A270/001.png", ' ',  true, true, {(int)(player.y * WIDTH_TEXTURE), (int)(player.x * HEIGHT_TEXTURE)}}});
        }
		else if (way == 3) {
            Move_down();
            PacmanTexture.insert({"player", {"./res/PacMan/A90/001.png", ' ',  true, true, {(int)(player.y * WIDTH_TEXTURE), (int)(player.x * HEIGHT_TEXTURE)}}});
        }
        PacmanText["life_value"].path = std::to_string(life);
		if (life < 0) {
			PacmanText.insert({"lost", {"Game Over", ' ', false, true, {300, 280}}});
			loose = true;
		}
		//print_map();
		currentTime = now;
	}
}

std::vector<std::vector<char>>  PacmanScene::getMap() const
{
	return pacmanMap;
}
