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
	Ray ret;
	ret.position = matrix * ray.position;
	ret.direction = matrix * ray.direction;
	return ret;
};

LocalGeo Transformation::operator*(const LocalGeo& local) const {
	LocalGeo ret;
	ret.normal = minvt * local.normal;
	ret.position = matrix * local.position;
	return ret;
};