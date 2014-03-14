#ifndef BRDF_H
#define BRDF_H

#include "color.h"

class BRDF {

public:

	Color ka, kd, ks, kr, ke;

	float sp;

	BRDF();

	BRDF(Color ka, Color kd, Color ks, Color kr, Color ke, float sp);

	BRDF operator=(const BRDF& brdf);

	void reset();

};

#endif