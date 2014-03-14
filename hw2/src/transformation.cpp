#include "transformation.h"

Transformation::Transformation() { };

Transformation::Transformation(Matrix& matrix) : matrix(matrix) { };

Transformation Transformation::inverse() {
	Matrix inverse = matrix.inverse();
	return Transformation(inverse);
};

Vector Transformation::operator*(const Vector& vector) const {
	exit(1);
};

Point Transformation::operator*(const Point& point) const {
	exit(1);
};

Normal Transformation::operator*(const Normal& normal) const {
	exit(1);
};

Ray Transformation::operator*(const Ray& ray) const {
	exit(1);
};

LocalGeo Transformation::operator*(const LocalGeo& local) const {
	exit(1);
};