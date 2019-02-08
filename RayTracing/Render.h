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

Sphere* ClosestIntersection(Vec3f pos, Vec3f dir, std::vector<Sphere>& sph_vec, float t_min, float t_max, float& t) {
	float parametr_t;
	Sphere* IntersectSphere = NULL;
	for (auto& sph : sph_vec) {		
		if (Intersection(pos, dir, sph, parametr_t)) {
			if (parametr_t < t_max && parametr_t > t_min) {
				t_max = parametr_t;
				IntersectSphere = &sph;
			}
		}
	}
	t = t_max;
	return IntersectSphere;
}

Vec3f screen_to_plan(int i, int j) {
	float dist_to_plan = 100;

	float plan_width = 2 * dist_to_plan;
	float plan_height = plan_width * screen_heigt / screen_width;

	float cx = (float)i / screen_width;
	float cy = (float)j / screen_heigt;

	return Vec3f(plan_width * (cx - 0.5), plan_height * (cy - 0.5), 0);
}

Vec3f Reflect_ray(Vec3f fallen_ray, Vec3f normal) {
	return fallen_ray - 2 * (fallen_ray % normal) / (normal % normal) * normal;
}

float Calculate_bright(Sphere* sp, 
						std::vector<Light_point>& light_vec, 
						std::vector<Sphere>& sph_vec, 
						Vec3f intersected_point, 
						Vec3f dir) {
	float bright = 0;
	for (const auto& l : light_vec) {
		Vec3f fallen_ray = l.pos - intersected_point;
		Vec3f normal = intersected_point - sp->center;
		Vec3f reflected_ray = Reflect_ray(fallen_ray, normal);
		
		float parametr_t;
		if (ClosestIntersection(intersected_point, fallen_ray, sph_vec, 0.00001, 1, parametr_t)) {
			continue;
		}

		//Diffuse light
		float k1 = cos(fallen_ray, normal);
		if (k1 > 0) {
			bright += l.brightness * k1;
		}
		//Specular light
		float k2 = cos(reflected_ray, dir);
		if (k2 > 0) {
			bright += l.brightness * pow(k2, sp->specular.val);
		}		
	}
	return bright;
}

sf::Color TraceRay(Vec3f pos, Vec3f dir, std::vector<Sphere>& sph_vec, std::vector<Light_point>& light_vec, int level) {
	float parametr_t = 0;
	Sphere* closest_obj = ClosestIntersection(pos, dir, sph_vec, 0, 1000, parametr_t);

	if (closest_obj != NULL) {
		Vec3f intersected_point = pos + parametr_t * dir;
		float bright = Calculate_bright(closest_obj, light_vec, sph_vec, intersected_point, dir);
		Vec3f color(closest_obj->color);		
		if (level > 0) {
			color = bright * color;
			//color = (1 - sp->reflection) * bright * color + sp->reflection * TraceRay(intersected_point, (1) * reflected_row, sph_vec, light_vec, --level);
		}
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

			sf::Color received_color = TraceRay(pos_on_plan, dir, sph_vec, light_vec, 1);
			img.setPixel(i, j, received_color);
		}
	}

	return img;
}

