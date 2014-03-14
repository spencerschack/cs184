#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "matrix.h"

class Transformation {

	Matrix matrix, minvt;

public:

	Transformation();

	Transformation(Matrix& matrix);

	Transformation inverse();

	Vector operator*(const Vector& vector);

	Point operator*(const Point& point);

	Normal operator*(const Normal& normal);

	Ray operator*(const Ray& ray);

	LocalGeo operator*(const LocalGeo& local);

};

#endif