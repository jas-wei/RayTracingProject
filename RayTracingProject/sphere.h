#pragma once

#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {

public:
	sphere(const point3& center, double radius, std::shared_ptr<material> mat) :
		center(center), radius(std::fmax(0, radius)), mat(mat)
	{
	}

	bool hit(const ray& r, interval ray_t, hit_record& rec) const override {

		// raydata
		vec3 ray_direction = r.get_direction();
		point3 ray_origin = r.get_origin();

		vec3 camera_to_sphere = center - ray_origin;

		// assembling t from parts of a quadratic equation
		double a = dot(ray_direction, ray_direction);
		double b = dot(-2 * ray_direction, camera_to_sphere);
		double c = dot(camera_to_sphere, camera_to_sphere) - (radius * radius);

		double t[2];

		if (!quadratic_equation(t, a, b, c))
			return false;

		for (int i = 0; i < 2; i++) {
			if (ray_t.surrounds(t[i])) {
				vec3 outward_normal = normalize(r.at(t[i]) - center);

				rec.p = r.at(t[i]);
				rec.t = t[i];
				rec.mat = mat;
				rec.set_face_normal(r, outward_normal);

				return true;
			}
		}

		return false;
	}

private:
	point3 center;
	double radius;
	shared_ptr<material> mat;
};

#endif