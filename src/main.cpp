/* Test File: Make sure you can run this. */
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
<<<<<<< HEAD
	connectFourGame();
=======
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
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
		window.draw(shape);
		window.display();
	}

>>>>>>> 0d09193ff9ecaf87bfc29c70bb644f6557b05856
	return 0;
}
//jared testing git repo