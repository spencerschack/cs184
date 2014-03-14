#ifndef MATERIAL_H
#define MATERIAL_H

#include "brdf.h"

class Material {

public:

	BRDF constantBRDF;

	Material();

	Material(BRDF b);

	void getBRDF(LocalGeo& local, BRDF& brdf);

};

#endif