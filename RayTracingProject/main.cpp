#include "main.h"
#include "sphere.h"
#include "hittable.h"
#include "hittableList.h"
#include "camera.h"


//Sphere data

const point3 CENTER = point3(0, 0, 0);
const double RADIUS = 0.5;

//void helloWorld() {
//	// make the image dimentions the max color amount for this demo (255)
//	int imageWidth = 256;
//	int imageHeight = 256;
//
//	//PPM header (needed for valid pnm files)
//	std::cout << "P3\n";
//	std::cout << imageWidth << ' ' << imageHeight << '\n';
//	std::cout << "255\n";
//
//	for (int i = 0; i < imageWidth; i++) {
//		std::clog << "\rScanlines remaining: " << (imageHeight - i) << ' ' << std::flush;
//
//		for (int j = 0; j < imageHeight; j++) {
//			double r = double(i) / double(imageWidth - 1);
//			double g = double(j) / double(imageHeight - 1);
//			double b = 0.0;
//
//			color pixelColor = color(r, g, b);
//			write_color(std::cout, pixelColor);
//		}
//	}
//
//	std::clog << "\rDone.                 \n";
//}



void rayTrace() {

	camera camera;

	//set to default values for visibility (but not needed)
	camera.cameraPosition = point3(0,0,0);
	camera.aspectRatio = 16.0 / 9.0;
	camera.imageWidth = 400;
	camera.viewportHeight = 2.0;
	camera.focalLength = 1.0;

	// test if the ray intersects with the sphere
	std::shared_ptr<sphere> sphereObject1 = std::make_shared<sphere>(point3(0, 0, -1), 0.5);
	std::shared_ptr<sphere> sphereObject2 = std::make_shared<sphere>(point3(0, -100.5, -1), 100);

	hittableList hittableObjectList;
	hittableObjectList.add(sphereObject1);
	hittableObjectList.add(sphereObject2);

	camera.render(hittableObjectList);





	//make viewport
	//double aspectRatio = 16.0 / 9.0;

	//int imageWidth = 400;
	//int imageHeight = int(imageWidth / aspectRatio);
	//if (imageHeight < 1) imageHeight = 1;

	//auto focal_length = 1.0;
	//double viewportHeight = 2.0;
	//double viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);

	////make camera
	//camera camera;
	//camera.position = point3(0,0,0);

	//point3 cameraCenter = point3(0, 0, 0);

	//// World-space viewport directions
	//vec3 viewport_u = vec3(viewportWidth, 0, 0); //don't want unit vectors here
	//vec3 viewport_v = vec3(0, -viewportHeight, 0);

	//// Distance between neighboring pixels
	//auto pixel_delta_u = viewport_u * (double(1) / imageWidth);
	//auto pixel_delta_v = viewport_v * (double(1) / imageHeight);

	//// Find viewport's upper-left corner
	//auto viewport_upper_left = cameraCenter
	//	- vec3(0, 0, focal_length)
	//	- viewport_u / 2
	//	- viewport_v / 2;


	//// Find center of first pixel
	//auto pixel00_loc = viewport_upper_left
	//	+ ( pixel_delta_u / 2)
	//	+ ( pixel_delta_v / 2);

	//PPM header (needed for valid pnm files)
	//std::cout << "P3\n";
	//std::cout << imageWidth << ' ' << imageHeight << '\n';
	//std::cout << "255\n";

	//for (int j = 0; j < imageHeight; j++) {
	//	std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;

	//	for (int i = 0; i < imageWidth; i++) {

	//		// Find this pixel in world space
	//		auto pixelCenter = pixel00_loc
	//			+ (pixel_delta_u * i)
	//			+ (pixel_delta_v * j);

	//		// Create ray from camera through pixel
	//		auto rayDirection = pixelCenter - cameraCenter;
	//		ray r = ray(cameraCenter, rayDirection);

	//		color pixel_color = rayColor(r);
	//		write_color(std::cout, pixel_color);
	//	}
	//}

	//std::clog << "\rDone.                 \n";
} 

int main() {
	//helloWorld();
	rayTrace();

	return 0;
}