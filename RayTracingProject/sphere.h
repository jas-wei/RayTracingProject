#pragma once

#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {

	public:
		sphere(const point3& center, double radius) :
			center(center), radius(std::fmax(0, radius))
		{}

		bool hit(const ray& ray, interval ray_t, hitRecord& rec) const override {

			// raydata
			vec3 rayDirection = ray.getDirection();
			point3 rayOrigin = ray.getOrigin();

			vec3 cameraToSphere = center - rayOrigin;

			// assembling t from parts of a quadratic equation
			double a = dot(rayDirection, rayDirection);
			double b = dot(-2 * rayDirection, cameraToSphere);
			double c = dot(cameraToSphere, cameraToSphere) - (radius * radius);

			double t[2];
			quadraticEquation(t, a, b, c);
			for (int i = 0; i < 2; i++) {
				if (ray_t.surrounds(t[i])) {
					vec3 outwardNormal = normalize(ray.at(t[i]) - center);

					rec.point = ray.at(t[i]);
					rec.t = t[i];
					rec.setFaceNormal(ray, outwardNormal);

					return true;
				}
			}
			
			
			return false;
		}

	private:
		point3 center;
		double radius;
};

#endif