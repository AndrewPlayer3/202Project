/*
	CS 202 Group Project
	Connect4 Board Game made with SFML

	Members: Robert Lawton, Andrew Player,
	Jadon Nashoanak, Jordan Day, Jared Maltos

	12/3/2019
	Professor Hartman
*/
#include "board.hpp"
#include <iostream>

int connectFourGame() {

	int windowHeight = 900;
	int windowWidth = 1100;

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Connect4!", 
	sf::Style::Titlebar | !sf::Style::Resize | sf::Style::Close);
	window.setKeyRepeatEnabled(false);
	Board board(&window);
	board.initBoard();

	sf::Font font;
	font.loadFromFile("resrcs/consola.ttf");

	sf::Text currentPlayerStatus;
	currentPlayerStatus.setCharacterSize(30.f);
	currentPlayerStatus = { std::string("Player: 1"), font, 50 };

	sf::Text winnerMessage;
	winnerMessage.setCharacterSize(30.f);

	sf::Text drawMessage;
	drawMessage.setCharacterSize(30.f);
	
	sf::SoundBuffer placingSoundBuffer;
	if (!placingSoundBuffer.loadFromFile("resrcs/placingsound.wav")) {
		std::cout << "couldn't load placingsound.wav" << std::endl;
	}
	sf::Sound placingSound;
	placingSound.setBuffer(placingSoundBuffer);
	
	sf::SoundBuffer winningSoundBuffer;
	if (!winningSoundBuffer.loadFromFile("resrcs/ohyeah.wav")) {
		std::cout << "couldn't load ohyeah.wav" << std::endl;
	}
	sf::Sound winningSound;
	winningSound.setVolume(50);
	winningSound.setBuffer(winningSoundBuffer);

	sf::SoundBuffer drawSoundBuffer;
	if (!drawSoundBuffer.loadFromFile("resrcs/wahwah.wav")) {
		std::cout << "couldn't load wahwah.wav" << std::endl;
	}
	sf::Sound drawSound;
	drawSound.setVolume(50);
	drawSound.setBuffer(drawSoundBuffer);

	sf::Music backgroundMusic;
	if (!backgroundMusic.openFromFile("resrcs/elevator.wav")) {
		std::cout << "couldn't load elevator.wav" << std::endl;
	}
	backgroundMusic.setVolume(25);
	backgroundMusic.setLoop(true);
	backgroundMusic.play();
	
	bool hasWon = false;
	bool isDraw = false;

	// This is the game loop
	while (window.isOpen())
	{
		if (hasWon || isDraw) {
			if (board.currentPlayer) {
				winnerMessage = { std::string("Player 2 Wins!"), font, 50 };
			} else {
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
				} else {
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
				if (hasWon) winningSound.play();
				if (isDraw && !hasWon) drawSound.play();
				placingSound.play();
			}
		}

		currentPlayerStatus.setOutlineThickness(2.f);
		currentPlayerStatus.setOutlineColor(sf::Color::Black);
		currentPlayerStatus.setPosition(100.f, 10);

		sf::Color boardColor(153, 51, 255);
		window.clear(boardColor);
		window.draw(currentPlayerStatus);

		if (hasWon) window.draw(winnerMessage);
		if (isDraw && !hasWon) window.draw(drawMessage);
		
		board.drawBoard();
		window.display();
	}

	return 0;
}