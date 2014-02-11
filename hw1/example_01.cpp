
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
  glVertex2f(x + 0.5, y + 0.5);   // The 0.5 is to target pixel
  // centers 
  // Note: Need to check for gap
  // bug on inst machines.
}

//****************************************************
// Draw a filled circle.  
//****************************************************


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

        // setPixel(i,j, 1.0, 0.0, 0.0);

        // This is amusing, but it assumes negative color values are treated reasonably.
        setPixel(i,j, x/radius, y/radius, z/radius );
      }


    }
  }


  glEnd();
}
//****************************************************
// function that does the actual drawing of stuff
//***************************************************
void myDisplay() {

  glClear(GL_COLOR_BUFFER_BIT);				// clear the color buffer

  glMatrixMode(GL_MODELVIEW);			        // indicate we are specifying camera transformations
  glLoadIdentity();				        // make sure transformation is "zero'd"


  // Start drawing
  circle(viewport.w / 2.0 , viewport.h / 2.0 , min(viewport.w, viewport.h) / 3.0);

  glFlush();
  glutSwapBuffers();					// swap buffers (we earlier set double buffer)
}

void parseOptions(int argc, char* argv[]) {
  char* option;
  // Must start from 1, don't want to parse the program name.
  for(int i = 1; i < argc; i++) {
    option = argv[i];

    // Ambient color coefficients of the sphere material.
    if(strcmp(option, "-ka") == 0) {
      float r = atof(argv[++i]); // [0.0, 1.0]
      float g = atof(argv[++i]); // [0.0, 1.0]
      float b = atof(argv[++i]); // [0.0, 1.0]

    // Diffuse color coefficients of the sphere material.
    } else if(strcmp(option, "-kd") == 0) {
      float r = atof(argv[++i]); // [0.0, 1.0]
      float g = atof(argv[++i]); // [0.0, 1.0]
      float b = atof(argv[++i]); // [0.0, 1.0]

    // Specfular color coefficients of the sphere material.
    } else if(strcmp(option, "-ks") == 0) {
      float r = atof(argv[++i]); // [0.0, 1.0]
      float g = atof(argv[++i]); // [0.0, 1.0]
      float b = atof(argv[++i]); // [0.0, 1.0]

    // Power coefficient on the specular term.
    } else if(strcmp(option, "-sp") == 0) {
      float specPower = atof(argv[++i]); // [0.0, max_float]

    // Point light.
    } else if(strcmp(option, "-pl") == 0) {
      float x = atof(argv[++i]); // [0.0, max_float]
      float y = atof(argv[++i]); // [0.0, max_float]
      float z = atof(argv[++i]); // [0.0, max_float]
      float r = atof(argv[++i]); // [0.0, max_float]
      float g = atof(argv[++i]); // [0.0, max_float]
      float b = atof(argv[++i]); // [0.0, max_float]

    // Directional light.
    } else if(strcmp(option, "-dl") == 0) {
      float x = atof(argv[++i]); // [0.0, max_float]
      float y = atof(argv[++i]); // [0.0, max_float]
      float z = atof(argv[++i]); // [0.0, max_float]
      float r = atof(argv[++i]); // [0.0, max_float]
      float g = atof(argv[++i]); // [0.0, max_float]
      float b = atof(argv[++i]); // [0.0, max_float]

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

  initScene();							// quick function to set up scene

  glutDisplayFunc(myDisplay);				// function to run when its time to draw something
  glutReshapeFunc(myReshape);				// function to run when the window gets resized

  glutMainLoop();							// infinite loop that will keep drawing and resizing
  // and whatever else

  return 0;
}








