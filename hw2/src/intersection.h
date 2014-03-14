#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "local_geo.h"
#include "primitive.h"

class Intersection {

public:

	Intersection(LocalGeo& local, Primitive& primitive);

	LocalGeo local;

	Primitive& primitive;

};

#endif