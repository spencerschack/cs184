#ifndef SCENE_H
#define SCENE_H

#include "options.h"

using namespace std;

class Scene {

private:

	const Options& options;

public:

	Scene(const Options& options);

	int render();
	
};

#endif