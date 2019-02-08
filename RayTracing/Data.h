#pragma once

const sf::Color back_ground = sf::Color::Black;

//—феры
struct Sphere {
	Vec3f center;
	float radius;
	sf::Color color;
	float specular;//блики света
	float reflection;//отражение
	float transparent;
	Sphere(Vec3f c, float r, sf::Color col, float s, float reflect = 0, float transp = 0) : 
		center(c), radius(r), color(col), specular(s), reflection(reflect), transparent(transp) {}
};

std::vector<Sphere> GetData() {
	std::vector<Sphere> v;
	v.push_back(Sphere(Vec3f(100, 100, 200), 100, sf::Color(155, 20, 20), 0.5));
	v.push_back(Sphere(Vec3f(-100, -100, 200), 50, sf::Color(20, 20, 155), 1));
	v.push_back(Sphere(Vec3f(0, 0, 450), 300, sf::Color(20, 155, 20), 0.5, 0.2));
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
	v.push_back(Light_point(Vec3f(-300, 0, 0), 0.9));
	v.push_back(Light_point(Vec3f(0, 0, -100), 0.1));
	return v;
}
