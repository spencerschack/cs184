#ifndef SCENE_H
#define SCENE_H

#include "camera.h"

using namespace std;

class Scene {

public:

	Scene();

	Camera camera;

	string filename;

	unsigned int width, height, maxdepth;

	float camera_fov;

	int render();
	
};

#endif