
#include <vector>
#include <iostream>
#include <fstream>
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

class Curve {
public:
  float p0, p1, p2, p3;
  Curve(float p0, float p1, float p2, float p3) :
    p0(p0), p1(p1), p2(p2), p3(p3) { };
  void print() const {
    printf("Curve<p0: %f, p1: %f, p2: %f, p3: %f>", p0, p1, p2, p3);
  }
};

class Patch {
public:
  Curve c0, c1, c2, c3;
  Patch(Curve c0, Curve c1, Curve c2, Curve c3) :
    c0(c0), c1(c1), c2(c2), c3(c3) { }
  void print() const {
    printf("Patch<"
        "c0: Curve<p0: %f, p1: %f, p2: %f, p3: %f>"
        "c2: Curve<p0: %f, p1: %f, p2: %f, p3: %f>"
        "c3: Curve<p0: %f, p1: %f, p2: %f, p3: %f>"
        "c4: Curve<p0: %f, p1: %f, p2: %f, p3: %f>"
      ">",
      c0.p0, c0.p1, c0.p2, c0.p3,
      c1.p0, c1.p1, c1.p2, c1.p3,
      c2.p0, c2.p1, c2.p2, c2.p3,
      c3.p0, c3.p1, c3.p2, c3.p3);
  }
};

typedef enum {
  NullTesselation,
  UniformTesselation,
  AdaptiveTesselation
} TesselationMode;

Viewport viewport;
TesselationMode tesselation = NullTesselation;
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
    case 's':
      break;
    case 'w':
      break;
  }
}

char* parseOption(int argc, char *argv[], int &i) {
  if(++i >= argc) {
    printf("Not enough arguments");
    exit(1);
  } else {
    return argv[i];
  }
}

Curve parseCurve(ifstream &file) {
  float p0, p1, p2, p3;
  file >> p0 >> p1 >> p2 >> p3;
  return Curve(p0, p1, p2, p3);
}

void parseOptions(int argc, char *argv[]) {
  int i;
  char* filename = NULL;
  for(i = 0; i < argc; i++) {
    char* option = argv[i];
    if(option[0] == '-') {
      switch(option[1]) {
        case 'f': {
          filename = parseOption(argc, argv, i);
          break;
        } case 't': {
          char* mode = parseOption(argc, argv, i);
          if(strcmp(mode, "uniform") == 0) {
            tesselation = UniformTesselation;
          } else if(strcmp(mode, "adaptive") == 0) {
            tesselation = AdaptiveTesselation;
          } else {
            printf("Unknown tesselation mode: %s", mode);
            exit(1);
          }
          break;
        } default: {
          printf("Unknown flag: %s", option);
          exit(1);
        }
      }
    } else {
      printf("Expected flag, got: %s", option);
      exit(1);
    }
  }
  if(filename == NULL) {
    printf("Must specify a patch file with '-f'");
    exit(1);
  } else {
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
      printf("Could not open patch file: %s", filename);
      exit(1);
    }
  }
  if(tesselation == NullTesselation) {
    printf("Must specify a tesselation mode with '-t'");
    exit(1);
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
