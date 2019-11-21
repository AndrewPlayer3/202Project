#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>


int main()
{
	std::vector<std::vector<int> > vect{ { 0, 0, 0, 0, 0, 0, 0 },
										 { 0, 0, 0, 0, 0, 0, 0 },
										 { 0, 0, 0, 0, 0, 1, 0 },
										 { 0, 0, 0, 0, 0, 0, 0 },
										 { 0, 0, 0, 0, 0, 0, 0 },
										 { 0, 0, 1, 0, 1, 0, 0 }};


	sf::RenderWindow window(sf::VideoMode(1100,900 ), "Connect4!");
	sf::CircleShape shape(50.f);
	shape.setFillColor(sf::Color::White);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		window.clear(sf::Color::Cyan);
		for (int row = 0; row < 7; ++row) {
			for (int column = 0; column < 6; ++column) {
				shape.setPosition(100+row * 130.f, 100+column * 130.f);
				if (vect[column][row] == 0) {
					shape.setFillColor(sf::Color::White);
				}
				else if(vect[column][row] == 1){
					shape.setFillColor(sf::Color::Red);
				}
				window.draw(shape);
			}
		}
		window.display();
	}

	return 0;
}