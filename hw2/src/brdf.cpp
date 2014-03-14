#include "brdf.h"

BRDF::BRDF() { };

BRDF::BRDF(Color ka, Color kd, Color ks, Color kr, Color ke, float sp) :
	kd(kd), ks(ks), kr(kr), ke(ke), sp(sp) { };

BRDF BRDF::operator=(const BRDF& brdf) {
	ka = brdf.ka;
	kd = brdf.kd;
	ks = brdf.ks;
	kr = brdf.kr;
	ke = brdf.ke;
	sp = brdf.sp;
	return *this;
}

void BRDF::reset() {
	ka.reset();
	kd.reset();
	ks.reset();
	kr.reset();
	ke.reset();
	sp = 0;
}
