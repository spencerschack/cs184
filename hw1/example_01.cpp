
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
#include "normal.cpp"
#include "ray.cpp"
#include "color.cpp"
#include "light.cpp"
#include "brdf.cpp"
#include "localgeo.cpp"
#include "matrix.cpp"
#include "sample.cpp"
#include "sphere.cpp"


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

Normal* camera = new Normal(0, 0, -1);
Sphere* sphere = new Sphere();
Light* pointLights[5];
Light* directionalLights[5];
int    numPointLights       = 0;
int    numDirectionalLights = 0;
char*  filename = NULL;

//****************************************************
// Simple init function
//****************************************************
void init() {

}

//****************************************************
// reshape viewport if the window is resized
//****************************************************
void resize(int w, int h) {
  viewport.w = w;
  viewport.h = h;

  glViewport(0, 0, viewport.w, viewport.h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, viewport.w, 0, viewport.h);

}

//****************************************************
// function that does the actual drawing of stuff
//***************************************************
void draw() {

  glClear(GL_COLOR_BUFFER_BIT); // clear the color buffer

  glMatrixMode(GL_MODELVIEW); // indicate we are specifying camera transformations
  glLoadIdentity();	

  int i, j, l;
  float x, y, r, dot;
  Color color;
  Ray ray;
  Vector* intersection;
  Normal normal, light_normal, reflection, viewer;
  Light* light;

  glBegin(GL_POINTS);


  // What happens if a point/directional light source is behind sphere?
  for(i = 0; i < viewport.w; i++) {
    for(j = 0; j < viewport.h; j++) {

      r = min(viewport.w, viewport.h) / 2.25;
      x = i / r - (viewport.w / 2.0 / r);
      y = j / r - (viewport.h / 2.0 / r);
      ray = Ray(Vector(x, y, 2.0), camera);
      intersection = sphere->intersect(ray);

      if(intersection != NULL) {

        normal = sphere->normal(intersection);
        color = Color(sphere->ambientColor);

        for(l = 0; l < numPointLights; l++) {
          // Diffuse
          light = pointLights[l];
          light_normal = Normal(*intersection - &light->position);
          dot = max(0.0f, normal.dot(&light_normal));
          color += *(sphere->diffuseColor * &light->color) * dot;
          // Specular
          reflection = Normal(light_normal.vector()->reflect(normal.vector()));
          viewer = Normal(ray.position - intersection);
          dot = pow(max(0.0f, reflection.dot(&viewer)), sphere->specularPower);
          color += *(sphere->specularColor * &light->color) * dot;
        }

        for (l = 0; l < numDirectionalLights; l++) {
          // Diffuse
          light = directionalLights[l];
          light_normal = Normal(&light->position);
          dot = max(0.0f, normal.dot(&light_normal));
          color += *(sphere->diffuseColor * &light->color) * dot;
          // Specular
          reflection = Normal(light_normal.vector()->reflect(normal.vector()));
          viewer = Normal(ray.position - intersection);
          dot = pow(max(0.0f, reflection.dot(&viewer)), sphere->specularPower);
          color += *(sphere->specularColor * &light->color) * dot;
        }

        glColor3f(color.r, color.g, color.b);
        glVertex2f(i + 0.5, j + 0.5);
      }
    }
  }

  glEnd();

  glFlush();
  glutSwapBuffers(); // swap buffers (we earlier set double buffer)
}

void keyboardFunc(unsigned char key, int x, int y) {
  if(key == 32) exit(0);
}

float parseOption(int &index, int argc, char* argv[]) {
  if(++index < argc) {
    return atof(argv[index]);
  } else {
    printf("Not enough arguments.\n");
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
  float x = -parseOption(index, argc, argv);
  float y = -parseOption(index, argc, argv);
  float z = -parseOption(index, argc, argv);
  float r = parseOption(index, argc, argv);
  float g = parseOption(index, argc, argv);
  float b = parseOption(index, argc, argv);
  return new Light(x, y, z, r, g, b);
}

void parseOptions(int argc, char* argv[]) {
  char* option;
  // Must start from 1, don't want to parse the program name.
  for(int i = 1; i < argc; i++) {
  //int i = 1;
  //while (i < argc) {
    option = argv[i];

    // Ambient color coefficients of the sphere material.
    if(strcmp(option, "-ka") == 0) {
      sphere->ambientColor = colorFromArgs(i, argc, argv);
      //i += 4;
    // Diffuse color coefficients of the sphere material.
    } else if(strcmp(option, "-kd") == 0) {
      sphere->diffuseColor = colorFromArgs(i, argc, argv);
      //i += 4;
    // Specfular color coefficients of the sphere material.
    } else if(strcmp(option, "-ks") == 0) {
      sphere->specularColor = colorFromArgs(i, argc, argv);
      //i += 4;
    // Power coefficient on the specular term.
    } else if(strcmp(option, "-sp") == 0) {
      sphere->specularPower = parseOption(i, argc, argv);
      //i += 2;
    // Point light.
    } else if(strcmp(option, "-pl") == 0) {
      if(numPointLights < 4) {
        pointLights[numPointLights++] = lightFromArgs(i, argc, argv);
        //i += 7;
      } else {
        printf("Too many point lights.\n");
        exit(1);
      }

    // Directional light.
    } else if(strcmp(option, "-dl") == 0) {
      if(numDirectionalLights < 4) {
        directionalLights[numDirectionalLights++] = lightFromArgs(i, argc, argv);
        //i += 7;
      } else {
        printf("Too many directional lights.\n");
        exit(1);
      }

    // Export to file.
    } else if(strcmp(option, "-f") == 0) {
      filename = argv[++i];

    } else {
      printf("Incorrect command line argument.\n");
      exit(1);
    }
  }
}

//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
int main(int argc, char *argv[]) {

  parseOptions(argc, argv);
  printf("%s", filename);

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

  init(); // quick function to set up scene

  glutDisplayFunc(draw); // function to run when its time to draw something
  glutReshapeFunc(resize); // function to run when the window gets resized

  glutMainLoop(); // infinite loop that will keep drawing and resizing

  return 0;
}








