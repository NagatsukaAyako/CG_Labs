#include "stdafx.h"
#include <math.h>
#include "glut.h"

float round_value(float v)
{
	return floor(v + 0.5);
}

void CircleDDA(int xc, int yc, int r)
{
	int val = 1, n = 0;
	float sig, x, y;
	while (val<r)
	{
		val = val * 2;
		n++;
	}
	sig = pow(2, -n);
	x = 0;
	y = r;
	while (x <= y)
	{
		glBegin(GL_POINTS);
		glVertex2f(x + xc, y + yc);
		glVertex2f(-x + xc, y + yc);
		glVertex2f(-x + xc, -y + yc);
		glVertex2f(x + xc, -y + yc);
		glVertex2f(y + xc, x + yc);
		glVertex2f(-y + xc, x + yc);
		glVertex2f(-y + xc, -x + yc);
		glVertex2f(y + xc, -x + yc);
		glEnd();
		x = x + sig * y;
		y = y - sig * x;
	}
}
void LineDDA(int X1, int Y1, int X2, int Y2)
{
	double dx = (X2 - X1);
	double dy = (Y2 - Y1);
	double steps;
	float xInc, yInc, x = X1, y = Y1;
	/* Find out whether to increment x or y */
	steps = (fabs(dx)>fabs(dy)) ? (fabs(dx)) : (fabs(dy));
	xInc = dx / (float)steps;
	yInc = dy / (float)steps;

	
	glBegin(GL_POINTS);
	glVertex2d(x, y);
	int k;
	/* For every step, find an intermediate vertex */
	for (k = 0; k<steps; k++)
	{
		x += xInc;
		y += yInc;
		/* printf("%0.6lf %0.6lf\n",floor(x), floor(y)); */
		glVertex2d(round_value(x), round_value(y));
	}
	glEnd();
	
}
void DrawScheme() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	LineDDA(0, 200, 400, 200);
	LineDDA(200, 0, 200, 400);
	LineDDA(200, 400, 400, 200);
	LineDDA(400, 200, 200, 0);
	CircleDDA(200, 200, 140);
	glFlush();
}
void Init()
{
	glClearColor(1.0, 1.0, 1.0, 0);
	glColor3f(0.0, 0.0, 0.0);
	gluOrtho2D(0, 640, 0, 480);
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(640, 480);
	glutCreateWindow("DDA_Line");
	Init();
	glutDisplayFunc(DrawScheme);
	glutMainLoop();
}