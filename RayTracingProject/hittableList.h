#pragma once

#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <vector>

using std::make_shared;
using std::shared_ptr;

class hittableList : public hittable {
	public:
		std::vector<shared_ptr<hittable>> objects;

		hittableList() {};
		hittableList(shared_ptr<hittable> object) { add(object); }

		void add(shared_ptr<hittable> object) {
			objects.push_back(object);
		}

        //for this ray, check if it hits anything and store the rec of the closer object
        bool hit(const ray& ray, interval ray_t, hitRecord& rec) const override {
            bool hitAnything = false;
            double closestSoFar = ray_t.max;

            for (const auto& object : objects) {
                hitRecord tempRec;

                // Only accept hits closer than the closest one found so far
                if (object->hit(ray, interval(ray_t.min, closestSoFar), tempRec)) {
                    hitAnything = true;

                    closestSoFar = tempRec.t;
                    rec = tempRec;
                }
            }

            return hitAnything;
        }
};


#endif 
