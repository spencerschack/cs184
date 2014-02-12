#include <cmath>

class LocalGeo{

public:

	Vector pos;
	Normal normal;
	LocalGeo() { }
	LocalGeo(Vector pos, Normal normal): pos(pos), normal(normal) { }
	LocalGeo(LocalGeo* localgeo) {
		pos = localgeo->pos;
		normal = localgeo->normal;
	}
};