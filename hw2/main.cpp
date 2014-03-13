#include <iostream>

#include "src/options.cpp"
#include "src/vector.cpp"
#include "src/point.cpp"
#include "src/normal.cpp"
#include "src/local_geo.cpp"
#include "src/color.cpp"
#include "src/ray.cpp"
#include "src/sample.cpp"
#include "src/sampler.cpp"
#include "src/matrix.cpp"
#include "src/ray_tracer.cpp"
#include "src/camera.cpp"
#include "src/scene.cpp"
#include "src/film.cpp"
#include "src/light_ray.cpp"
#include "src/light.cpp"

using namespace std;

int main(int argc, char* argv[]) {
	if(argc != 2) {
		printf("USAGE: raytracer commands.txt\n");
		exit(1);
	}
	Scene scene;
	Options(argv[1], scene);
	return scene.render();
}