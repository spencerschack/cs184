#include "local_geo.h"

LocalGeo::LocalGeo() { };

LocalGeo::LocalGeo(Point position, Normal normal) :
	position(position), normal(normal) { };