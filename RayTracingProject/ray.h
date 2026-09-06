#pragma once

#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray
{
	public:
		//constructor 1
		ray() {}

		//constructor 2 (with initializer list)
		ray(const point3& origin, const vec3& direction) 
		: orig(origin), dir(direction){}

		//gets immutable reference of origin
		const point3& getOrigin() const{
			return orig;
		}

		//gets immutable reference of direction
		const vec3& getDirection() const{ 
			return dir;
		}

		//sets new origin
		void setOrigin(const point3 newOrig) {
			 orig = newOrig;
		}

		//sets new direction
		void setDirection(const vec3 newDir) {
			dir = newDir;
		}

		//returns a point along ray at t
		const point3 at(double t) const {
			return orig + (dir * t);
		}


	private:
		point3 orig;
		vec3 dir;
};

#endif
