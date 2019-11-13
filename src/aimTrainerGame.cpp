#include "game.hpp"
#include <iostream>
#include <sstream>
#include <vector>

float getAverage(const std::vector<float>& times) {
	float sum  = 0;
	for (float f : times) sum += f;
	return sum / (float)times.size();
}

float getBest(const std::vector<float>& times) {
	float lowest = times[0];
	for (float f : times) {
		if (f < lowest) lowest = f;
	}
	return lowest;
}

int aimTrainerGame() {

	std::srand(static_cast<unsigned int>(std::time(NULL)));

	const int wW = 1280;
	const int wH = 720;

	sf::RenderWindow window(sf::VideoMode(wW, wH), "Aim Trainer",
		sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	sf::Font font;
	font.loadFromFile("resrcs/consola.ttf");

	sf::Text last;
	sf::Text avg;
	sf::Text best;

	std::vector<float> times;

	float targetRadius = 25.f;

	sf::CircleShape target(targetRadius);
	target.setFillColor(sf::Color::Green);
	target.setOrigin(targetRadius / 2.f, targetRadius / 2.f);

	sf::Clock reactionClock;
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
				reactionClock.restart();

				target.setPosition(std::rand() % wW, std::rand() % wH);
			}

			if (event.type == sf::Event::Resized) {
				sf::View view;
				view.setSize(wW, wH);
				view.setCenter(wW / 2.f, wH / 2.f);
				window.setView(view);
			}
		}
		if (isPlaying) {
			bool clicked = false;
			if (event.type == sf::Event::MouseButtonPressed &&
				event.mouseButton.button == sf::Mouse::Left) {
				if (((std::abs(sf::Mouse::getPosition(window).x - target.getPosition().x) <= targetRadius) &&
					(std::abs(sf::Mouse::getPosition(window).y - target.getPosition().y) <= targetRadius))) {

					target.setPosition(std::rand() % wW, std::rand() % wH);
					float reactionTime = reactionClock.getElapsedTime().asMilliseconds();
					if (reactionTime >= 20) {	
						times.push_back((float)reactionTime);
						
						std::ostringstream l;
						l << "Last Time: " << reactionTime << "ms\n";
						
						std::ostringstream b;
						b << "Best Time: " << getBest(times) << "ms\n";
						
						std::ostringstream a;
						a << "Average Time: " << getAverage(times) << "ms\n";
						
						last = { sf::String(l.str()), font, 30 };
						best = { sf::String(b.str()), font, 30 };
						avg  = { sf::String(a.str()), font, 30 };
						clicked = true;
						reactionClock.restart().asMilliseconds();
					}
				}
			}
			
			last.setPosition(10, 0);
			best.setPosition(last.getPosition().x + (wW / 4), 0);
			avg.setPosition(best.getPosition().x + (wW / 4), 0);

			window.clear(sf::Color::Red);
			window.draw(last);
			window.draw(best);
			window.draw(avg);
			window.draw(target);
			window.display();

		}
	}

	return EXIT_SUCCESS;
}