#include "transformation.h"

Transformation::Transformation(Matrix& matrix) : matrix(matrix) { };

Vector operator*(Vector& vector) {

};

Point Transformation::operator*(Point& point) {

};

Normal Transformation::operator*(Normal& normal) {

};

Ray Transformation::operator*(Ray& ray) {

};

LocalGeo Transformation::operator*(LocalGeo& local) {

};