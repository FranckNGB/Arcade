/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by asianpw,
*/

#ifndef CPP_ARCADE_ARCADEEXCEPTION_HPP
#define CPP_ARCADE_ARCADEEXCEPTION_HPP

#include <string>
#include <stdexcept>

namespace arcade {
	class Error : public std::exception {
	public:
		explicit Error(std::string const &e) noexcept : message(e) {};
		const char *what() const noexcept override { return message.what(); };
	protected:
		std::runtime_error message;
	};

	class LoaderError : public Error {
	public:
		explicit LoaderError(std::string const &e) noexcept : Error(e) {};
	};

	class GraphicsLibraryError : public Error {
	public:
		explicit GraphicsLibraryError(std::string const &e) noexcept : Error(e) {};
	};

	class CoreError : public Error {
	public:
		explicit CoreError(std::string const &e) noexcept : Error(e) {};
	};
}

#endif //CPP_ARCADE_ARCADEEXCEPTION_HPP
