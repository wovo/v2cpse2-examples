#include <iostream>
#include <SFML/Graphics.hpp>
#include "ball.hpp"

sf::Vector2f Vector2f_from_Vector2i(sf::Vector2i rhs) {
	return sf::Vector2f((float)rhs.x, (float)rhs.y);
}

const struct { sf::Keyboard::Key key; float x; float y; } actions[] = {
	{ sf::Keyboard::Left,  -1.0,  0.0 },
	{ sf::Keyboard::Right, +1.0,  0.0 },
	{ sf::Keyboard::Up,     0.0, -1.0 },
	{ sf::Keyboard::Down,   0.0, +1.0 }
};

int main( int argc, char *argv[] ){
	std::cout << "Starting application 01-04 array of deltas\n";

	sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window" };
	ball my_ball{ sf::Vector2f{ 320.0, 240.0 } };

	while (window.isOpen()) {
		for (auto & action : actions) {
			if( sf::Keyboard::isKeyPressed(action.key)) {
				my_ball.move(sf::Vector2f{ action.x, action.y });
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			my_ball.jump(Vector2f_from_Vector2i(sf::Mouse::getPosition(window)));
		}

		sf::Event event;
		if( window.pollEvent(event) ){
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();
		my_ball.draw(window);
		window.display();

		sf::sleep(sf::milliseconds(20));

	}

	std::cout << "Terminating application\n";
	return 0;
}

