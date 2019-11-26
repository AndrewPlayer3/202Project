#include "board.hpp"
#include <iostream>

int getColumnFromPos(float mPos, Board& board) {
	int col = -1;
	for (int i = 0; i < 7; i++) {
		if (i == 0
			&& mPos < board.getPlacePosition(0, 1).x
			&& !board.isColumnFull(0)) {
			col = 0;
		}
		else if (i == 6
			&& mPos > board.getPlacePosition(0, 6).x
			&& !board.isColumnFull(6)) {
			col = 6;
		}
		else if (i < 6 && mPos < board.getPlacePosition(0, i + 1).x
			&& mPos > board.getPlacePosition(0, i).x
			&& !board.isColumnFull(i)) {
			col = i;
		}
	}
	return col;
}

int connectFourGame() {

	int windowHeight = 900;
	int windowWidth = 1100;

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Connect4!");
	window.setKeyRepeatEnabled(false);
	Board board(&window);
	board.initBoard();

	sf::Font font;
	font.loadFromFile("resrcs/consola.ttf");

	sf::Text currentPlayerStatus;
	currentPlayerStatus.setCharacterSize(30.f);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left) {
			float mPos = sf::Mouse::getPosition(window).x;
			int col = getColumnFromPos(mPos, board);
			if (col == -1) {
				event.type = sf::Event::KeyPressed;
				continue;
			}
			int row = board.getLowestPlace(col);
			if (board.currentPlayer) {
				board.setColor(row, col, sf::Color::Red);
				currentPlayerStatus = { std::string("Player: 1"), font, 50 };
			}
			else {
				board.setColor(row, col, sf::Color::Blue);
				currentPlayerStatus = { std::string("Player: 2"), font, 50 };
			}
			event.type = sf::Event::KeyPressed;
			board.currentPlayer = !board.currentPlayer;
		}

		currentPlayerStatus.setOutlineThickness(2.f);
		currentPlayerStatus.setOutlineColor(sf::Color::Black);
		currentPlayerStatus.setPosition(100.f, 10);

		window.clear(sf::Color::Cyan);
		window.draw(currentPlayerStatus);
		board.drawBoard();
		window.display();
	}

	return 0;
}