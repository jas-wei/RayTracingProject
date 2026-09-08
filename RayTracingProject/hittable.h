#pragma once

#ifndef HITTABLE_H
#define HITTABLE_H

#include "main.h"

// Forward declaration — material is defined in material.h
class material;

class hit_record {
public:
	point3 p;
	vec3 normal;
	double t;
	shared_ptr<material> mat;
	bool front_face = false;

	//This function makes sure that if we are inside an object, the normals will flip
	void set_face_normal(const ray& r, const vec3& outward_normal) {
		if (dot(normalize(r.get_direction()), outward_normal) > 0.0) {
			// ray is inside the sphere
			this->normal = -outward_normal;
			this->front_face = false;
		}
		else {
			// ray is outside the sphere
			this->normal = outward_normal;
			this->front_face = true;
		}
	}
};

class hittable {
public:
	// "virtual" means that other classes can derrive from this one
	virtual ~hittable() = default;

	virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;

	bool quadratic_equation(double* t, double a, double b, double c) const {
		double discriminant = (b * b) - (4 * a * c);
		if (discriminant < 0)
			return false;

		t[0] = (-b - sqrt(discriminant)) / (2 * a);
		t[1] = (-b + sqrt(discriminant)) / (2 * a);

		return true;
	}
};

#endif