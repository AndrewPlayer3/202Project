#ifndef _BOARD_HPP_
#define _BOARD_HPP_

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

	void initBoard();
	int getLowestPlace(int column);
	bool isOccupied(sf::Color playerColor, int row, int column);
	bool checkForWinner();
	bool isColumnFull(int column);
	void setColor(int row, int column, sf::Color color);
	void drawBoard();

private:
	int _rows = 6;
	int _cols = 7;
};

int connectFourGame();

#endif
