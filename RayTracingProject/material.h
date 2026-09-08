#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"
class material {
	public:
		virtual ~material() = default;

        virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
            return false;
        }
};

class lambertian: public material {
    public:
        lambertian(const color& albedo) : albedo(albedo) {}

        bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
            // Basically ((p+n) + random_unit_vector()) - p
            auto scatter_direction = rec.normal + random_unit_vector();

            // Catch scatter direction close to zero (no direction)
            if (scatter_direction.near_zero())
                scatter_direction = rec.normal;

            scattered = ray(rec.p, scatter_direction);
            attenuation = albedo; //color multiplier applied to the bounced ray’s returned light
            return true;
        }

    private:
        color albedo;
};

class metal : public material {
public:
    metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        // Basically ((p+n) + random_unit_vector()) - p
        vec3 reflected_dir = reflect(r_in.get_direction(), rec.normal);
        point3 fuzzed_point = rec.p + reflected_dir + fuzz*random_unit_vector();
        scattered = ray(rec.p, fuzzed_point - rec.p);
        attenuation = albedo; //color multiplier applied to the bounced ray’s returned light
        
        return (dot(scattered.get_direction(), rec.normal) > 0);
    }

private:
    color albedo;
    double fuzz;
};



#endif