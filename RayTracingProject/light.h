#pragma once

#ifndef LIGHT_H
#define LIGHT_H

#include "vec3.h"
#include "color.h"


class light {
    public:
        virtual ~light() = default;

        virtual point3 get_position() const = 0;

        virtual vec3 get_facing_direction() const {
            return vec3(0, 0, 0);
        }

        virtual color get_ambient_color() const = 0;
        virtual color get_diffuse_color() const = 0;
        virtual color get_specular_color() const = 0;

        virtual double get_attenuation(const point3& p) const = 0;
};


class point_light : public light {
    public:

        point3 position;

        color ambient_color;
        color diffuse_color;
        color specular_color;

        float constant;
        float linear;
        float quadratic;

        point3 get_position() const override {
            return position;
        }

        color get_ambient_color() const override {
            return ambient_color;
        }

        color get_diffuse_color() const override {
            return diffuse_color;
        }

        color get_specular_color() const override {
            return specular_color;
        }

        float get_constant() const {
            return constant;
        }

        float get_linear() const {
            return linear;
        }

        float get_quadratic() const {
            return quadratic;
        }

        double get_attenuation(const point3& p) const override {
            float light_distance = (position - p).length();
            vec3 light_dir = normalize(position - p);
            return  1.0 / (constant + (linear * light_distance) + (quadratic * light_distance * light_distance));
        }

};

#endif
