#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Board {

public:

	sf::RenderWindow* window;
	std::vector<std::vector<sf::CircleShape>> places;
	bool currentPlayer;

	Board(sf::RenderWindow* window)
		: window(window), places(), currentPlayer(true) {}

	void initBoard() {
		for (int row = 0; row < _rows; row++) {
			places.push_back(std::vector<sf::CircleShape>(_cols));
			for (int col = 0; col < _cols; col++) {
				sf::CircleShape place(50.f);
				place.setFillColor(sf::Color::White);
				place.setPosition(100 + col * 130.f, 100 + row * 130.f);
				places[row][col] = place;
			}
		}
	}

	int getLowestPlace(int column) {
		for (int row = 0; row < _rows; row++) {
			if (places[row][column].getFillColor() == sf::Color::White) {
				if ((row == _rows - 1) || (places[row + 1][column].getFillColor() != sf::Color::White)) {
					return row;
				}
			}
		}
	}

	bool isOccupied(sf::Color playerColor, int row, int column) {
		if (places[row][column].getFillColor() == playerColor) {
			return true;
		}
		return false;
	}

	bool checkForWinner() {
		//Winning Logic
	}

	bool isColumnFull(int column) {
		if (places[0][column].getFillColor() != sf::Color::White) {
			return true;
		}
		return false;
	}

	void setColor(int row, int column, sf::Color color) {
		if (row < _rows && column < _cols) {
			places[row][column].setFillColor(color);
		}
		else {
			std::cout << "Vector Indices Out of Range: " << row << ", " << column << std::endl;
		}
	}

	void drawBoard() {
		for (int row = 0; row < _rows; row++) {
			for (int col = 0; col < _cols; col++) {
				window->draw(places[row][col]);
			}
		}
	}

private:
	int _rows = 6;
	int _cols = 7;
};

int connectFourGame();

#endif
