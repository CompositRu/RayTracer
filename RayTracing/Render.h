#pragma once

#include <math.h>
#include "Vec.h"
#include "Data.h"

sf::Color sfColorFromVec(Vec3f v) {
	for (int i = 0; i < 3; i++) {
		if (v[i] > 255) v[i] = 255;
	}
	for (int i = 0; i < 3; i++) {
		if (v[i] < 0) v[i] = 0;
	}
	return sf::Color((int)v.x, (int)v.y, (int)v.z);
}

bool Intersection(Vec3f pos, Vec3f dir, Sphere sph, float& t) {
	float a = (dir % dir);
	float half_b = (dir % (pos - sph.center));
	float c = (pos - sph.center) % (pos - sph.center) - sph.radius * sph.radius;

	float D1 = half_b * half_b - a * c;

	if (D1 < 0) return false;
	if (D1 == 0) {
		t = -half_b / a;
		return t;
	}
	t = (-half_b - sqrt(D1)) / a;
	return t;
}

Vec3f screen_to_plan(int i, int j) {
	float dist_to_plan = 100;

	float plan_width = 2 * dist_to_plan;
	float plan_height = plan_width * screen_heigt / screen_width;

	float cx = (float)i / screen_width;
	float cy = (float)j / screen_heigt;

	return Vec3f(plan_width * (cx - 0.5), plan_height * (cy - 0.5), 0);
}

sf::Color TraceRay(Vec3f pos, Vec3f dir, std::vector<Sphere>& sph_vec, std::vector<Light_point>& light_vec) {
	float z_buff = 1000;
	Vec3f point_buff;
	Sphere* sp = NULL;

	for (auto& sph : sph_vec) {
		float parametr_t = 0;
		if (Intersection(pos, dir, sph, parametr_t)) {
			Vec3f p = pos + parametr_t * dir;
			if (p.z < z_buff) {
				z_buff = p.z;
				point_buff = p;
				sp = &sph;
			}
		}
	}
	if (sp != NULL) {
		float bright = 0;
		Vec3f color(sp->color);
		for (const auto& l : light_vec) {
			Vec3f fallen_row = l.pos - point_buff;
			Vec3f normal = point_buff - sp->center;
			Vec3f reflected_row = fallen_row - 2 * (fallen_row % normal) / (normal % normal) * normal;

			//Diffuse light
			float k1 = cos(fallen_row, normal);
			if (k1 > 0) {
				bright += l.brightness * k1;
			}
			//Reflect light
			float k2 = cos(reflected_row, dir);
			if (k2 > 0) {
				bright += sp->specular * pow(k2, 8);
			}
		}
		color = bright * color;
		return sfColorFromVec(color);
	}
	else {
		return back_ground;
	}
}

sf::Image GetRenderImage() {
	sf::Image img;
	img.create(screen_width, screen_heigt);

	std::vector<Sphere> sph_vec = GetData();
	std::vector<Light_point> light_vec = GetDataLight();

	float PI = 3.1415926535;
	float fov = PI / 4;

	Vec3f camera_pos(0, 0, -100);
	Vec3f camera_dir(0, 0, 1);

	for (int i = 0; i < screen_width; i++) {
		for (int j = 0; j < screen_heigt; j++) {
			Vec3f pos_on_plan = screen_to_plan(i, j);
			Vec3f dir = pos_on_plan - camera_pos;

			sf::Color received_color = TraceRay(pos_on_plan, dir, sph_vec, light_vec);
			img.setPixel(i, j, received_color);
		}
	}

	return img;
}
#pragma once
