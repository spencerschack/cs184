#include "intersection.h"

Intersection::Intersection() { };

Intersection::Intersection(LocalGeo& local, Primitive* primitive) :
	local(local), primitive(primitive) { };

Intersection Intersection::operator=(Intersection& in) {
	local = in.local;
	primitive = in.primitive;
	return *this;
}