
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
#include "bitmap_image.hpp"


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


#ifdef _WIN32
static DWORD lastTime;
#else
static struct timeval lastTime;
#endif

#define PI 3.14159265

using namespace std;

//Draws the 3D scene
void drawSphere(bool isFile) {
  int i, j, l;
  float x, y, r, dot;
  Color color;
  Ray ray;
  Vector* intersection;
  Normal normal, light_normal, reflection, viewer;
  Light* light;

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
        //printf("i+0.5 = %f, j+0.5 = %f\n", i + 0.5, j + 0.5);
        // Need to adjust this according to bool isFile
        glVertex2f(i + 0.5, j + 0.5);
      }
    }
  }
}

//*****************************************************************
// function that does the actual drawing and file writing of stuff
//*****************************************************************

void drawToImage()
{
  //Clear information from last draw
  //glClear(GL_COLOR_BUFFER_BIT);
 
  glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
  glLoadIdentity(); //Reset the drawing perspective 

  // glEnable(GL_DEPTH_TEST);
 
  static unsigned char texture[3 * 400 * 400];
  static unsigned int texture_id;
 
  // Texture setting
  // glEnable(GL_TEXTURE_2D);
  // glGenTextures(1, &texture_id);
  // glBindTexture(GL_TEXTURE_2D, texture_id);
  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 400, 400, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
 
  //glLoadIdentity();
  glTranslatef(0, 0, -10);  
 
  /* Define a view-port adapted to the texture */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(20, 1, 5, 15);
  glViewport(0, 0, 400, 400);
  glMatrixMode(GL_MODELVIEW);
 
  /* Render to buffer */
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT); 
 
  glColor3f(1.0,0.0,1.0);
 
  glBegin(GL_TRIANGLES);
  
  glVertex2f( 0.0f, 1.0f);             
 
  glVertex2f(-1.0f,-1.0f);             
 
  glVertex2f( 1.0f,-1.0f);             
 
  //drawSphere(true);

  glEnd();            
 
  glEnd();  
  glFlush();
  // Image Writing  
  unsigned char* imageData = (unsigned char *)malloc((int)(400*400*(3)));
  glReadPixels(0, 0, 400, 400, GL_RGB, GL_UNSIGNED_BYTE, imageData);
  //write 
  bitmap_image image(400,400);
  image_drawer draw(image);
 
  for (unsigned int i = 0; i < image.width(); ++i)
  {
    for (unsigned int j = 0; j < image.height(); ++j)
    {
      image.set_pixel(i,j,*(++imageData),*(++imageData),*(++imageData));    
    }
  }
 
  image.save_image(filename);
  glutSwapBuffers(); 
}

//****************************************************
// function that does the actual drawing of stuff
//***************************************************

void draw() {

  glClear(GL_COLOR_BUFFER_BIT); // clear the color buffer

  glMatrixMode(GL_MODELVIEW); // indicate we are specifying camera transformations
  glLoadIdentity();
  glBegin(GL_POINTS);

  drawSphere(false);

  glEnd();

  glFlush();
  glutSwapBuffers(); // swap buffers (we earlier set double buffer)
}

void keyboardFunc(unsigned char key, int x, int y) {
  if(key == 32) exit(0);
}

char* getOption(int &index, int argc, char* argv[]) {
  if(++index < argc) {
    return argv[index];
  } else {
    printf("Not enough arguments.\n");
    exit(1);
  }
}

float parseOption(int &index, int argc, char* argv[]) {
  return atof(getOption(index, argc, argv));
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
      filename = getOption(i, argc, argv);

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
  //printf("%s", filename);

  //This initializes glut
  glutInit(&argc, argv);

  //This tells glut to use a double-buffered window with red, green, and blue channels 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  // Initalize theviewport size
  viewport.w = 400;
  viewport.h = 400;

  //The size and position of the window
  glutInitWindowSize(viewport.w, viewport.h);
  

  if (filename != NULL) {
    glutCreateWindow("Test"); 
    drawToImage();
  } else {
    glutInitWindowPosition(0,0);
    glutCreateWindow(argv[0]);
    glutKeyboardFunc(keyboardFunc);

    init(); // quick function to set up scene

    glutDisplayFunc(draw); // function to run when its time to draw something
    glutReshapeFunc(resize); // function to run when the window gets resized

    glutMainLoop(); // infinite loop that will keep drawing and resizing
  }
  return 0;
}








