#pragma once

class Vec3f {
public:
	float x, y, z;
	Vec3f(float a = 0) {
		x = y = z = a;
	}
	Vec3f(float xt, float yt, float zt) : x(xt), y(yt), z(zt) {}
	Vec3f(sf::Color color) : x(color.r), y(color.g), z(color.b) {}

	float& operator[] (int i) {
		if (i == 0) return x;
		if (i == 1) return y;
		if (i == 2) return z;
	}
};

std::ostream& operator<< (std::ostream& os, Vec3f v) {
	bool flag = false;
	os << "[";
	for (int i = 0; i < 3; i++) {
		if (flag) {
			os << ", ";
		}
		flag = true;
		os << v[i];
	}
	os << "]";
	return os;
}

Vec3f operator+ (Vec3f lhs, Vec3f rhs) {
	return Vec3f(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

Vec3f operator- (Vec3f lhs, Vec3f rhs) {
	return Vec3f(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

Vec3f operator* (float t, Vec3f v) {
	return Vec3f(t * v.x, t * v.y, t * v.z);
}

Vec3f operator/ (Vec3f v, float t) {
	return Vec3f(v.x / t, v.y / t, v.z / t);
}

float operator% (Vec3f lhs, Vec3f rhs) {
	return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
}

Vec3f operator! (Vec3f v) {
	float length = sqrt(v % v);
	return v / length;
}

float cos(Vec3f lhs, Vec3f rhs) {
	return (!lhs) % (!rhs);
}