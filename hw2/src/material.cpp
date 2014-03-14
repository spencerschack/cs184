class Material {
public:
	BRDF constantBRDF;

	Material(BRDF b) {
		constantBRDF = b;
	}

	void getBRDF(LocalGeo& local, BREF& brdf) {
		brdf = constantBRDF;
	}
}