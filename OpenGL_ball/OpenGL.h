#if !defined	_OpenGL_Hans_
#define _OpenGL_Hans_

#include "gl/glut.h"
#include <math.h>
#include <stdio.h>

#define GL_PI 3.1415f

#define SIZE 100.0f


typedef struct EyePoint {
	GLfloat x;
	GLfloat y;
	GLfloat z;
} EYEPOINT;

typedef struct Point {
	float x;
	float y;
	float z;
} Point;


EYEPOINT Eye;
GLint WinWidth=600;
GLint WinHeight=600;


void OnDisplay(void);
void OnReshape(int,int);
void OnKeyboard(int,int,int);
void SetupLights();
void Level(Point,Point,Point,float);
Point distance(Point,Point,float);

#endif