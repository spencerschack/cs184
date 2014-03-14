#include <fstream>
#include <sstream>
#include <vector>

#include "options.h"
#include "scene.h"
#include "matrix.h"
#include "transformation.h"
#include "geometric_primitive.h"
#include "sphere.h"
#include "directional_light.h"
#include "point_light.h"

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
		printf("Expected non-negative number, got: '%d'\n.", n);
		fail();
	}
	return (unsigned int) n;
}

unsigned int Options::parse_pint() {
	int n = parse_int();
	if(n <= 0) {
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
	Material material;
	material.brdf.ka = Color(0.2, 0.2, 0.2);	
	std::stack<Matrix> transformStack;
	std::vector<Point> v;
	std::vector<LocalGeo> vn;
	Matrix identity = Matrix(im);
	transformStack.push(identity);
	while(getline(commands, line)) {
		if(line.empty() || line[0] == '#') { continue; }
		string command = parse_string();
		if(command == "size") {
			width = parse_pint();
			height = parse_pint();
		} else if(command == "maxdepth") {
			maxdepth = parse_pint();
		} else if(command == "output") {
			filename = parse_string();
		} else if(command == "camera") {
			camera_position.x = parse_float();
			camera_position.y = parse_float();
			camera_position.z = parse_float();
			camera_direction.x = parse_float();
			camera_direction.y = parse_float();
			camera_direction.z = parse_float();
			camera_up.x = parse_float();
			camera_up.y = parse_float();
			camera_up.z = parse_float();
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
			GeometricPrimitive* primitive =
				new GeometricPrimitive(transformation, sphere, material);
			root_primitive.primitives.push_back(primitive);
		} else if (command == "maxverts" || command == "maxvertsnorms") { 
			// We can ignore these because we're using vectors which are
			// dynamically sized.
		} else if (command == "vertex") {
			v.push_back(Point(parse_float(), parse_float(), parse_float()));
		} else if (command == "vertexnormal") {
			vn.push_back(LocalGeo(
				Point(parse_float(), parse_float(), parse_float()), 
				Normal(parse_float(), parse_float(), parse_float())));
		} else if (command == "tri") {
			// Take next 3 numbers as vertex indexes
			// And put them into a triangle
			Triangle* triangle = new Triangle(
				Point(v[parse_uint()]),
				Point(v[parse_uint()]),
				Point(v[parse_uint()]));
			GeometricPrimitive* primitive =
				new GeometricPrimitive(transformStack.top(), triangle, material);
			root_primitive.primitives.push_back(primitive);
		} else if (command == "trinormal") {
			Triangle* triangle = new Triangle(
				LocalGeo(vn[parse_uint()]),
				LocalGeo(vn[parse_uint()]),
				LocalGeo(vn[parse_uint()]));
			GeometricPrimitive* primitive =
				new GeometricPrimitive(transformStack.top(), triangle, material);
			root_primitive.primitives.push_back(primitive);
		} else if (command == "translate") {
			// Get translation matrix
			if (push) {
				Matrix toMult = Matrix::Translation(parse_float(), parse_float(), parse_float());
				Matrix toPush = toMult * transformStack.top();
				transformStack.pop();
				transformStack.push(toPush);
			}
		} else if (command == "rotate") {
			// Get the rotation matrix
			if (push) {
				Matrix toMult = Matrix::Rotate(parse_float(), parse_float(), parse_float(), parse_float());
				Matrix toPush = toMult * transformStack.top();
				transformStack.pop();
				transformStack.push(toPush);
			}
		} else if (command == "scale") {
			// Get the scaling matrix
			if (push) {
				Matrix toMult = Matrix::Scale(parse_float(), parse_float(), parse_float());
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
			if (transformStack.size() == 0) transformStack.push(identity);
		} else if (command == "point") {
			Light* light = new PointLight(
				parse_float(),
				parse_float(),
				parse_float(),
				parse_float(),
				parse_float(),
				parse_float());
			lights.push_back(light);
		} else if (command == "attenuation") {
			//	Sets attenuation
		} else if (command == "emission") {
			// Set emissive color of the surface
		} else if(command == "diffuse") {
			material.brdf.kd.r = parse_float();
			material.brdf.kd.g = parse_float();
			material.brdf.kd.b = parse_float();
		} else if(command == "ambient") {
			material.brdf.ka.r = parse_float();
			material.brdf.ka.g = parse_float();
			material.brdf.ka.b = parse_float();
		} else if(command == "specular") {
			material.brdf.ks.r = parse_float();
			material.brdf.ks.g = parse_float();
			material.brdf.ks.b = parse_float();
		} else if(command == "shininess") {
			material.brdf.sp = parse_float();
		} else if(command == "directional") {
			Light* light = new DirectionalLight(
				parse_float(),
				parse_float(),
				parse_float(),
				parse_float(),
				parse_float(),
				parse_float());
			lights.push_back(light);
		} else if(command == "antialias") {
			antialias = true;
		} else {
			cout << "Unknown command: '" << command << "'.\n";
			exit(1);
		}
	}
	if(filename.empty()) {
		printf("Must specify a filename.\n");
		fail();
	}
	commands.close();
}
