#ifndef SAMPLER_H
#define SAMPLER_H

class Sampler {

	int current = 0;

public:

	int width, height;

	Sampler(const Options& options);

	bool generate_sample(Sample& sample);

};

#endif