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
class Normal;
class Bone;
class Skeleton;

class Vector {
public:
  float x, y, z;
  Vector() : x(0), y(0), z(0) { }
  Vector(float x, float y, float z) : x(x), y(y), z(z) { }
  Vector(const Vector& v) : x(v.x), y(v.y), z(v.z) { }
  Vector operator+(const Vector v) const {
    return Vector(x + v.x, y + v.y, z + v.z);
  }
  Vector operator-(const Vector v) const {
    return Vector(x - v.x, y - v.y, z - v.z);
  }
  Vector cross(const Vector v) const {
    return Vector(
      y * v.z - z * v.y,
      -x * v.z + z * v.x,
      x * v.y - y * v.x);
  }
  float dot(const Vector& v) const {
    return x * v.x + y * v.y + z * v.z;
  }
  Vector operator*(float factor) {
    return Vector(factor * x, factor * y, factor * z);
  }
  Vector operator/(float factor) {
    return Vector(factor / x, factor / y, factor / z);
  }
  float distance(const Vector& v) const {
    return sqrt(pow(x - v.x, 2) + pow(y - v.y, 2) + pow(z - v.z, 2));
  }
  float magnitude() const {
    return sqrt(x * x + y * y + z * z);
  }
  Vector magnitude(float m) const {
    return normalized() * m;
  }
  Vector normalized() const {
    return Vector(*this) / magnitude();
  }
  void print() const {
    printf("Vector<x: %f, y: %f, z: %f>\n", x, y, z);
  }
};

class Normal {
public:
  float x, y, z;
  Normal() : x(0), y(0), z(0) { }
  Normal(float x, float y, float z) : x(x), y(y), z(z) {
    normalize();
  }
  Normal(const Vector& v) : x(v.x), y(v.y), z(v.z) {
    normalize();
  }
  float dot(const Normal& n) const {
    return x * n.x + y * n.y + z * n.z;
  }
  Vector cross(const Normal& v) const {
    return Vector(
      y * v.z - z * v.y,
      -x * v.z + z * v.x,
      x * v.y - y * v.x);
  }
  Vector operator*(float factor) const {
    return Vector(factor * x, factor * y, factor * z);
  }
  void print() const {
    printf("Normal<x: %f, y: %f, z: %f>\n", x, y, z);
  }
private:
  void normalize() {
    float mag = sqrt(x * x + y * y + z * z);
    if(mag < FLT_MIN) {
      x = 0;
      y = 0;
      z = 0;
    } else {
      x /= mag;
      y /= mag;
      z /= mag;
    }
  }
};

class VectorNormal {
public:
  Vector vector;
  Normal normal;
  VectorNormal() { }
  VectorNormal(Vector vector, Normal normal) : vector(vector), normal(normal) { }
};

class Bone {
public:
  float length;
  Vector rotation, begin, end;
  Bone(float length) : length(length) { }
  VectorNormal project(const VectorNormal& geo) {
    float angle = rotation.magnitude();
    Normal axis(rotation);
    Vector rotated = geo.normal * cos(angle) +
      axis.cross(geo.normal) * sin(angle) +
      axis * ((1 - cos(angle)) * axis.dot(geo.normal));
    begin = geo.vector;
    end = begin + rotated * length;
    return VectorNormal(end, Normal(rotated));
  }
  void draw() const {
    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
    glVertex3f(begin.x, begin.y, begin.z);
    glVertex3f(end.x, end.y, end.z);
    glEnd();
  }
};

class Skeleton {
public:
  vector<Bone> bones;
  VectorNormal base;
  Skeleton() {
    base = VectorNormal(Vector(0, 0, 0), Normal(0, 1, 0));
  }
  void reach(const Vector& target) {
    int iterations = 0;
    Vector toEnd, toTarget, end = project(), lastEnd;
    float angle;
    do {
      lastEnd = end;
      for(vector<Bone>::reverse_iterator it = bones.rbegin(); it != bones.rend(); ++it) {
        /*
          Move end effector closest to goal by adjusting the rotation of the
          current bone.
            - Find vector from current joint to end effector.
            - Find vector from current joint to target.
            - Calculate angle between those two vectors.
            - Add that rotation to the current rotation.
        */
        toEnd = end - it->begin;
        toTarget = target - it->begin;
        angle = acos(toEnd.dot(toTarget) /
          (toEnd.magnitude() * toTarget.magnitude()));
        it->rotation = it->rotation + toEnd.cross(toTarget).magnitude(angle);
        end = project();
      }
    } while(++iterations < 100 &&
      target.distance(end) > 0.0001 &&
      lastEnd.distance(end) > 0.0001);
  }
  Vector project() {
    VectorNormal point = base;
    for(vector<Bone>::iterator it = bones.begin(); it != bones.end(); ++it) {
      point = it->project(point);
    }
    return point.vector;
  }
  void draw() const {
    for(vector<const Bone>::iterator it = bones.begin(); it != bones.end(); ++it) {
      it->draw();
    }
  }
};

class Sphere {
public:
  float radius;
  Vector position;
  Sphere(float x, float y, float z, float r) : radius(r) {
    position = Vector(x, y, z);
  }
  void draw() const {
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
      positionX = 0, positionZ = -15;
Skeleton skeleton;
Sphere sphere(0, 0, 0, 0.1);

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
  sphere.draw();
  skeleton.reach(sphere.position);
  skeleton.draw();
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
