//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Nibbler.hpp
//

#ifndef CPP_ARCADE_NIBBLER_HPP
#define CPP_ARCADE_NIBBLER_HPP

#include "../../../inc/IGame.hpp"

class Nibbler : public IGame {
public:
	Nibbler();
	~Nibbler() override = default;
	IScene	*start() override;

public:
	std::string const &getName() const override;
	std::string const &getDescription() const override;
};

#endif //CPP_ARCADE_NIBBLER_HPP
