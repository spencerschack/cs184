
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

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
  Point(float x, float y, float z) : x(x), y(y), z(z) { }
  string inspect() const {
    stringstream str;
    str << "Point<"
        << "x: " << x << ", "
        << "y: " << y << ", "
        << "z: " << z << ">";
    return str.str();
  }
};

class Curve : public Printable {
public:
  Point p0, p1, p2, p3;
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
};

class Patch : public Printable {
public:
  Curve c0, c1, c2, c3;
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
};

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

Viewport viewport;
float subdivisionParameter;
TesselationMode tesselationMode = UniformTesselation;
ShadingMode shadingMode = SmoothShading;
RenderingMode renderingMode = FilledRendering;
vector<Patch> patches;

void initScene(){

}

void reshape(int w, int h) {
  viewport.w = w;
  viewport.h = h;

  glViewport (0,0,viewport.w,viewport.h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, viewport.w, 0, viewport.h);
}

void setPixel(int x, int y, GLfloat r, GLfloat g, GLfloat b) {
  glColor3f(r, g, b);
  glVertex2f(x + 0.5, y + 0.5);
}

void circle(float centerX, float centerY, float radius) {
  // Draw inner circle
  glBegin(GL_POINTS);

  // We could eliminate wasted work by only looping over the pixels
  // inside the sphere's radius.  But the example is more clear this
  // way.  In general drawing an object by loopig over the whole
  // screen is wasteful.

  int i,j;  // Pixel indices

  int minI = max(0,(int)floor(centerX-radius));
  int maxI = min(viewport.w-1,(int)ceil(centerX+radius));

  int minJ = max(0,(int)floor(centerY-radius));
  int maxJ = min(viewport.h-1,(int)ceil(centerY+radius));



  for (i=0;i<viewport.w;i++) {
    for (j=0;j<viewport.h;j++) {

      // Location of the center of pixel relative to center of sphere
      float x = (i+0.5-centerX);
      float y = (j+0.5-centerY);

      float dist = sqrt(sqr(x) + sqr(y));

      if (dist<=radius) {

        // This is the front-facing Z coordinate
        float z = sqrt(radius*radius-dist*dist);

        setPixel(i,j, 1.0, 0.0, 0.0);

        // This is amusing, but it assumes negative color values are treated reasonably.
        // setPixel(i,j, x/radius, y/radius, z/radius );
      }


    }
  }

  glEnd();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  circle(viewport.w / 2.0 , viewport.h / 2.0 , min(viewport.w, viewport.h) / 3.0);

  glFlush();
  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
  switch(key) {
    case 's': {
      shadingMode = shadingMode == SmoothShading ? FlatShading : SmoothShading;
      break;
    } case 'w': {
      renderingMode = renderingMode == FilledRendering ? FilledRendering : WireframeRendering;
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
  glutInitWindowPosition(0,0);
  glutCreateWindow(argv[0]);
  initScene();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}
