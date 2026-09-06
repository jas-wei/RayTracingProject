#pragma once

#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class hitRecord {
public:
	point3 point;
	vec3 normal;
	double t;
	bool frontFace = false;

	//This function makes sure that if we are inside an object, the normals will flip
	void setFaceNormal(const ray& ray, const vec3& outwardNormal) {
		bool frontFace;
		if (dot(normalize(ray.getDirection()), outwardNormal) > 0.0) {
			// ray is inside the sphere
			this->normal = -outwardNormal;
			this->frontFace = false;
		}
		else {
			// ray is outside the sphere
			this->normal = outwardNormal;
			this->frontFace = true; 
		}
	}
};

class hittable {
	public:
		// "virtual" means that other classes can derrive from this one
		virtual ~hittable() = default;

		virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hitRecord& rec) const = 0;

		bool quadraticEquation(double* t, double a, double b, double c) const {
			double discriminant = (b * b) - (4 * a * c);
			if (discriminant < 0) return false;

			t[0] = (-b - sqrt(discriminant)) / (2 * a);
			t[1] = (-b + sqrt(discriminant)) / (2 * a);

			return true;
		}


};


#endif