#ifndef SAMPLER_H
#define SAMPLER_H

#include "options.h"

class Sampler {

	int pixel = 0;
	int sub = 0;

	bool antialias;

public:

	int width, height;

	Sampler(const Options& options);

	bool generate_sample(Sample& sample);

};

#endif