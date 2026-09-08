#include "main.h"
#include "sphere.h"
#include "hittable.h"
#include "hittableList.h"
#include "camera.h"
#include "material.h"


//Sphere data
const point3 CENTER = point3(0, 0, 0);
const double RADIUS = 0.5;

////Light data
//const point LIGHT_POS

void ray_trace() {

	camera camera;

	//set to default values for visibility (but not needed)
	camera.camera_position = point3(0, 0, 0);
	camera.aspect_ratio = 16.0 / 9.0;
	camera.image_width = 400;
	camera.viewport_height = 2.0;
	camera.focal_length = 1.0;
	camera.samples = 100;

	// test if the ray intersects with the sphere
	auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
	auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
	auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
	auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

	hittable_list hittable_object_list;
	hittable_object_list.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
	hittable_object_list.add(make_shared<sphere>(point3(0.0, 0.0, -1.2), 0.5, material_center));
	hittable_object_list.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
	hittable_object_list.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));


	camera.render(hittable_object_list);
}


int main() {
	//helloWorld();
	ray_trace();

	return 0;
}