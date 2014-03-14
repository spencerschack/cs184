class BRDF {
public:
	Color kd, ks, ka, kr;

	BRDF(Color kd1, Color ks1, Coloe ka1, Coloe kr1) {
		kd = kd1;
		ks = ks1;
		ka = ka1;
		kr = kr1;
	}

	BRDF BRDF::operator=(BRDF& brdf) {
		kd = brdf.kd;
		ks = brdf.ks;
		ka = brdf.ka;
		kr = brdf.kr;
		return *this;
	}
}