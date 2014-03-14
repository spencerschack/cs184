#include "transformation.h"

Transformation::Transformation(Matrix& matrix) : matrix(matrix) { };

Transformation Transformation::inverse() {
	return Transformation(matrix.inverse());
};

Vector operator*(Vector& vector) {
	exit(1);
};

Point Transformation::operator*(Point& point) {
	exit(1);
};

Normal Transformation::operator*(Normal& normal) {
	exit(1);
};

Ray Transformation::operator*(Ray& ray) {
	exit(1);
};

LocalGeo Transformation::operator*(LocalGeo& local) {
	exit(1);
};