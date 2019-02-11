#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>

const int screen_width = 1024;
const int screen_heigt = 768;

const bool debug_mod = true;

#include "Render.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(screen_width, screen_heigt), "Ray tracing");

	sf::Clock clock;
	sf::Image img;
	img = GetRenderImage();
	
	sf::Texture texture;
	texture.loadFromImage(img);
	sf::Time timer = clock.restart();
	sf::Time time_counter = sf::seconds(1);
	std::cout << "time form start: " << timer.asSeconds() << std::endl;

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

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					Vec3f camera_pos(0, 0, -100);
					Vec3f camera_dir(0, 0, 1);
					Vec3f pos_on_plan = screen_to_plan(event.mouseButton.x, event.mouseButton.y);
					Vec3f dir = pos_on_plan - camera_pos;
					std::vector<std::unique_ptr<Rended_object>> sph_vec = Get_data_rended_objects();
					std::vector<Light_point> light_vec = GetDataLight_scene1();
					sf::Color received_color = TraceRay(pos_on_plan, dir, sph_vec, light_vec, 3, true);
				}
			}
		}
		
		window.clear();
		window.draw(sp);
		window.display();

		timer = clock.restart();
		time_counter += timer;
		if (time_counter.asSeconds() > 1) {
			std::stringstream ss;
			ss << "fps: " << (int) (1 / timer.asSeconds());
			const std::string s = ss.str();
			window.setTitle(s.c_str());
			time_counter = sf::seconds(0);
		}
		
	}

	return 0;
}