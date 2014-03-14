#include "material.h"

Material::Material() { };

Material::Material(BRDF b) {
	constantBRDF = b;
}

void Material::getBRDF(LocalGeo& local, BRDF& brdf) {
	brdf = constantBRDF;
}
