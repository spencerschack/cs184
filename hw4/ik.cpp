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
class Quaternion;
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

class Quaternion {
public:
  float s;
  Vector v;
  Quaternion() : s(1) { }
  Quaternion(float s, float x, float y, float z) : s(s) {
    v = Vector(x, y, z);
  }
  Quaternion(Normal axis, float angle) {
    angle *= 0.5f;
    s = cos(angle);
    v = axis * sin(angle);
  }
  Quaternion operator*(const Quaternion& q) const {
    return Quaternion(
      s * q.s   - v.x * q.v.x - v.y * q.v.y - v.z * q.v.z,
      s * q.v.x + v.x * q.s   + v.y * q.v.z - v.z * q.v.y,
      s * q.v.y - v.x * q.v.z + v.y * q.s   + v.z * q.v.x,
      s * q.v.z + v.x * q.v.y - v.y * q.v.x + v.z * q.s
    );
  }
  Quaternion conjugate() const {
    return Quaternion(s, -v.x, -v.y, -v.z);
  }
  Normal rotate(const Normal& n) const {
    Quaternion res = *this * (Quaternion(0, n.x, n.y, n.z) * conjugate());
    return Normal(res.v.x, res.v.y, res.v.z);
  }
  void print() const {
    printf("Quaternion<s: %f, x: %f, y: %f, z: %f>\n", s, v.x, v.y, v.z);
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
  Vector begin, end;
  Quaternion rotation;
  Bone(float length) : length(length) { }
  VectorNormal project(const VectorNormal& geo) {
    Normal rotated = rotation.rotate(geo.normal);
    begin = geo.vector;
    end = begin + rotated * length;
    return VectorNormal(end, rotated);
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
    Normal axis;
    float angle;
    do {
      lastEnd = end;
      for(vector<Bone>::reverse_iterator it = bones.rbegin(); it != bones.rend(); ++it) {
        toEnd = end - it->begin;
        toTarget = target - it->begin;
        axis = Normal(toEnd.cross(toTarget));
        angle = min(acos(min(toEnd.dot(toTarget) /
          (toEnd.magnitude() * toTarget.magnitude()), 1.0f)), 0.5f);
        if(angle > 0.01) {
          it->rotation = it->rotation * Quaternion(axis, angle);
          end = project();
        }
      }
    } while(++iterations < 500 &&
      target.distance(end) > 0.001 &&
      lastEnd.distance(end) > 0.001);
    // TODO: tune these heuristics.
  }
  Vector project() {
    VectorNormal point = base;
    for(vector<Bone>::iterator it = bones.begin(); it != bones.end(); ++it) {
      point = it->project(point);
    }
    return point.vector;
  }
  void draw() {
    drawSphere(base.vector.x, base.vector.y, base.vector.z, 0.1, 0, 1, 0);
    for(vector<Bone>::iterator it = bones.begin(); it != bones.end(); ++it) {
      it->draw();
    }
  }
};

class Circle {
public:
  float x, y, z, r;
  Circle(float x, float y, float z, float r) : x(x), y(y), z(z), r(r) { }
  void move(Vector& v) const {
    Vector p = interpolate();
    v.x = p.x;
    v.y = p.y;
    v.z = p.z;
  }
  Vector interpolate() const {
    float t = ((float) (clock() % (CLOCKS_PER_SEC / 8))) / ((float) (CLOCKS_PER_SEC / 8)) * 2.0f * M_PI;
    return interpolate(t);
  }
  Vector interpolate(float t) const {
    return Vector(cos(t) * r + x, sin(t) * r + y, z);
  }
  void draw() const {
    Vector v;
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 32; i++) {
      v = interpolate((float) i / 32.0f * 2 * M_PI);
      glVertex3f(v.x, v.y, v.z);
    }
    glEnd();
  }
};

float rotationX = 0, rotationY = 0,
      positionX = 0, positionZ = -25;
Skeleton skeleton;
Circle circle(0, 7, 0, 7);
Vector target(0, 10, 0);
bool moved = true, interactive = true;

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
  if(!interactive) {
    circle.move(target);
    circle.draw();
  }
  if(!interactive || moved) {
    moved = false;
    skeleton.reach(target);
  }
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
    case 'W': if(interactive) { target.z += 0.1; moved = true; } break;
    case 'S': if(interactive) { target.z -= 0.1; moved = true; } break;
    case 'i': interactive = !interactive;
  }
}

void specialPress(int key, int x, int y) {
  if(glutGetModifiers() & GLUT_ACTIVE_SHIFT && interactive) {
    moved = true;
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
