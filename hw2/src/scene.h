#ifndef SCENE_H
#define SCENE_H

#include "options.h"

class Scene {

public:

	Scene(Options options);

	Options options;

	int render();
	
};

#endif