#ifndef LOCAL_GEO_H
#define LOCAL_GEO_H

#include "point.h"
#include "normal.h"

class LocalGeo {

public:

	Point position;

	Normal normal;

	LocalGeo();

	LocalGeo(Point position, Normal normal);

};

#endif