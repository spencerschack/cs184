#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iostream>
#include <iterator>

#include "options.h"
#include "scene.h"
#include "matrix.h"
#include "transformation.h"
#include "geometric_primitive.h"
#include "sphere.h"
#include "directional_light.h"
#include "triangle.h"
#include "triangle_n.h"
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

Options::Options(char* commands_filename) : width(640), height(480), maxdepth(5) {
	ifstream commands(commands_filename);
	Material material;
	material.brdf.ka = Color(0.2, 0.2, 0.2);	
	std::stack<Matrix> transformStack;
	std::vector<Point> v, objv;
	std::vector<LocalGeo> vn;
	std::vector<Normal> objvn;
	std::map<char, Point> objChar;
	float im[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
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
			Matrix matrix = translate * scale * transformStack.top();
			Transformation transformation(matrix);
			Sphere* sphere = new Sphere();
			GeometricPrimitive* primitive =
				new GeometricPrimitive(transformation, sphere, material);
			root_primitive.primitives.push_back(primitive);
		} else if (command == "maxverts" || command == "maxvertsnorms") { 
			// We can ignore these because we're using vectors which are
			// dynamically sized. -SS
			// BUT IT ONLY TAKES ONE LINE FOR EACH! -AK
		} else if (command == "vertex") {
			v.push_back(Point(parse_float(), parse_float(), parse_float()));
		} else if (command == "v") {
			objv.push_back(Point(parse_float(), parse_float(), parse_float()));
		} else if (command == "f") {
			string args[3] = {parse_string(), parse_string(), parse_string()};
			std::string str (args[0]);
			std::string str2 ("//");
			std::size_t found = str.find(str2);
			int c, d = 0;
			if (found!=std::string::npos) {
	   			std::vector<std::string> tokens;
				for (c = 0; c < 3; c++) {
				std::string s = args[c];
				std::string delimiter = "//";
					size_t pos = 0;
					std::string token;
					while ((pos = s.find(delimiter)) != std::string::npos) {
					    token = s.substr(0, pos);
					    tokens[d] = token;
					    d++;
					    s.erase(0, pos + delimiter.length());
					}
				}
    			TriangleN* triangle = new TriangleN(
					LocalGeo(objv[std::stoi(tokens[0])], objvn[std::stoi(tokens[1])]),
					LocalGeo(objv[std::stoi(tokens[2])], objvn[std::stoi(tokens[3])]),
					LocalGeo(objv[std::stoi(tokens[4])], objvn[std::stoi(tokens[5])]));
				Transformation transform(transformStack.top());
				GeometricPrimitive* primitive =
					new GeometricPrimitive(transform, triangle, material);
				root_primitive.primitives.push_back(primitive);
			} else {
				Triangle* triangle = new Triangle(Point(objv[std::stoi(args[0])]),
												  Point(objv[std::stoi(args[1])]),
												  Point(objv[std::stoi(args[2])]));
				Transformation transform(transformStack.top());
				GeometricPrimitive* primitive =
					new GeometricPrimitive(transform, triangle, material);
				root_primitive.primitives.push_back(primitive);
			}
			// Check what type of f it is (u_int_v, u_int_v//u_int_vn)
			// Parse accordingly 
		} else if (command == "vn") {
			objvn.push_back(Normal(parse_float(), parse_float(), parse_float()));
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
			Transformation transform(transformStack.top());
			GeometricPrimitive* primitive =
				new GeometricPrimitive(transform, triangle, material);
			root_primitive.primitives.push_back(primitive);
		} else if (command == "trinormal") {
			TriangleN* triangle = new TriangleN(
				LocalGeo(vn[parse_uint()]),
				LocalGeo(vn[parse_uint()]),
				LocalGeo(vn[parse_uint()]));
			Transformation transform(transformStack.top());
			GeometricPrimitive* primitive =
				new GeometricPrimitive(transform, triangle, material);
			root_primitive.primitives.push_back(primitive);
		} else if (command == "translate") {
			// Get translation matrix
			Matrix toMult = Matrix::Translation(parse_float(), parse_float(), parse_float());
			Matrix toPush = transformStack.top() * toMult;
			transformStack.pop();
			transformStack.push(toPush);
		} else if (command == "rotate") {
			// Get the rotation matrix
			Matrix toMult = Matrix::Rotate(parse_float(), parse_float(), parse_float(), parse_float());
			Matrix toPush = transformStack.top() * toMult;
			transformStack.pop();
			transformStack.push(toPush);
		} else if (command == "scale") {
			// Get the scaling matrix
			Matrix toMult = Matrix::Scale(parse_float(), parse_float(), parse_float());
			Matrix toPush = transformStack.top() * toMult;
			transformStack.pop();
			transformStack.push(toPush);
		} else if (command == "pushTransform") {
			// Push the incoming transformations onto transformation stack
			transformStack.push(transformStack.top());
		} else if (command == "popTransform") {
			// Pop one matrix off the transformation stack
			transformStack.pop();
			if(transformStack.size() == 0) { transformStack.push(identity); }
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
			material.brdf.ke.r = parse_float();
			material.brdf.ke.g = parse_float();
			material.brdf.ke.b = parse_float();
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
		} else if(command == "reflectivity") {
			material.brdf.kr.r = parse_float();
			material.brdf.kr.g = parse_float();
			material.brdf.kr.b = parse_float();
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
