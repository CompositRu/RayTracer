#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Vec3f {
public:
	float x, y, z;
	Vec3f(float a = 0);
	Vec3f(float xt, float yt, float zt);
	Vec3f(sf::Color color);
	float& operator[] (int i);
	//Vec3f operator= (Vec3f rhs);
};

std::ostream& operator<< (std::ostream& os, Vec3f& v);
Vec3f operator+ (Vec3f lhs, Vec3f rhs);
Vec3f operator- (Vec3f lhs, Vec3f rhs);
Vec3f operator- (Vec3f v);
Vec3f operator* (float t, Vec3f v);
Vec3f operator/ (Vec3f v, float t);
float operator% (Vec3f lhs, Vec3f rhs);
Vec3f operator! (Vec3f v);
float cos(Vec3f lhs, Vec3f rhs);