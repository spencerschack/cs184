#include "transformation.h"

Transformation::Transformation() { };

Transformation::Transformation(Matrix& matrix) : matrix(matrix) { };

Transformation Transformation::inverse() {
	Matrix inverse = matrix.inverse();
	return Transformation(inverse);
};

Vector operator*(const Vector& vector) {
	exit(1);
};

Point Transformation::operator*(const Point& point) {
	exit(1);
};

Normal Transformation::operator*(const Normal& normal) {
	exit(1);
};

Ray Transformation::operator*(const Ray& ray) {
	exit(1);
};

LocalGeo Transformation::operator*(const LocalGeo& local) {
	exit(1);
};