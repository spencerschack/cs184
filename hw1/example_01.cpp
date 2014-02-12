
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef OSX
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include <time.h>
#include <math.h>

#include "vector.cpp"
#include "color.cpp"
#include "light.cpp"

#define PI 3.14159265  // Should be used from mathlib
inline float sqr(float x) { return x*x; }

using namespace std;

//****************************************************
// Some Classes
//****************************************************

class Viewport;

class Viewport {
  public:
    int w, h; // width and height
};


//****************************************************
// Global Variables
//****************************************************
Viewport	viewport;

Color* ambientColor  = new Color();
Color* diffuseColor  = new Color();
Color* specularColor = new Color();
float  specularPower = 0;
Light* pointLights[5];
Light* directionalLights[5];
int    numPointLights       = 0;
int    numDirectionalLights = 0;

//****************************************************
// Simple init function
//****************************************************
void initScene(){

  // Nothing to do here for this simple example.

}


//****************************************************
// reshape viewport if the window is resized
//****************************************************
void myReshape(int w, int h) {
  viewport.w = w;
  viewport.h = h;

  glViewport (0,0,viewport.w,viewport.h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, viewport.w, 0, viewport.h);

}


//****************************************************
// A routine to set a pixel by drawing a GL point.  This is not a
// general purpose routine as it assumes a lot of stuff specific to
// this example.
//****************************************************

void setPixel(int x, int y, GLfloat r, GLfloat g, GLfloat b) {
  glColor3f(r, g, b);
  glVertex2f(x + 0.5, y + 0.5); // The 0.5 is to target pixel centers
}

//****************************************************
// Draw a filled circle.  
//****************************************************


void circle(float centerX, float centerY, float radius) {

  glBegin(GL_POINTS);

  int i,    j,
      minI, minJ,
      maxI, maxJ;
  float radiusSquared = sqr(radius);
  Color color;

  minI = max(0, (int) floor(centerX - radius));
  maxI = min(viewport.w - 1, (int) ceil(centerX + radius));

  for (i = minI; i < maxI; i++) {
    maxJ = (int) ceil(sqrt(radiusSquared - sqr(i - centerX)) + centerX);
    minJ = 2 * centerX - maxJ;
    for (j = minJ; j < maxJ; j++) {
      color = Color(ambientColor);
      /*
      for(k = 0; k < numPointLights; k++) {
        color += pointLights[k]->at(x, y);
      }
      for(k = 0; k < numDirectionalLights; k++) {
        color += directionalLights[k]->at(x, y);
      }
      setPixel(i, j, color.r, color.g, color.b);
      */
      setPixel(i, j, color.r, color.g, color.b);
    }
  }

  glEnd();
}
//****************************************************
// function that does the actual drawing of stuff
//***************************************************
void myDisplay() {

  glClear(GL_COLOR_BUFFER_BIT); // clear the color buffer

  glMatrixMode(GL_MODELVIEW); // indicate we are specifying camera transformations
  glLoadIdentity();	

  // Start drawing
  circle(viewport.w / 2.0 , viewport.h / 2.0 , min(viewport.w, viewport.h) / 3.0);

  glFlush();
  glutSwapBuffers(); // swap buffers (we earlier set double buffer)
}

void keyboardFunc(unsigned char key, int x, int y) {
  if(key == 32) {
    exit(0);
  }
}

float parseOption(int &index, int argc, char* argv[]) {
  if(++index < argc) {
    return atof(argv[index]);
  } else {
    printf("Not enough arguments.");
    exit(1);
  }
}

Color* colorFromArgs(int &index, int argc, char* argv[]) {
  float r = parseOption(index, argc, argv);
  float g = parseOption(index, argc, argv);
  float b = parseOption(index, argc, argv);
  return new Color(r, g, b);
}

Light* lightFromArgs(int &index, int argc, char* argv[]) {
  float x = parseOption(index, argc, argv);
  float y = parseOption(index, argc, argv);
  float z = parseOption(index, argc, argv);
  float r = parseOption(index, argc, argv);
  float g = parseOption(index, argc, argv);
  float b = parseOption(index, argc, argv);
  return new Light(x, y, z, r, g, b);
}

void parseOptions(int argc, char* argv[]) {
  char* option;
  // Must start from 1, don't want to parse the program name.
  for(int i = 1; i < argc; i++) {
    option = argv[i];

    // Ambient color coefficients of the sphere material.
    if(strcmp(option, "-ka") == 0) {
      ambientColor = colorFromArgs(i, argc, argv);

    // Diffuse color coefficients of the sphere material.
    } else if(strcmp(option, "-kd") == 0) {
      diffuseColor = colorFromArgs(i, argc, argv);

    // Specfular color coefficients of the sphere material.
    } else if(strcmp(option, "-ks") == 0) {
      specularColor = colorFromArgs(i, argc, argv);

    // Power coefficient on the specular term.
    } else if(strcmp(option, "-sp") == 0) {
      specularPower = parseOption(i, argc, argv);

    // Point light.
    } else if(strcmp(option, "-pl") == 0) {
      if(numPointLights < 4) {
        pointLights[numPointLights++] = lightFromArgs(i, argc, argv);
      } else {
        printf("Too many point lights.");
        exit(1);
      }

    // Directional light.
    } else if(strcmp(option, "-dl") == 0) {
      if(numDirectionalLights < 4) {
        directionalLights[numDirectionalLights++] = lightFromArgs(i, argc, argv);
      } else {
        printf("Too many directional lights.");
        exit(1);
      }

    } else {
      printf("Incorrect command line argument.");
      exit(1);
    }
  }
}

//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
int main(int argc, char *argv[]) {

  parseOptions(argc, argv);

  //This initializes glut
  glutInit(&argc, argv);

  //This tells glut to use a double-buffered window with red, green, and blue channels 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  // Initalize theviewport size
  viewport.w = 400;
  viewport.h = 400;

  //The size and position of the window
  glutInitWindowSize(viewport.w, viewport.h);
  glutInitWindowPosition(0,0);
  glutCreateWindow(argv[0]);

  glutKeyboardFunc(keyboardFunc);

  initScene();							// quick function to set up scene

  glutDisplayFunc(myDisplay);				// function to run when its time to draw something
  glutReshapeFunc(myReshape);				// function to run when the window gets resized

  glutMainLoop();							// infinite loop that will keep drawing and resizing
  // and whatever else

  return 0;
}








