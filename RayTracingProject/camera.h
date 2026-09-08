#pragma once

#include "main.h"
#include "interval.h"
#include "material.h"

#include <iostream>
#include <memory>
#include <limits>

class camera {
public:
	// Camera/image configuration
	double aspect_ratio = 16.0 / 9.0;
	int image_width = 400;
	double viewport_height = 2.0;
	point3 camera_position = point3(0, 0, 0);
	double focal_length = 1.0;

	// Rendering configuration
	int samples = 10;
	int max_depth = 10;

	camera() = default;


	void render(const hittable& hittable_object) {
		initialize();

		// PPM header
		std::cout << "P3\n";
		std::cout << image_width << ' ' << image_height << '\n';
		std::cout << "255\n";

		// Traverse pixels from left-to-right, top-to-bottom
		for (int j = 0; j < image_height; j++) {
			std::clog << "\rScanlines remaining: "
				<< (image_height - j) << ' ' << std::flush;

			for (int i = 0; i < image_width; i++) {

				// Find this pixel's center in world space
				auto pixel_center = pixel00_loc
					+ (pixel_delta_u * i)
					+ (pixel_delta_v * j);

				// Accumulate multiple random samples for anti-aliasing
				color avg_color = color(0, 0, 0);

				for (int k = 0; k < samples; k++) {
					point3 pixel_sample = sample_pixel(pixel_center);
					ray r = get_ray(pixel_sample);

					int current_depth = 0;
					color pixel_color =
						ray_color(r, current_depth, hittable_object);

					avg_color += pixel_color;
				}

				// Average all samples for this pixel
				avg_color /= double(samples);
				write_color(std::cout, avg_color);
			}
		}

		std::clog << "\rDone.                 \n";
	}


private:
	// Values calculated from the public camera configuration
	int image_height = 225;
	double viewport_width = 3.556;

	vec3 pixel_delta_u;
	vec3 pixel_delta_v;
	point3 pixel00_loc;


	void initialize() {
		// Calculate image dimensions
		image_height = int(image_width / aspect_ratio);
		if (image_height < 1)
			image_height = 1;

		// Match viewport proportions to the actual image proportions
		viewport_width =
			viewport_height * (double(image_width) / image_height);

		// World-space viewport directions
		vec3 viewport_u = vec3(viewport_width, 0, 0); //don't want unit vectors here
		vec3 viewport_v = vec3(0, -viewport_height, 0);

		// Distance between neighboring pixels
		pixel_delta_u = viewport_u * (double(1) / image_width);
		pixel_delta_v = viewport_v * (double(1) / image_height);

		// Find viewport's upper-left corner
		auto viewport_upper_left = camera_position
			- vec3(0, 0, focal_length)
			- viewport_u / 2
			- viewport_v / 2;

		// Find center of first pixel
		pixel00_loc = viewport_upper_left
			+ (pixel_delta_u / 2)
			+ (pixel_delta_v / 2);
	}


	// Select a random sample within the area surrounding a pixel center
	point3 sample_pixel(const point3& pixel_center) const {
		double random_u = get_random_double(-0.5, 0.5);
		double random_v = get_random_double(-0.5, 0.5);

		return pixel_center
			+ random_u * pixel_delta_u
			+ random_v * pixel_delta_v;
	}


	// Create a ray from the camera through a sampled viewport position
	ray get_ray(const point3& pixel_sample) const {
		auto ray_direction = pixel_sample - camera_position;
		return ray(camera_position, ray_direction);
	}


	color ray_color(
		const ray& r,
		int& current_depth,
		const hittable& hittable_object
	) const {

		// Stop recursively bouncing once the maximum depth is reached
		if (current_depth == max_depth)
			return color(0, 0, 0);

		hit_record rec;

		bool is_hit = hittable_object.hit( r, interval(0.001, std::numeric_limits<double>::infinity()), rec);

		// check if hit point is valid and is in front of the ray orgin (camera pos)
		if (is_hit) {
			current_depth++;

			//containers to-be-assigned values from scatter()
			color attenuation;
			ray scattered;

			//if scatter() from the material returns a valid direction
			if (rec.mat->scatter(r, rec, attenuation, scattered)) {

				// recursively call ray_color again (attenuation * ... * attenuation * sky_color)
				return attenuation * ray_color(scattered, current_depth, hittable_object);
			}

			return color(0, 0, 0);
		}

		// output sky color if no hit detected
		color white = color(1, 1, 1);
		color light_blue = color(0.5, 0.7, 1.0);

		auto a = 0.5 * (normalize(r.get_direction()).y() + 1.0);
		auto sky_color = (1 - a) * white + a * light_blue;

		return sky_color;
	}
};