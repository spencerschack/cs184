
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cfloat>

#include <sys/time.h>

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

class Viewport;
class Printable;
class Point;
class PointNormal;
class PointDerivative;
class Quad;
class Curve;
class Patch;

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

class Viewport {
public:
  int w, h;
};

class Printable {
public:
  virtual string inspect() const = 0;
  void print() const {
    cout << inspect() << '\n';
  }
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
  Point operator+(Point point) const {
    return Point(x + point.x, y + point.y, z + point.z);
  }
  Point operator-(Point point) const {
    return Point(x - point.x, y - point.y, z - point.z);
  }
  Point operator*(float factor) const {
    return Point(x * factor, y * factor, z * factor);
  }
};

class PointNormal : public Printable {
public:
  Point point, normal;
  PointNormal() { }
  PointNormal(Point point, Point normal) : point(point), normal(normal) { }
  string inspect() const {
    stringstream str;
    str << "PointNormal<"
        << "point: " << point.inspect() << ", "
        << "normal: " << normal.inspect() << ">";
    return str.str();
  }
};

class PointDerivative : public Printable {
public:
  Point point, derivative;
  PointDerivative() { }
  PointDerivative(Point point, Point derivative) :
    point(point), derivative(derivative) { }
  string inspect() const {
    stringstream str;
    str << "PointDerivative<"
        << "point: " << point.inspect() << ", "
        << "derivative: " << derivative.inspect() << ">";
    return str.str();
  }
};

Viewport viewport;
float subdivisionParameter;
TesselationMode tesselationMode = UniformTesselation;
ShadingMode shadingMode = SmoothShading;
RenderingMode renderingMode = FilledRendering;
Point position(0, 0, -5);
int rotationX = 0, rotationY = 0;
vector<Patch> patches;
vector<Quad> quads;

class Quad : public Printable {
public:
  Point p0, p1, p2, p3;
  Quad() { }
  Quad(Point p0, Point p1, Point p2, Point p3) :
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
  Point interpolate(float u) const {
    float iu = 1.0 - u;
    Point a, b;
    a = p0 * iu + p1 * u;
    b = p2 * iu + p3 * u;
    return a * iu + b * u;
  }
};

class Patch : public Printable {
public:
  Curve c0, c1, c2, c3;
  Patch() { }
  Patch(Curve c0, Curve c1, Curve c2, Curve c3) :
    c0(c0), c1(c1), c2(c2), c3(c3) { }
  string inspect() const {
    stringstream str;
    str << "Patch<"
        << "c0: " << c0.inspect() << ", "
        << "c1: " << c1.inspect() << ", "
        << "c2: " << c2.inspect() << ", "
        << "c3: " << c3.inspect() << ">";
    return str.str();
  }
  void subdivide() const {
    float max = 1.0 + subdivisionParameter + FLT_EPSILON;
    float u, v;
    Point lastFrontPoint, lastBackPoint, currentFrontPoint, currentBackPoint;
    Curve currentCurve, lastCurve = interpolate(0);
    for(u = subdivisionParameter; u < max; u += subdivisionParameter) {
      currentCurve = interpolate(u);
      lastBackPoint = lastCurve.interpolate(0);
      lastFrontPoint = currentCurve.interpolate(0);
      for(v = subdivisionParameter; v < max; v += subdivisionParameter) {
        currentFrontPoint = currentCurve.interpolate(v);
        currentBackPoint = lastCurve.interpolate(v);
        quads.push_back(Quad(lastBackPoint, currentBackPoint,
          currentFrontPoint, lastFrontPoint));
        lastFrontPoint = currentFrontPoint;
        lastBackPoint = currentBackPoint;
      }
      lastCurve = currentCurve;
    }
  }
  Curve interpolate(float u) const {
    return Curve(c0.interpolate(u), c1.interpolate(u),
      c2.interpolate(u), c3.interpolate(u));
  }
};

void initScene(){
  for(vector<Patch>::iterator p = patches.begin(); p != patches.end(); ++p) {
    p->subdivide();
  }
}

void reshape(int w, int h) {
  viewport.w = w;
  viewport.h = h;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // Do camera movements here.
  gluPerspective(45, w / h, 0.1, 100);
  glMatrixMode(GL_MODELVIEW);
}

void display() {
  if(renderingMode == WireframeRendering) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else if(renderingMode == FilledRendering) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(position.x, position.y, position.z);
  glRotatef(rotationX, 0, 1, 0);
  glRotatef(rotationY, 1, 0, 0);
  glColor3f(0.0, 0.0, 1.0);
  for(vector<Quad>::iterator q = quads.begin(); q != quads.end(); ++q) {
    Quad quad = *q;
    glBegin(GL_QUADS);
    glVertex3f(quad.p0.x, quad.p0.y, quad.p0.z);
    glVertex3f(quad.p1.x, quad.p1.y, quad.p1.z);
    glVertex3f(quad.p2.x, quad.p2.y, quad.p2.z);
    glVertex3f(quad.p3.x, quad.p3.y, quad.p3.z);
    glEnd();
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
      if(shifted) rotationY = rotationY == 359 ? 0 : rotationY + 1;
      else position.y += 0.05;
      break;
    } case GLUT_KEY_RIGHT: {
      if(shifted) rotationX = rotationX == 359 ? 0 : rotationX + 1;
      else position.x += 0.05;
      break;
    } case GLUT_KEY_DOWN: {
      if(shifted) rotationY = rotationY == 0 ? 359 : rotationY - 1;
      else position.y -= 0.05;
      break;
    } case GLUT_KEY_LEFT: {
      if(shifted) rotationX = rotationX == 0 ? 359 : rotationX - 1;
      else position.x -= 0.05;
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
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  viewport.w = 400;
  viewport.h = 400;
  glutInitWindowSize(viewport.w, viewport.h);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Bezier");
  initScene();
  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyPress);
  glutSpecialFunc(specialPress);
  glutMainLoop();
  return 0;
}
