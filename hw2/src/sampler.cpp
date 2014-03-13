#include "sampler.h"

Sampler::Sampler(int width, int height) : width(width), height(height) { };

bool Sampler::generate_sample(Sample& sample) {
	if(current >= width * height) { return false; }
	sample.y = ((float) (current / width)) + 0.5;
	sample.x = ((float) (current % width)) + 0.5;
	current++;
	return true;
};