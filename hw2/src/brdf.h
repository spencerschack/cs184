#ifndef BRDF_H
#define BRDF_H

#include "color.h"

class BRDF {

public:

	Color kd, ks, ka, kr;

	BRDF(Color kd, Color ks, Color ka, Color kr);

	BRDF operator=(BRDF& brdf);

};

#endif