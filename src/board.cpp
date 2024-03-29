/*
	CS 202 Group Project
	Connect4 Board Game made with SFML

	Members: Robert Lawton, Andrew Player,
	Jadon Nashoanak, Jordan Day, Jared Maltos

	12/3/2019
	Professor Hartman
*/
#include "board.hpp"

void Board::initBoard() { //Creates Board
	for (int row = 0; row < _rows; row++) {
		_places.push_back(std::vector<sf::CircleShape>(_cols));
		for (int col = 0; col < _cols; col++) {
			sf::CircleShape place(50.f);
			place.setFillColor(sf::Color::White);
			place.setPosition(100 + col * 130.f, 100 + row * 130.f);
			_places[row][col] = place;
		}
	}
}

int Board::getLowestPlace(int column) {	//Finds the lowest spot for chip to drop
	if (column < _cols) {
		for (int row = 0; row < _rows; row++) {
			if (_places[row][column].getFillColor() == sf::Color::White) {
				if ((row == _rows - 1) || (_places[row + 1][column].getFillColor() != sf::Color::White)) {
					return row;
				}
			}
		}
	}
}

bool Board::isOccupied(sf::Color playerColor, int row, int column) { //Indicates whether or not spot is filled
	if (_places[row][column].getFillColor() == playerColor) {
		return true;
	}
	return false;
}

sf::Vector2f Board::getPlacePosition(int row, int column) { //Determines positioning
	return _places[row][column].getPosition();
}


bool Board::checkForWinner(sf::Color playerColor) { //Checks for four pieces in a row.
	int count = 0;
	// Rows
	for (int row = 0; row < _rows; row++) {
		for (int col = 0; col < _cols; col++) {
			if (_places[row][col].getFillColor() == playerColor)
				count++;
			else count = 0;
			if (count == 4) return true;
		}
		count = 0;
	}
	// Columns
	for (int col = 0; col < _cols; col++) {
		for (int row = 0; row < _rows; row++) {
			if (_places[row][col].getFillColor() == playerColor)
				count++;
			else count = 0;
			if (count == 4) return true;
		}
		count = 0;
	}
	// Right Diagonals
	for (int row = 3; row < _rows; row++) {
		for (int col = 0; col < _cols - 3; col++) {
			int currentCol = col;
			bool breakIf = false;
			for (int currentRow = row; currentRow >= 0 && !breakIf; currentRow--) {
				if (_places[currentRow][currentCol].getFillColor() == playerColor)
					count++;
				else count = 0;
				if (count == 4) return true;
				if (currentCol == _cols - 1) breakIf = true;
				else currentCol++;
			}
			count = 0;
		}
	}
	// Left Diagonals
	for (int row = 3; row < _rows; row++) {
		for (int col = _cols - 1; col > 2; col--) {
			int currentCol = col;
			bool breakIf = false;
			for (int currentRow = row; currentRow >= 0 && !breakIf; currentRow--) {
				if (_places[currentRow][currentCol].getFillColor() == playerColor)
					count++;
				else count = 0;
				if (count == 4) return true;
				if (currentCol == 0) breakIf = true;
				else currentCol--;
			}
			count = 0;
		}
	}
	return false;
}

bool Board::checkForDraw() {	//If the board is entirely filled
	int fullCount = 0;
	for (int col = 0; col < _cols; col++) {
		if (isColumnFull(col)) fullCount++;
	}
	if (fullCount == _cols) return true;
	return false;
}

bool Board::isColumnFull(int column) {	//Checks for full column
	if (_places[0][column].getFillColor() != sf::Color::White) {
		return true;
	}
	return false;
}

void Board::setColor(int row, int column, sf::Color color) {		
	if (row < _rows && column < _cols) {
		_places[row][column].setFillColor(color);
	}
	else {
		std::cout << "Vector Indices Out of Range: " << row << ", " << column << std::endl;
	}
}

void Board::drawBoard() {
	for (int row = 0; row < _rows; row++) {
		for (int col = 0; col < _cols; col++) {
			window->draw(_places[row][col]);
		}
	}
}

int Board::getColumnFromPos(float mPos) { //Tracks mouse click over column, returns column
	int col = -1;
	for (int i = 0; i < 7; i++) {
		if (i == 0
			&& mPos < getPlacePosition(0, 1).x
			&& !isColumnFull(0)) {
			col = 0;
		}
		else if (i == _cols - 1
			&& mPos > getPlacePosition(0, _cols - 1).x
			&& !isColumnFull(_cols - 1)) {
			col = _cols - 1;
		}
		else if (i < _cols - 1 && mPos < getPlacePosition(0, i + 1).x
			&& mPos > getPlacePosition(0, i).x
			&& !isColumnFull(i)) {
			col = i;
		}
	}
	return col;
}
