#pragma once

#include "main.h"
//#include "ray.h"

#include <iostream>
#include <memory>
#include <limits>

class camera {
public:
	double aspectRatio = 16.0 / 9.0;
	int imageWidth = 400;
	double viewportHeight = 2.0;
	point3 cameraPosition = point3(0, 0, 0);
	double focalLength = 1.0;


	camera() {}



	void render(hittable& hittableObject) {
		initialize();

		std::cout << "P3\n";
		std::cout << imageWidth << ' ' << imageHeight << '\n';
		std::cout << "255\n";

		for (int j = 0; j < imageHeight; j++) {
			std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;

			for (int i = 0; i < imageWidth; i++) {

				// Find this pixel in world space
				auto pixelCenter = pixel00_loc
					+ (pixel_delta_u * i)
					+ (pixel_delta_v * j);

				ray r = getRay(pixelCenter, cameraPosition);

				color pixel_color = rayColor(r, hittableObject);
				write_color(std::cout, pixel_color);
			}
		}

		std::clog << "\rDone.                 \n";
	}


private:

	int imageHeight = 225;
	double viewportWidth = 3.556;
	vec3 pixel_delta_u;
	vec3 pixel_delta_v;
	point3 pixel00_loc;

	void initialize() {

		imageHeight = int(imageWidth / aspectRatio);
		if (imageHeight < 1) imageHeight = 1;

		viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);


		// World-space viewport directions
		vec3 viewport_u = vec3(viewportWidth, 0, 0); //don't want unit vectors here
		vec3 viewport_v = vec3(0, -viewportHeight, 0);

		// Distance between neighboring pixels
		pixel_delta_u = viewport_u * (double(1) / imageWidth);
		pixel_delta_v = viewport_v * (double(1) / imageHeight);

		// Find viewport's upper-left corner
		auto viewport_upper_left = cameraPosition
			- vec3(0, 0, focalLength)
			- viewport_u / 2
			- viewport_v / 2;


		// Find center of first pixel
		pixel00_loc = viewport_upper_left
			+ (pixel_delta_u / 2)
			+ (pixel_delta_v / 2);
	}

	ray getRay(const point3& pixelCenter, const point3& cameraCenter) {
		// Create ray from camera through pixel
		auto rayDirection = pixelCenter - cameraCenter;
		ray r = ray(cameraCenter, rayDirection);
		return r;
	}

	color rayColor(const ray& ray, hittable& hittableObject) {

		hitRecord closesetSphereHitRecord;
		bool isHit = hittableObject.hit(
			ray,
			interval(0, std::numeric_limits<double>::infinity()),
			closesetSphereHitRecord
		);

		// check if hit point is valid and is in front of the ray orgin (camera pos)
		if (isHit) {
			return 0.5 * (closesetSphereHitRecord.normal + color(1, 1, 1));
		}

		// output sky color if no hit detected
		color white = color(1, 1, 1);
		color lightBlue = color(0.5, 0.7, 1.0);

		auto a = 0.5 * (normalize(ray.getDirection()).y() + 1.0);
		auto skyColor = (1 - a) * white + a * lightBlue;

		return skyColor;
	}

};