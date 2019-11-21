#include "Token.hpp"
#include <SFML/Graphics.hpp>

Token::Token() : _player(0) {};

auto Token::getColor(){
	if (_player == 1) {
		return sf::Color::White;
	}
	else if (_player == 2) {
		return sf::Color::Red;
	}
	else if (_player == 0) {
		return sf::Color::Black;
	}
}