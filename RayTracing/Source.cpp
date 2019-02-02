#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

const int screen_width = 1024;
const int screen_heigt = 768;

#include "Render.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(screen_width, screen_heigt), "Ray tracing");

	sf::Image img;
	img = GetRenderImage();

	sf::Texture texture;
	texture.loadFromImage(img);

	sf::Sprite sp;
	sp.setTexture(texture);
	sp.setPosition(0, 0);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(sp);
		window.display();
	}

	return 0;
}