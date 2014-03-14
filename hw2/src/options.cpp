#include <fstream>
#include <sstream>

#include "options.h"
#include "scene.h"
#include "matrix.h"
#include "transformation.h"
#include "geometric_primitive.h"
#include "sphere.h"

using namespace std;

string Options::parse_string() {
	if(line.empty()) {
		printf("Not enough arguments.\n");
		fail();
	}
	unsigned int index = line.find(' ');
	if(index == -1) { index = line.length(); }
	string str = line.substr(0, index);
	if(index < line.length()) {
		line = line.substr(index + 1);
	}
	return str;
}

int Options::parse_int() {
	return atoi(parse_string().c_str());
}

unsigned int Options::parse_uint() {
	int n = parse_int();
	if(n < 0) {
		printf("Expected positive number, got: '%d'\n.", n);
		fail();
	}
	return (unsigned int) n;
}

float Options::parse_float() {
	return atof(parse_string().c_str());
}

void Options::fail() {
	commands.close();
	exit(1);
}

Options::Options(char* commands_filename) {
	ifstream commands(commands_filename);
	while(getline(commands, line)) {
		if(line.empty() || line[0] == '#') { continue; }
		string command = parse_string();
		if(command == "size") {
			width = parse_uint();
			height = parse_uint();
		} else if(command == "maxdepth") {
			maxdepth = parse_uint();
		} else if(command == "output") {
			filename = parse_string();
		} else if(command == "camera") {
			camera_position_x = parse_float();
			camera_position_y = parse_float();
			camera_position_z = parse_float();
			camera_direction_x = parse_float();
			camera_direction_y = parse_float();
			camera_direction_z = parse_float();
			camera_up_x = parse_float();
			camera_up_y = parse_float();
			camera_up_z = parse_float();
			camera_fov_y = parse_float();
		} else if(command == "sphere") {
			Matrix translate = Matrix::Translation(
				parse_float(),
				parse_float(),
				parse_float());
			Matrix scale = Matrix::Scale(parse_float());
			Matrix matrix = translate * scale;
			Transformation transformation(matrix);
			Sphere* sphere = new Sphere();
			GeometricPrimitive* primitive = new GeometricPrimitive(transformation, sphere);
			root_primitive.primitives.push_back(primitive);
		} else if (command == "maxverts") { 
			// Always check thet vector v does not grow bigger than this
			maxverts = parse_uint(); 
		} else if (command == "maxvertsnorms") { 
			// Always check thet vector vn does not grow bigger than this
			maxvertsnorms = parse_uint();
		} else if (command == "vertex") {
			// Put this vertex in the vertex vector if size(v) <= maxverts
			if (v.size() <= maxverts) {
				v.push_back(new Point(parse_float(), parse_float(), parse_float()));
			}
		} else if (command == "vertexnormal") {
			// Put the vertexes and vertexnormals in the vertexnormal vector if size(vn) <= maxvertsnorms
			if (vn.size() <= maxvertsnorms) {
				v.push_back(new LocalGeo(
							new Point(parse_float(), parse_float(), parse_float()), 
							new Normal(new Vector(parse_float(), parse_float(), parse_float()));
			}
		} else if (command == "tri") {
			// Take next 3 numbers as vertex indexes
			// And put them into a triangle
			Matrix tr = transformStack.top();
			triangles.push_back(new Triangle(tr * (new Point(v[parse_uint()])),
											 tr * (new Point(v[parse_uint()])),
											 tr * (new Point(v[parse_uint()]))));
			transformStack.pop();
			transformStack.push(tr);
		} else if (command == "trinormal") {
			Matrix tr = transformStack.top();
			trianglesN.push_back(new Triangle(tr * (new LocalGeo(vn[parse_uint()])),
											  tr * (new LocalGeo(vn[parse_uint()])),
											  tr * (new LocalGeo(vn[parse_uint()]))));
			transformStack.pop();
			transformStack.push(tr);
		} else if (command == "translate") {
			// Get translation matrix
			if (push) {
				Matrix toMult = new Matrix::translation(parse_float(), parse_float(), parse_float());
				Matrix toPush = toMult * transformStack.top();
				transformStack.pop();
				transformStack.push(toPush);
			}
		} else if (command == "rotate") {
			// Get the rotation matrix
			if (push) {
				Matrix toMult = new Matrix::rotate(parse_float(), parse_float(), parse_float(), parse_float());
				Matrix toPush = toMult * transformStack.top();
				transformStack.pop();
				transformStack.push(toPush);
			}
		} else if (command == "scale") {
			// Get the scaling matrix
			if (push) {
				Matrix toMult = new Matrix::scale(parse_float(), parse_float(), parse_float());
				Matrix toPush = toMult * transformStack.top();
				transformStack.pop();
				transformStack.push(toPush);
			}
		} else if (command == "pushTransform") {
			// Push the incoming transformations onto transformation stack
			push = true;
		} else if (command == "popTransform") {
			// Pop one matrix off the transformation stack
			push = false;
			transformStack.pop();
			if (transformStack.size() == 0) transformStack.push(im);
		} else if (command == "directional") {
			// Parse next args as light
			
		} else if (command == "point") {
			//	Parse next args as point 
		} else if (command == "attenuation") {
			//	Sets attenuation
		} else if (command == "ambient") {
			//	Sets ambient light source
		} else if (command == "diffuse") {
			//	Sets diffuse coefficients
		} else if (command == "specular") {
			//	Sets specular coefficients
		} else if (command == "shininess") {
			//	Sets shininess coefficient (specular power)
		} else if (command == "emission") {
			// Set emissive color of the surface
		}
	}
	if(width == 0) {
		printf("Must specify a non-zero width, got: '%d'.\n", width);
		fail();
	}
	if(height == 0) {
		printf("Must specify a non-zero height, got: '%d'.\n", height);
		fail();
	}
	if(filename.empty()) {
		printf("Must specify a filename.\n");
		fail();
	}
	if(maxdepth == 0) { maxdepth = 5; }
	commands.close();
}
