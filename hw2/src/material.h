#ifndef MATERIAL_H
#define MATERIAL_H

#include "brdf.h"

class Material {

public:

	BRDF brdf;

	Material();

	Material(BRDF& brdf);

	void getBRDF(LocalGeo& local, BRDF& brdf) const;

};

#endif