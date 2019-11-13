/* Test File: Make sure you can run this. */
#include "game.hpp"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
	sf::CircleShape shape(100.f);
	sf::CircleShape shape2(200.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		if (event.type == sf::Event::MouseButtonPressed) {
			window.draw(shape2);
		}

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Left) {
				std::cout << "Move Left" << std::endl;
				sf::Vector2f left(-1, 0);
				shape.move(left);
			}

			if (event.key.code == sf::Keyboard::Right) {
				std::cout << "Moved Right" << std::endl;
				sf::Vector2f right(1, 0);
				shape.move(right);
			}

			if (event.key.code == sf::Keyboard::Down) {
				std::cout << "Moved Down" << std::endl;
				sf::Vector2f down(0, 1);
				shape.move(down);
			}

			if (event.key.code == sf::Keyboard::Up) {
				std::cout << "Moved Up" << std::endl;
				sf::Vector2f up(0, -1);
				shape.move(up);
			}
		}

		window.draw(shape);
		window.display();
	}

	return 0;
}
