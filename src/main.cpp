/* Test File: Make sure you can run this. */
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1100,900 ), "Connect4!");
	sf::CircleShape shape(50.f);
	shape.setFillColor(sf::Color::Cyan);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		window.clear(sf::Color::Blue);
		for (int row = 0; row < 7; ++row) {
			for (int column = 0; column < 6; ++column) {
				shape.setPosition(100+row * 130.f, 100+column * 130.f);
				window.draw(shape);
			}
		}
		window.display();
	}

	return 0;
}