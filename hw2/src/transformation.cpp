#include "transformation.h"

Transformation::Transformation() { };

Transformation::Transformation(Matrix& matrix) : matrix(matrix) {
	minvt = matrix.inverse().transpose();
};

Transformation Transformation::inverse() {
	Matrix inverse = matrix.inverse();
	return Transformation(inverse);
};

Vector Transformation::operator*(const Vector& vector) const {
	return matrix * vector;
};

Point Transformation::operator*(const Point& point) const {
	return matrix * point;
};

Normal Transformation::operator*(const Normal& normal) const {
	return minvt * normal;
};

Ray Transformation::operator*(const Ray& ray) const {
	return matrix * ray;
};

LocalGeo Transformation::operator*(const LocalGeo& local) const {
	return matrix * local;
};