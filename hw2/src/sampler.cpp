#include "sampler.h"

Sampler::Sampler(const Options& options) :
	width(options.width), height(options.height), antialias(options.antialias),
	pixel(0), sub(0) { };

bool Sampler::generate_sample(Sample& sample) {
	if(pixel >= width * height) { return false; }
	if(antialias) {
		float x = sub < 2 ? 0.25 : 0.75;
		float y = sub % 2 == 0 ? 0.25 : 0.75;
		sample.y = ((float) (pixel / width)) + x;
		sample.x = ((float) (pixel % width)) + y;
		if(sub++ == 4) {
			pixel++;
			sub = 0;
		}
	} else {
		sample.y = ((float) (pixel / width)) + 0.5;
		sample.x = ((float) (pixel % width)) + 0.5;
		pixel++;
	}
	return true;
};