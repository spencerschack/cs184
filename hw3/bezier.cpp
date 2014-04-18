#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cfloat>

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef OSX
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include <time.h>
#include <math.h>


#define PI 3.14159265
inline float sqr(float x) { return x*x; }

using namespace std;

class Printable;
class Point;
class PointNormal;
class PointDerivative;
class Quad;
class Curve;
class Patch;
class Drawable;

typedef enum {
  UniformTesselation,
  AdaptiveTesselation
} TesselationMode;

typedef enum {
  SmoothShading,
  FlatShading
} ShadingMode;

typedef enum {
  FilledRendering,
  WireframeRendering
} RenderingMode;

class Printable {
public:
  virtual string inspect() const = 0;
  void print() const {
    cout << inspect() << '\n';
  }
};

class Drawable {
public:
  virtual void draw() const = 0;
};

class Point : public Printable {
public:
  float x, y, z;
  Point() : x(0), y(0), z(0) { }
  Point(float x, float y, float z) : x(x), y(y), z(z) { }
  string inspect() const {
    stringstream str;
    str << "Point<"
        << "x: " << x << ", "
        << "y: " << y << ", "
        << "z: " << z << ">";
    return str.str();
  }
  Point operator+(const Point point) const {
    return Point(x + point.x, y + point.y, z + point.z);
  }
  Point operator-(const Point point) const {
    return Point(x - point.x, y - point.y, z - point.z);
  }
  Point operator*(float factor) const {
    return Point(x * factor, y * factor, z * factor);
  }
  Point cross(const Point& point) const {
    return Point(
      y * point.z - z * point.y,
      -x * point.z + z * point.x,
      x * point.y - y * point.x);
  }
};

class PointNormal : public Printable, public Drawable {
public:
  Point point, normal;
  float u, v;
  PointNormal() { }
  PointNormal(Point point, Point normal) : point(point), normal(normal) { }
  PointNormal(Point point, Point normal, float u, float v) :
    point(point), normal(normal), u(u), v(v) { }
  string inspect() const {
    stringstream str;
    str << "PointNormal<"
        << "u: " << u << ", "
        << "v: " << v << ", "
        << "point: " << point.inspect() << ", "
        << "normal: " << normal.inspect() << ">";
    return str.str();
  }
  void draw() const {
    glNormal3f(normal.x, normal.y, normal.z);
    glVertex3f(point.x,  point.y,  point.z);
  }
};

float ambientShading[3] = { 0, 0.5, 0.1 },
  diffuseShading[3] = { 0, 0.8, 0 },
  specularShading[3] = { 0, 0.8, 0 },
  lightPosition[3] = { -5.0, 5.0, -5.0 },
  shininess[1] = { 16.0 };
float subdivisionParameter;
TesselationMode tesselationMode = UniformTesselation;
ShadingMode shadingMode = SmoothShading;
RenderingMode renderingMode = FilledRendering;
Point position(0, 0, -12);
int rotationX = 0, rotationY = 0;
vector<Patch> patches;
vector<Drawable*> faces;

class Quad : public Printable, public Drawable {
public:
  PointNormal p0, p1, p2, p3;
  Quad() { }
  Quad(PointNormal p0, PointNormal p1, PointNormal p2, PointNormal p3) :
    p0(p0), p1(p1), p2(p2), p3(p3) { }
  string inspect() const {
    stringstream str;
    str << "Quad<"
        << "p0: " << p0.inspect() << ", "
        << "p1: " << p1.inspect() << ", "
        << "p2: " << p2.inspect() << ", "
        << "p3: " << p3.inspect() << ">";
    return str.str();
  }
  void draw() const {
    glBegin(GL_QUADS);
    p0.draw();
    p1.draw();
    p2.draw();
    p3.draw();
    glEnd();
  }
};

class Triangle : public Printable, public Drawable {
public:
  PointNormal p0, p1, p2;
  Triangle() { }
  Triangle(PointNormal p0, PointNormal p1, PointNormal p2) :
    p0(p0), p1(p1), p2(p2) { }
  Triangle(Triangle &t) : p0(t.p0), p1(t.p1), p2(t.p2) { }
  string inspect() const {
    stringstream str;
    str << "Triangle<"
        << "p0: " << p0.inspect() << ", "
        << "p1: " << p1.inspect() << ", "
        << "p2: " << p2.inspect() << ">";
    return str.str();
  }
  void draw() const {
    glBegin(GL_TRIANGLES);
    p0.draw();
    p1.draw();
    p2.draw();
    glEnd();
  }
};

class Curve : public Printable {
public:
  Point p0, p1, p2, p3;
  Curve() { }
  Curve(Point p0, Point p1, Point p2, Point p3) :
    p0(p0), p1(p1), p2(p2), p3(p3) { };
  string inspect() const {
    stringstream str;
    str << "Curve<"
        << "p0: " << p0.inspect() << ", "
        << "p1: " << p1.inspect() << ", "
        << "p2: " << p2.inspect() << ", "
        << "p3: " << p3.inspect() << ">";
    return str.str();
  }
  PointNormal interpolate(float u) const {
    float iu = 1.0 - u;
    Point a, b, c, d, e;
    // First interpolation
    a = p0 * iu + p1 * u;
    b = p1 * iu + p2 * u;
    c = p2 * iu + p3 * u;
    // Second interpolation
    d = a * iu + b * u;
    e = b * iu + c * u;
    // Third interpolation
    return PointNormal(d * iu + e * u, (e - d) * 3);
  }
};

class Patch : public Printable {
public:
  Curve u0, u1, u2, u3, v0, v1, v2, v3;
  Patch() { }
  Patch(Curve u0, Curve u1, Curve u2, Curve u3) :
    u0(u0), u1(u1), u2(u2), u3(u3) {
      v0 = Curve(u0.p0, u1.p0, u2.p0, u3.p0);
      v1 = Curve(u0.p1, u1.p1, u2.p1, u3.p1);
      v2 = Curve(u0.p2, u1.p2, u2.p2, u3.p2);
      v3 = Curve(u0.p3, u1.p3, u2.p3, u3.p3);
    }
  string inspect() const {
    stringstream str;
    str << "Patch<"
        << "u0: " << u0.inspect() << ", "
        << "u1: " << u1.inspect() << ", "
        << "u2: " << u2.inspect() << ", "
        << "u3: " << u3.inspect() << ">";
    return str.str();
  }
  void uniformSubdivide() const {
    float u, v, max = 1.0 + FLT_EPSILON;
    for(u = 0; u < max; u += subdivisionParameter) {
      for(v = 0; v < max; v += subdivisionParameter) {
        faces.push_back(new Quad(
          interpolate(u, v),
          interpolate(u + subdivisionParameter, v),
          interpolate(u + subdivisionParameter, v + subdivisionParameter),
          interpolate(u, v + subdivisionParameter)));
      }
    }
  }
  void adaptiveSubdivide() const {
    PointNormal p0 = interpolate(0, 0),
                p1 = interpolate(0, 1),
                p2 = interpolate(1, 1),
                p3 = interpolate(1, 0);
    subdivide(p0, p1, p2);
    subdivide(p2, p3, p0);
  }
  void subdivide(PointNormal v1, PointNormal v2, PointNormal v3) const {
    PointNormal v12, v23, v31;
    bool e12 = edge_test(v1, v2, v12);
    bool e23 = edge_test(v2, v3, v23);
    bool e31 = edge_test(v3, v1, v31);
    if (e12 && e23 && e31) {
      faces.push_back(new Triangle(v1, v2, v3));
    }
    if (!e12 && e23 && e31) {
      subdivide(v1, v12, v3);
      subdivide(v12, v3, v2);
    }
    if (e12 && !e23 && e31) {
      subdivide(v1, v23, v3);
      subdivide(v1, v23, v2);
    }
    if (e12 && e23 && !e31) {
      subdivide(v1, v31, v2);
      subdivide(v31, v3, v2);
    }
    if (!e12 && !e23 && e31) {
      subdivide(v1, v3, v12);
      subdivide(v12, v23, v2);
      subdivide(v3, v12, v23);
    }
    if (!e12 && e23 && !e31) {
      subdivide(v1, v31, v12);
      subdivide(v12, v31, v2);
      subdivide(v3, v2, v31);
    }
    if (e12 && !e23 && !e31) {
      subdivide(v3, v31, v23);
      subdivide(v1, v31, v23);
      subdivide(v1, v2, v23);
    }
    if (!e12 && !e23 && !e31) {
      subdivide(v1, v31, v12);
      subdivide(v2, v23, v12);
      subdivide(v3, v31, v23);
      subdivide(v23, v31, v12);
    }
  }
  bool edge_test(PointNormal v1, PointNormal v2, PointNormal &v12) const {
    v12 = interpolate(0.5*(v1.u + v2.u), 0.5*(v1.v + v2.v));
    Point midp = (v1.point + v2.point)*0.5;
    return (distance(midp, v12.point) < subdivisionParameter);
  }
  float distance(Point p1, Point p2) const {
    return sqrt(pow((p1.x - p2.x), 2.0) + pow((p1.y - p2.y), 2.0) + pow((p1.z - p2.z), 2.0));
  }
  PointNormal interpolate(float u, float v) const {
    PointNormal uPointNormal = interpolateU(u).interpolate(v),
      vPointNormal = interpolateV(v).interpolate(u);
    // The choice between vPointNormal and uPointNormal for the first arg
    // is arbitrary, their points should be the same.
    return PointNormal(vPointNormal.point,
      vPointNormal.normal.cross(uPointNormal.normal), u, v);
  }
  Curve interpolateU(float u) const {
    return Curve(u0.interpolate(u).point, u1.interpolate(u).point,
      u2.interpolate(u).point, u3.interpolate(u).point);
  }
  Curve interpolateV(float v) const {
    return Curve(v0.interpolate(v).point, v1.interpolate(v).point,
      v2.interpolate(v).point, v3.interpolate(v).point);
  }
};

void initScene(){
  for(vector<Patch>::iterator p = patches.begin(); p != patches.end(); ++p) {
    if(tesselationMode == UniformTesselation) {
      p->uniformSubdivide();
    } else if(tesselationMode == AdaptiveTesselation) {
      p->adaptiveSubdivide();
    }
  }
}

void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // Do camera movements here.
  gluPerspective(45, (float) w / h, 0.001, 1000);
  glMatrixMode(GL_MODELVIEW);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  if(shadingMode == SmoothShading) {
    glShadeModel(GL_SMOOTH);
  } else if(shadingMode == FlatShading) {
    glShadeModel(GL_FLAT);
  }
  if(renderingMode == WireframeRendering) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDisable(GL_LIGHTING);
    glColor3f(0.0, 0.5, 0.1);
  } else if(renderingMode == FilledRendering) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientShading);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseShading);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularShading);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glEnable(GL_LIGHT0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ambientShading);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularShading);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  }
  glTranslatef(position.x, position.y, position.z);
  glRotatef(rotationX, 0, 1, 0);
  glRotatef(rotationY, 1, 0, 0);
  for(vector<Drawable*>::iterator f = faces.begin(); f != faces.end(); ++f) {
    (*f)->draw();
  }
  glFlush();
  glutSwapBuffers();
}

void keyPress(unsigned char key, int x, int y) {
  switch(key) {
    case 's': {
      shadingMode = shadingMode == SmoothShading ?
        FlatShading : SmoothShading;
      break;
    } case 'w': {
      renderingMode = renderingMode == FilledRendering ?
        WireframeRendering : FilledRendering;
      break;
    } case 'h': {
      // TODO
      break;
    } case '+': {
      position.z += 0.05;
      break;
    } case '-': {
      position.z -= 0.05;
      break;
    }
  }
}

void specialPress(int key, int x, int y) {
  int shifted = glutGetModifiers() & GLUT_ACTIVE_SHIFT;
  switch(key) {
    case GLUT_KEY_UP: {
      if(shifted) position.y += 0.05;
      else rotationY = rotationY == 359 ? 0 : rotationY + 1;
      break;
    } case GLUT_KEY_RIGHT: {
      if(shifted) position.x += 0.05;
      else rotationX = rotationX == 359 ? 0 : rotationX + 1;
      break;
    } case GLUT_KEY_DOWN: {
      if(shifted) position.y -= 0.05;
      else rotationY = rotationY == 0 ? 359 : rotationY - 1;
      break;
    } case GLUT_KEY_LEFT: {
      if(shifted) position.x -= 0.05;
      else rotationX = rotationX == 0 ? 359 : rotationX - 1;
      break;
    }
  }
}

Point parsePoint(ifstream &file) {
  float x, y, z;
  file >> x >> y >> z;
  return Point(x, y, z);
}

Curve parseCurve(ifstream &file) {
  return Curve(parsePoint(file), parsePoint(file),
    parsePoint(file), parsePoint(file));
}

void parseOptions(int argc, char *argv[]) {
  if(argc < 3 || argc > 4) {
    printf("USAGE: ./bezier inputfile.bez 0.1 [-a]");
    exit(1);
  }
  char* filename = argv[1];
  ifstream file(filename);
  if(file.is_open()) {
    string line;
    getline(file, line);
    int numPatches = atoi(line.c_str());
    file >> skipws; // Ignore all whitespace in the file.
    while(numPatches--) {
      patches.push_back(Patch(
        parseCurve(file), parseCurve(file),
        parseCurve(file), parseCurve(file)));
      getline(file, line); // Throw out line in between patches.
    }
    file.close();
  } else {
    printf("Could not open patch file: %s\n", filename);
    exit(1);
  }
  subdivisionParameter = atof(argv[2]);
  if(argc == 4) {
    char* tesselationOption = argv[3];
    if(strcmp(tesselationOption, "-a") == 0) {
      tesselationMode = AdaptiveTesselation;
    } else {
      printf("Unknown tesselation mode: %s\n", tesselationOption);
      exit(1);
    }
  }
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  parseOptions(argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(400, 400);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Bezier");
  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);
  initScene();
  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyPress);
  glutSpecialFunc(specialPress);
  glutMainLoop();
  return 0;
}
