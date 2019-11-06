#include <iostream>
#include <SFML/Graphics.hpp>
#include "ball.hpp"

int main( int argc, char *argv[] ){
	std::cout << "Starting application 01-02 static ball\n";

	sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window" };
	ball my_ball{ sf::Vector2f{ 320.0, 240.0 } };

	window.clear();
	my_ball.draw( window );
	window.display();

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		sf::sleep(sf::milliseconds(20));
	}
	std::cout << "Terminating application\n";
	return 0;
}

