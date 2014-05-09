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

using namespace std;

class Vector;
class Bone;
class Skeleton;

class Vector {
public:
  float x, y, z;
  Vector() : x(0), y(0), z(0) { }
  Vector(float x, float y, float z) : x(x), y(y), z(z) { }
};

class Bone {
public:
  float length, angleX, angleY;
  Bone(float length) : length(length), angleY(0), angleX(0) { }
  void draw() {

  }
};

class Skeleton {
public:
  vector<Bone> bones;
  void draw() {

  }
};

class Sphere {
public:
  float radius;
  Vector position;
  Sphere(float x, float y, float z, float r) : radius(r) {
    position = Vector(x, y, z);
  }
  void draw() {
    glPushMatrix();
    glColor3f(1.0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glTranslatef(position.x, position.y, position.z);
    GLUquadric* quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluSphere(quadric, radius, 16, 16);
    gluDeleteQuadric(quadric);
    glEndList();
    glEnd();
    glPopMatrix();
  }
};

float rotationX = 0, rotationY = 0,
      positionX = 0, positionZ = 0;
Skeleton skeleton;
Sphere sphere(0, 0, 0, 1.0);

void initScene(){
  skeleton.bones.push_back(Bone(4));
  skeleton.bones.push_back(Bone(3));
  skeleton.bones.push_back(Bone(2));
  skeleton.bones.push_back(Bone(1));
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
  glTranslatef(positionX, 0, positionZ);
  glRotatef(rotationX, 1, 0, 0);
  glRotatef(rotationY, 0, 1, 0);
  skeleton.draw();
  sphere.draw();
  glFlush();
  glutSwapBuffers();
}

void keyPress(unsigned char key, int x, int y) {
  switch(key) {
    case 'w': positionZ += 0.05; break;
    case 'd': positionX += 0.05; break;
    case 's': positionZ -= 0.05; break;
    case 'a': positionX -= 0.05; break;
  }
}

void specialPress(int key, int x, int y) {
  int shifted = glutGetModifiers() & GLUT_ACTIVE_SHIFT;
  switch(key) {
    case GLUT_KEY_UP:    rotationX += 0.5; break;
    case GLUT_KEY_RIGHT: rotationY -= 0.5; break;
    case GLUT_KEY_DOWN:  rotationX -= 0.5; break;
    case GLUT_KEY_LEFT:  rotationY += 0.5; break;
  }
}

void mouseDrag(int x, int y) {
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
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
  glutMotionFunc(mouseDrag);
  glutMainLoop();
  return 0;
}
