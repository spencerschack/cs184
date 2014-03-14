#include "material.h"

Material::Material() { };

Material::Material(BRDF& brdf) : brdf(brdf) { };

void Material::getBRDF(LocalGeo& local, BRDF& destination) const {
	destination = brdf;
}
