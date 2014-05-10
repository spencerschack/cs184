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

void drawSphere(float x, float y, float z, float d, float r, float g, float b) {
  glPushMatrix();
  glColor3f(r, g, b);
  glTranslatef(x, y, z);
  glutSolidSphere(d, 8, 8);
  glPopMatrix();
}

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
    return Vector(x * factor, y * factor, z * factor);
  }
  Vector operator/(float divisor) {
    return Vector(x / divisor, y / divisor, z / divisor);
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
    drawSphere(end.x, end.y, end.z, 0.1, 1, 0, 0);
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
        // Here's the problem, I don't think you can simply add these.
        it->rotation = it->rotation + toEnd.cross(toTarget).magnitude(angle);
        end = project();
      }
    } while(++iterations < 100 &&
      target.distance(end) > 0.01 &&
      lastEnd.distance(end) > 0.0001);
    // TODO: tune these heuristics.
  }
  Vector project() {
    VectorNormal point = base;
    for(vector<Bone>::iterator it = bones.begin(); it != bones.end(); ++it) {
      point = it->project(point);
    }
    return point.vector;
  }
  void draw() const {
    drawSphere(base.vector.x, base.vector.y, base.vector.z, 0.1, 0, 1, 0);
    for(vector<const Bone>::iterator it = bones.begin(); it != bones.end(); ++it) {
      it->draw();
    }
  }
};

float rotationX = 0, rotationY = 0,
      positionX = 0, positionZ = -25;
Skeleton skeleton;
Vector target(1, 1, 1);

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
  glRotatef(rotationY, 0, 0, 1);
  drawSphere(target.x, target.y, target.z, 0.1, 1.0, 0.5, 0);
  skeleton.reach(target);
  skeleton.draw();
  glFlush();
  glutSwapBuffers();
}

void keyPress(unsigned char key, int x, int y) {
  if(glutGetModifiers() & GLUT_ACTIVE_SHIFT) {
    switch(key) {
      case 'w': target.z += 0.1; break;
      case 's': target.z -= 0.1; break;
    }
  } else {
    switch(key) {
      case 'w': positionZ += 0.05; break;
      case 'd': positionX += 0.05; break;
      case 's': positionZ -= 0.05; break;
      case 'a': positionX -= 0.05; break;
    }
  }
}

void specialPress(int key, int x, int y) {
  if(glutGetModifiers() & GLUT_ACTIVE_SHIFT) {
    switch(key) {
      case GLUT_KEY_UP:    target.y += 0.1; break;
      case GLUT_KEY_RIGHT: target.x += 0.1; break;
      case GLUT_KEY_DOWN:  target.y -= 0.1; break;
      case GLUT_KEY_LEFT:  target.x -= 0.1; break;
    }
  } else {
    switch(key) {
      case GLUT_KEY_UP:    rotationX -= 0.5; break;
      case GLUT_KEY_RIGHT: rotationY -= 0.5; break;
      case GLUT_KEY_DOWN:  rotationX += 0.5; break;
      case GLUT_KEY_LEFT:  rotationY += 0.5; break;
    }
  }
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(400, 400);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Inverse Kinematics");
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
