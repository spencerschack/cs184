#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "matrix.h"
#include "vector.h"
#include "point.h"
#include "normal.h"
#include "ray.h"
#include "local_geo.h"

class Transformation {

	Matrix matrix, minvt;

public:

	Transformation();

	Transformation(Matrix& matrix);

	Transformation inverse();

	Vector operator*(const Vector& vector) const;

	Point operator*(const Point& point) const;

	Normal operator*(const Normal& normal) const;

	Ray operator*(const Ray& ray) const;

	LocalGeo operator*(const LocalGeo& local) const;

};

#endif