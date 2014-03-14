#include "brdf.h"

BRDF::BRDF(Color kd, Color ks, Color ka, Color kr) :
	kd(kd), ks(ks), ka(ka), kr(kr) { };

BRDF BRDF::operator=(BRDF& brdf) {
	kd = brdf.kd;
	ks = brdf.ks;
	ka = brdf.ka;
	kr = brdf.kr;
	return *this;
}