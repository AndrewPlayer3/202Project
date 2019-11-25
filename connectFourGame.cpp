#include "src/game.hpp"
#include <iostream>

int connectFourGame() {

	int windowHeight = 900;
	int windowWidth = 1100;

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Connect4!");
	window.setKeyRepeatEnabled(false);
	Board board(&window);
	board.initBoard();

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
			int col = -1;
			for (int i = 0; i < 7; i++) {
				if (i == 0
					&& mPos < board.places[0][1].getPosition().x
					&& !board.isColumnFull(0)) {
					col = 0;
				}
				else if (i == 6
					&& mPos > board.places[0][6].getPosition().x
					&& !board.isColumnFull(6)) {
					col = 6;
				}
				else if( i < 6 && mPos < board.places[0][i+1].getPosition().x
					&& mPos > board.places[0][i].getPosition().x
					&& !board.isColumnFull(i)) {
					col = i;
				}
			}
			if (col == -1) {
				event.type = sf::Event::KeyPressed;
				continue;
			}
			int row = board.getLowestPlace(col);
			if(board.currentPlayer) board.setColor(row, col, sf::Color::Red);
			else board.setColor(row, col, sf::Color::Blue);
			event.type = sf::Event::KeyPressed;
			board.currentPlayer = !board.currentPlayer;
		}

		window.clear(sf::Color::Cyan);
		board.drawBoard();
		window.display();
	}

	return 0;
}