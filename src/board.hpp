/*
	CS 202 Group Project
	Connect4 Board Game made with SFML

	Members: Robert Lawton, Andrew Player,
	Jadon Nashoanak, Jordan Day, Jared Maltos

	12/3/2019
	Professor Hartman
*/
#ifndef _BOARD_HPP_
#define _BOARD_HPP_

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Board {

public:

	sf::RenderWindow* window;
	bool currentPlayer;
	int filledPlaces;
	sf::Color playerOneColor;
	sf::Color playerTwoColor;

	Board(sf::RenderWindow* window)
		: window(window), _places(), currentPlayer(true) {
		playerOneColor = sf::Color (255 ,51 ,51);
		playerTwoColor = sf::Color(51, 51, 255);
		filledPlaces = 0;
	}

	void initBoard();
	int getLowestPlace(int column);
	bool isOccupied(sf::Color playerColor, int row, int column);
	bool checkForWinner(sf::Color playerColor);
	bool checkForWinner(int row, int col);
	bool checkForDraw();
	sf::Vector2f getPlacePosition(int row, int column);
	int getColumnFromPos(float mPos);
	bool isColumnFull(int column);
	void setColor(int row, int column, sf::Color color);
	void drawBoard();
	int getNumberOfRows() { return _rows; }
	int getNumberOfColumns() { return _cols; }

private:
	std::vector<std::vector<sf::CircleShape>> _places;
	int _rows = 6;
	int _cols = 7;
};

int connectFourGame();

#endif
