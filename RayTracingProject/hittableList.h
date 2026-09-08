#pragma once

#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <vector>

using std::make_shared;
using std::shared_ptr;

class hittable_list : public hittable {
public:
    std::vector<shared_ptr<hittable>> objects;

    hittable_list() {};
    hittable_list(shared_ptr<hittable> object) { add(object); }

    void add(shared_ptr<hittable> object) {
        objects.push_back(object);
    }

    //for this ray, check if it hits anything and store the rec of the closer object
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        bool hit_anything = false;
        double closest_so_far = ray_t.max;

        for (const auto& object : objects) {
            hit_record temp_rec;

            // Only accept hits closer than the closest one found so far
            if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
                hit_anything = true;

                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
};

#endif