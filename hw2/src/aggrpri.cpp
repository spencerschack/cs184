#include <vector>
#include <limits>

class AggrPri {
public:
	// AggrPri(vector<Primitive*> list); Could be a linked list
	// Length of the above list
	using namespace std;
	vector<Primitive*> priList;
	addPri(Primitive& pri) {
		priList.pushBack(&pri);
	}

	bool intersect(Ray& ray, float& t_hit, Intersection& in) {
		int len = priList.size();
		float t = std::numeric_limits<float>::infinity;
		Primitive toRetPr;
		Intersection toRetIn;
		bool intersected = false;
		for (int i = 0; i < len; i++) {
			Primitive p = priList[i];
			float t_check;
			Intersection in_check;
			in_check.primitive = p;
			if (p.intersect(ray, t_check, in_check)) {
				intersected = true;
				t = min(t, t_check);
				if (t = t_check) {
					toRetIn = in_check;
				}
			}
		}
		if (intersected) {
			in = toRetIn;
			t_hit = t;
			return true;
		}
		return false;
	}

	void getBRDF(LocalGeo& local, BRDF& brdf) {
		exit(1);
	}
}