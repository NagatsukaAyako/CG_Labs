#include "stdafx.h"
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "glut.h"
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")

int angle = 0;
bool flag = false;
float mat3_dif[] = { 0.9f,0.2f,0.0f };

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH); // режим закрашивания: интерполируемые значения 
	GLfloat light1_diffuse[] = { 0.4, 0.7, 0.2 };
	GLfloat light1_position[] = { 0.0, 0.0, 1.0, 1.0 };
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

void display() {
	flag = true;
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(angle, 1, 1, 0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat3_dif);
	glutSolidSphere(1.0f, 20, 20);
	glPopMatrix();
	glutSwapBuffers();
	flag = false;
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, GLfloat(1.33), 1, 20);
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
}

void key(unsigned char key, int  x, int y) {
	if (key == 27 || key == 'q' || key == 'Q') {
		exit(0);
	}
}

void mytime(int value) // таймер
{
	angle = (angle>358) ? 0 : angle + 2;
	if (!flag) {
		glutPostRedisplay();
	}
	glutTimerFunc(40, mytime, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	int glWin = glutCreateWindow("My program");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutTimerFunc(40, mytime, 0);
	glutMainLoop();
	return 0;
}