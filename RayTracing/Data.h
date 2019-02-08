#pragma once

const sf::Color back_ground = sf::Color::Black;

struct Specular {
	int val;
	explicit Specular(int value) : val(value) {}
};

//—феры
struct Sphere {
	Vec3f center;
	float radius;
	sf::Color color;
	Specular specular;//блики света
	float reflection;//отражение
	float transparent;
	Sphere(Vec3f c, float r, sf::Color col, Specular s, float reflect = 0, float transp = 0) :
		center(c), radius(r), color(col), specular(s.val), reflection(reflect), transparent(transp) {}
};

std::vector<Sphere> GetData() {
	std::vector<Sphere> v;
	v.push_back(Sphere(Vec3f(100, 100, 200), //red
				100, 
				sf::Color(155, 20, 20), 
				Specular(10)));
	v.push_back(Sphere(Vec3f(-100, -100, 200), //blue
				50, 
				sf::Color(20, 20, 155), 
				Specular(50)));
	v.push_back(Sphere(Vec3f(0, 0, 450), //green
				300, 
				sf::Color(20, 155, 20), 
				Specular(50),
				0.2));
	v.push_back(Sphere(Vec3f(-350, 250, 650), //orange
				200,
				sf::Color(214, 161, 13),
				Specular(50),
				0.2));
	return v;
}

//—вет
struct Light_point {
	Vec3f pos;
	float brightness;

	Light_point(Vec3f position, float bright) : pos(position), brightness(bright) {}
};

std::vector<Light_point> GetDataLight() {
	std::vector<Light_point> v;
	v.push_back(Light_point(Vec3f(-300, 0, 0), 0.7));
	//v.push_back(Light_point(Vec3f(0, 0, -100), 0.3));
	v.push_back(Light_point(Vec3f(300, 100, -100), 0.5));
	return v;
}
