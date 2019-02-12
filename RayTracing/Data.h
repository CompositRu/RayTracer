#pragma once
#include "Sphere.h"
#include "Prism.h"
#include <memory>

const sf::Color back_ground = sf::Color::Black;



//Сферы
struct Sphere_struct {
	Vec3f center;
	float radius;
	sf::Color color;
	Specular specular;//блики света
	float reflection;//отражение
	float transparent;
	Sphere_struct(Vec3f c, float r, sf::Color col, Specular s, float reflect = 0, float transp = 0) :
		center(c), radius(r), color(col), specular(s.val), reflection(reflect), transparent(transp) {}
};

std::vector<Sphere_struct> GetData_scene1() {
	std::vector<Sphere_struct> v;
	v.push_back(Sphere_struct(Vec3f(200, 100, 200), //red
				100, 
				sf::Color(155, 20, 20), 
				Specular(10),
				0.2));
	v.push_back(Sphere_struct(Vec3f(-100, -100, 200), //blue
				50, 
				sf::Color(20, 20, 155), 
				Specular(50),
				0.5));
	v.push_back(Sphere_struct(Vec3f(0, 0, 450), //green
				150, 
				sf::Color(20, 155, 20), 
				Specular(50),
				0.3));
	v.push_back(Sphere_struct(Vec3f(-350, 50, 650), //orange
				200,
				sf::Color(214, 161, 13),
				Specular(50),
				0.8));
	v.push_back(Sphere_struct(Vec3f(0, 5000, 0), //big
				4900,
				sf::Color(13, 161, 214),
				Specular(50),
				0.5));
	v.push_back(Sphere_struct(Vec3f(0, -500, 200), //top
				100,
				sf::Color(155, 20, 20),
				Specular(10),
				0.2));
	return v;
}

std::vector<Sphere_struct> GetData_scene2() {
	std::vector<Sphere_struct> v;
	v.push_back(Sphere_struct(Vec3f(100, 100, 200), //red
		100,
		sf::Color(155, 20, 20),
		Specular(10)));
	v.push_back(Sphere_struct(Vec3f(-100, -100, 200), //blue
		50,
		sf::Color(20, 20, 155),
		Specular(50),
		0.5));
	v.push_back(Sphere_struct(Vec3f(0, 0, 450), //green
		300,
		sf::Color(20, 155, 20),
		Specular(50),
		0.5));
	v.push_back(Sphere_struct(Vec3f(-350, 250, 650), //orange
		200,
		sf::Color(214, 161, 13),
		Specular(50),
		0.2));
	return v;
}

//Свет
struct Light_point {
	Vec3f pos;
	float intensity;

	Light_point(Vec3f position, float bright) : pos(position), intensity(bright) {}
};

std::vector<Light_point> GetDataLight_scene1() {
	std::vector<Light_point> v;
	v.push_back(Light_point(Vec3f(-300, 0, 0), 0.5));
	v.push_back(Light_point(Vec3f(0, 0, -100), 0.3));
	v.push_back(Light_point(Vec3f(150, 100, -100), 0.5));
	return v;
}

std::vector<Light_point> GetDataLight_scene2() {
	std::vector<Light_point> v;
	v.push_back(Light_point(Vec3f(-300, 0, 0), 0.7));
	v.push_back(Light_point(Vec3f(0, 0, -100), 0.3));
	v.push_back(Light_point(Vec3f(300, 100, -100), 0.5));
	return v;
}

//Объекты классов
std::vector<std::shared_ptr<Rended_object>> Get_data_rended_objects() {
	std::vector<std::shared_ptr<Rended_object>>  v;
	
	v.push_back(std::make_shared<Sphere>( Sphere(2, Vec3f(200, 100, 200), //red
		100.0,
		sf::Color(155, 20, 20),
		Specular(10),
		0.2,
		0)));
	v.push_back(std::make_shared<Sphere>(Sphere(3, Vec3f(-100, -100, 200), //blue
		50,
		sf::Color(20, 20, 155),
		Specular(50),
		0.5,
		0)));
	v.push_back(std::make_shared<Sphere>(Sphere(4, Vec3f(0, 0, 450), //green
		150,
		sf::Color(20, 155, 20),
		Specular(50),
		0.3,
		0)));
	v.push_back(std::make_shared<Sphere>(Sphere(5, Vec3f(-350, 50, 650), //orange
		200,
		sf::Color(214, 161, 13),
		Specular(50),
		0.8,
		0)));
	v.push_back(std::make_shared<Sphere>(Sphere(6, Vec3f(0, 5000, 0), //big
		4900,
		sf::Color(13, 161, 214),
		Specular(50),
		0.5,
		0)));
	v.push_back(std::make_shared<Sphere>(Sphere(7, Vec3f(0, -500, 200), //top
		100,
		sf::Color(155, 20, 20),
		Specular(10),
		0.2,
		0)));
	return v;
}