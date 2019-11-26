#include "board.hpp"
#include <iostream>

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

	sf::Text winnerMessage;
	winnerMessage.setCharacterSize(30.f);

	sf::Text drawMessage;
	drawMessage.setCharacterSize(30.f);

	bool hasWon = false;
	bool isDraw = false;

	while (window.isOpen())
	{

		if (hasWon || isDraw) {
			if (board.currentPlayer) {
				winnerMessage = { std::string("Player 2 Wins!"), font, 50 };
			}
			else {
				winnerMessage = { std::string("Player 1 Wins!"), font, 50 };
			}
			winnerMessage.setPosition(400.f, 10.f);
			winnerMessage.setOutlineThickness(2.f);
			winnerMessage.setOutlineColor(sf::Color::Black);
			drawMessage = { std::string("Draw!"), font, 50 };
			drawMessage.setPosition(500.f, 10.f);
			drawMessage.setOutlineThickness(2.f);
			drawMessage.setOutlineColor(sf::Color::Black);
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed
				|| event.type == sf::Event::KeyReleased
				&& event.key.code == sf::Keyboard::Escape)
				window.close();

			if ((hasWon || isDraw)
				&& event.type == sf::Event::KeyReleased
				&& event.key.code == sf::Keyboard::Space) {
				board.initBoard();
				hasWon = false;
				isDraw = false;
				board.filledPlaces = 0;
			}
		}
		if (!hasWon) {
			if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left) {
				float mPos = sf::Mouse::getPosition(window).x;
				int col = board.getColumnFromPos(mPos);
				if (col == -1) {
					event.type = sf::Event::KeyPressed;
					continue;
				}
				int row = board.getLowestPlace(col);
				if (board.currentPlayer) {
					board.setColor(row, col, board.playerOneColor);
					hasWon = board.checkForWinner(board.playerOneColor);
					currentPlayerStatus = { std::string("Player: 2"), font, 50 };
				}
				else {
					board.setColor(row, col, board.playerTwoColor);
					hasWon = board.checkForWinner(board.playerTwoColor);
					currentPlayerStatus = { std::string("Player: 1"), font, 50 };
				}
				if (++board.filledPlaces ==
					(board.getNumberOfColumns() * board.getNumberOfRows())) {
					isDraw = true;
				}
				event.type = sf::Event::KeyPressed;
				board.currentPlayer = !board.currentPlayer;
			}
		}

		currentPlayerStatus.setOutlineThickness(2.f);
		currentPlayerStatus.setOutlineColor(sf::Color::Black);
		currentPlayerStatus.setPosition(100.f, 10);

		window.clear(sf::Color::Green);
		window.draw(currentPlayerStatus);
		if (hasWon) {
			window.draw(winnerMessage);
		}
		if (isDraw && !hasWon) {
			window.draw(drawMessage);
		}
		board.drawBoard();
		window.display();
	}

	return 0;
}