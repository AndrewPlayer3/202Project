#include "game.hpp"
#include <iostream>

int foodGame() {

	std::srand(static_cast<unsigned int>(std::time(NULL)));

	const int wHeight = 720;
	const int wWidth = 1280;

	sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "Test Game",
		sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	float playerRadius = 35.f;
	float playerSpeed = 300.f;
	float foodRadius = 10.f;
	float scaleFactor = 1.1f;

	sf::CircleShape player(playerRadius);
	player.setFillColor(sf::Color::White);
	player.setOrigin(playerRadius / 2.f, playerRadius / 2.f);

	sf::CircleShape food(foodRadius);
	food.setOutlineThickness(5.f);
	food.setOutlineColor(sf::Color::White);
	food.setFillColor(sf::Color::Black);
	food.setOrigin(foodRadius / 2.f, foodRadius / 2.f);

	sf::Clock clock;
	bool isPlaying = false;
	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if ((event.type == sf::Event::Closed)
				|| (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				window.close();
				break;
			}

			if (!isPlaying) {
				isPlaying = true;
				clock.restart();

				player.setPosition(10, wHeight / 2);
				food.setPosition(std::rand() % wWidth, std::rand() % wHeight);
			}

			if (event.type == sf::Event::Resized) {
				sf::View view;
				view.setSize(wWidth, wHeight);
				view.setCenter(wWidth / 2.f, wHeight / 2.f);
				window.setView(view);
			}
		}

		if (isPlaying) {
			float deltaTime = clock.restart().asSeconds();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				player.move(0.f, -playerSpeed * deltaTime);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				player.move(0.f, playerSpeed * deltaTime);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				player.move(-playerSpeed * deltaTime, 0.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				player.move(playerSpeed * deltaTime, 0.f);
			}

			if (std::abs(player.getPosition().x - food.getPosition().x) <= playerRadius &&
				std::abs(player.getPosition().y - food.getPosition().y) <= playerRadius) {

				std::cout << "["     << player.getPosition().x
						  << ", "	 << player.getPosition().y 
					      << "], ["  << food.getPosition().x
					      << ", "    << food.getPosition().y
					      << "]"     << std::endl;

				food.setPosition(std::rand() % wWidth, std::rand() % wHeight);

				player.scale(sf::Vector2f(scaleFactor, scaleFactor));
				playerRadius *= scaleFactor;
			}


			window.clear(sf::Color::Black);

			if (isPlaying) {
				window.draw(player);
				window.draw(food);
			}

			window.display();
		}
	}

	return EXIT_SUCCESS;
}