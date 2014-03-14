class GeoPri : public Primitive {
public:
	Transformation objToWorld, worldToObj;
	Shape shape;

	GeoPri(Transformation otw, Transformation wto, Shape s) {
		objToWorld = otw;
		worldToObj = wto;
		shape = s;
	}

	bool intersect(Ray& ray, float& t_hit, Intersection& in) {
		Ray oray = worldToObj*ray;
		LocalGeo olocal;
		if (!shape.intersect(oray, thit, olocal)) { return false; }
		in.primitive = this;
		in.local = objToWorld*olocal;
		return true;
	}

	void getBRDF(LocalGeo& local, BRDF& brdf) {
		material.getBRDF(local, brdf);
	}

}