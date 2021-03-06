#include "stdafx.h"


static int w = 0, h = 0;
static float sclX = 1.0f;
static float sclY = 1.0f;
static float sclZ = 1.0f;
static float trX = 0.0f;
static float trY = 0.0f;
static float rtrX = 0.0f;
static float rtrY = 0.0f;
static float rtrZ = 0.0f;
static float rtrX2 = 0.0f;
static bool isReflected = false;
static bool isReflectedXY = false;

void Init(void) {
	glShadeModel(GL_SMOOTH);            // Разрешить плавное цветовое сглаживание
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);          // Очистка экрана в черный цвет
	glClearDepth(1.0f);              // Разрешить очистку буфера глубины
	glEnable(GL_DEPTH_TEST);            // Разрешить тест глубины
	glDepthFunc(GL_LEQUAL);            // Тип теста глубины
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);      // Улучшение в вычислении перспективы
}

void DrawGLScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity(); 
	if (isReflected)
	{
		glRotatef(180, 0.0f, 1.0f, 0.0f);
		glRotatef(180, 1.0f, 0.0f, 0.0f);
		glRotatef(180, 0.0f, 0.0f, 1.0f);
	}
	if (isReflectedXY)
	{
		glRotatef(180, 1.0f, 1.0f, 0.0f);
	}
	glRotatef(rtrY, 0.0f, 1.0f, 0.0f);
	glRotatef(rtrX, 1.0f, 0.0f, 0.0f);
	glRotatef(rtrZ, 0.0f, 0.0f, 1.0f);
	glTranslatef(trX, trY, -7.0f);
	glRotatef(rtrX2, 0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.5f);
	glVertex3f(0.5f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, 0.0f, 0.5f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(-1.0f, 2.0f, 1.0f);
	glVertex3f(1.0f, 2.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 2.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, 0.0f, 0.5f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.5f);
	glVertex3f(0.5f, 0.0f, 1.0f);
	glVertex3f(1.0f, 2.0f, 1.0f);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.5f);
	glVertex3f(1.0f, 2.0f, 1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.5f);
	glVertex3f(-1.0f, 2.0f, 1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f); 
	glVertex3f(0.5f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, 2.0f, 1.0f);
	glVertex3f(1.0f, 2.0f, 1.0f);
	glEnd();
	glFlush();
	glutSwapBuffers();
}

void Reshape(int width, int height) {
	w = width;
	h = height;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0f, w / h, 0.1f, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '1':
		rtrY += 0.5f;
		glutPostRedisplay();
		break;
	case '2':
		rtrX += 0.5f;
		glutPostRedisplay();
		break;
	case '3':
		rtrZ += 0.5f;
		glutPostRedisplay();
		break;
	case 'a':
		trX -= 0.5f;
		glutPostRedisplay();
		break;
	case 'd':
		trX += 0.5f;
		glutPostRedisplay();
		break;
	case 'w':
		trY -= 0.5f;
		glutPostRedisplay();
		break;
	case 's':
		trY += 0.5f;
		glutPostRedisplay();
		break;
	case 'l':
		rtrX2 += 0.5f;
		glutPostRedisplay();
		break;
	case 'k':
		sclX = sclY = sclZ = 1.5f * sclZ; 
		glutPostRedisplay();
		break;
	case 'n':
		isReflected = !isReflected;
		glutPostRedisplay();
		break;
	case 'm':
		isReflectedXY = !isReflectedXY;
		glutPostRedisplay();
		break;
	case 'z':
		trX = 0;
		trY = 0;
		rtrX = 0;
		rtrY = 0;
		rtrZ = 0;
		sclX = 1;
		sclY = 1;
		sclZ = 1;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("OpenGL");
	glutDisplayFunc(DrawGLScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyboard);
	Init();
	glutMainLoop();
	return 0;
}
