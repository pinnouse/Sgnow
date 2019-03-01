#include <SFML/Graphics.hpp>
#include <stdio.h>

void renderingThread(sf::RenderWindow* window) {
	window->setActive(true);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	sf::Font font;
	if (!font.loadFromFile("Comfortaa-Regular.ttf")) {
		printf("Error: font not found");
	}
	printf("Loaded font");

	sf::Text text;
	text.setFont(font);
	text.setString("Hello World");
	text.setCharacterSize(28);
	text.setFillColor(sf::Color::White);

	while (window->isOpen()) {
		window->clear(sf::Color::Color(64, 64, 64));
		window->draw(shape);

		window->draw(text);
		window->display();
	}
}

int main() {

	sf::ContextSettings settings;
	settings.antialiasingLevel = 14;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Test", sf::Style::Default, settings);

	window.setActive(false);

	sf::Thread renderThread(&renderingThread, &window);
	renderThread.launch();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
	}

	return 0;
}