#pragma once

#include "main.h"
#include "interval.h"

#include <iostream>
#include <memory>
#include <limits>

class camera {
public:
	// Camera/image configuration
	double aspectRatio = 16.0 / 9.0;
	int imageWidth = 400;
	double viewportHeight = 2.0;
	point3 cameraPosition = point3(0, 0, 0);
	double focalLength = 1.0;

	// Rendering configuration
	int samples = 10;
	int maxDepth = 10;

	camera() = default;


	void render(const hittable& hittableObject) {
		initialize();

		// PPM header
		std::cout << "P3\n";
		std::cout << imageWidth << ' ' << imageHeight << '\n';
		std::cout << "255\n";

		// Traverse pixels from left-to-right, top-to-bottom
		for (int j = 0; j < imageHeight; j++) {
			std::clog << "\rScanlines remaining: "
				<< (imageHeight - j) << ' ' << std::flush;

			for (int i = 0; i < imageWidth; i++) {

				// Find this pixel's center in world space
				auto pixelCenter = pixel00_loc
					+ (pixel_delta_u * i)
					+ (pixel_delta_v * j);

				// Accumulate multiple random samples for anti-aliasing
				color avgColor = color(0, 0, 0);

				for (int k = 0; k < samples; k++) {
					point3 pixelSample = samplePixel(pixelCenter);
					ray r = getRay(pixelSample);

					int currentDepth = 0;
					color pixelColor =
						rayColor(r, currentDepth, hittableObject);

					avgColor += pixelColor;
				}

				// Average all samples for this pixel
				avgColor /= double(samples);
				write_color(std::cout, avgColor);
			}
		}

		std::clog << "\rDone.                 \n";
	}


private:
	// Values calculated from the public camera configuration
	int imageHeight = 225;
	double viewportWidth = 3.556;

	vec3 pixel_delta_u;
	vec3 pixel_delta_v;
	point3 pixel00_loc;


	void initialize() {
		// Calculate image dimensions
		imageHeight = int(imageWidth / aspectRatio);
		if (imageHeight < 1)
			imageHeight = 1;

		// Match viewport proportions to the actual image proportions
		viewportWidth =
			viewportHeight * (double(imageWidth) / imageHeight);

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


	// Select a random sample within the area surrounding a pixel center
	point3 samplePixel(const point3& pixelCenter) const {
		double randomU = getRandomDouble(-0.5, 0.5);
		double randomV = getRandomDouble(-0.5, 0.5);

		return pixelCenter
			+ randomU * pixel_delta_u
			+ randomV * pixel_delta_v;
	}


	// Create a ray from the camera through a sampled viewport position
	ray getRay(const point3& pixelSample) const {
		auto rayDirection = pixelSample - cameraPosition;
		return ray(cameraPosition, rayDirection);
	}


	color rayColor(
		const ray& r,
		int& currentDepth,
		const hittable& hittableObject
	) const {

		// Stop recursively bouncing once the maximum depth is reached
		if (currentDepth == maxDepth)
			return color(0, 0, 0);

		hitRecord closesetSphereHitRecord;

		bool isHit = hittableObject.hit(
			r,
			interval(0.001, std::numeric_limits<double>::infinity()),
			closesetSphereHitRecord
		);

		// check if hit point is valid and is in front of the ray orgin (camera pos)
		if (isHit) {
			currentDepth++;

			// Generate a random bounce direction on the surface's hemisphere
			vec3 direction = closesetSphereHitRecord.normal + randomOnSphereNormalized();

			// recursively call rayColor again (0.5 * 0.5 * ... * 0.5 * skyColor)
			return 0.5 * rayColor(
				ray(closesetSphereHitRecord.point, direction),
				currentDepth,
				hittableObject
			);
		}

		// output sky color if no hit detected
		color white = color(1, 1, 1);
		color lightBlue = color(0.5, 0.7, 1.0);

		auto a = 0.5 * (normalize(r.getDirection()).y() + 1.0);
		auto skyColor = (1 - a) * white + a * lightBlue;

		return skyColor;
	}
};