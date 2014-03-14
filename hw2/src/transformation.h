#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "matrix.h"

class Transformation {

	Matrix matrix, minvt;

public:

	Transformation(Matrix& matrix);

	Transformation inverse();

	Vector operator*(Vector& vector);

	Point operator*(Point& point);

	Normal operator*(Normal& normal);

	Ray operator*(Ray& ray);

	LocalGeo operator*(LocalGeo& local);

};

#endif