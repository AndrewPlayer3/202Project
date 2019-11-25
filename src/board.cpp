#include "board.hpp"

void Board::initBoard() {
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

int Board::getLowestPlace(int column) {
	for (int row = 0; row < _rows; row++) {
		if (_places[row][column].getFillColor() == sf::Color::White) {
			if ((row == _rows - 1) || (_places[row + 1][column].getFillColor() != sf::Color::White)) {
				return row;
			}
		}
	}
}

bool Board::isOccupied(sf::Color playerColor, int row, int column) {
	if (_places[row][column].getFillColor() == playerColor) {
		return true;
	}
	return false;
}

sf::Vector2f Board::getPlacePosition(int row, int column) {
	return _places[row][column].getPosition();
}

bool Board::checkForWinner() {
	//Winning Logic
	return true;
}

bool Board::isColumnFull(int column) {
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