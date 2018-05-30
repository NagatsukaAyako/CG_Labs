#include "stdafx.h"
#include "glut.h"
#include "math.h"

double x, y;
int Color[3] = { 255, 0, 0 };
int BolderColor[3] = { 255, 0, 255 };

bool compaireColors(int mas1[], int mas2[])
{
	for (int i = 0; i < 3; i++)
	if (mas1[i] != mas2[i]) { return false; }

	return true;
}

void getpixel(int x, int y, int* colors)
{
	unsigned char pixel[4];
	glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

	colors[0] = pixel[0];
	colors[1] = pixel[1];
	colors[2] = pixel[2];
}

int LineFill(int x, int y, int dir, int PrevXl, int PrevXr)
{
	int xl = x;
	int xr = x;
	int c[3];

	do getpixel(--xl, y, c); 
		while ((!compaireColors(c, BolderColor)) && (!compaireColors(c, Color)));

	do getpixel(++xr, y, c); while ((!compaireColors(c, BolderColor)) && (!compaireColors(c, Color)));
	xl++; xr--;

	glBegin(GL_LINES);
	glColor3d(255, 0, 0);
	glVertex2d(xl, y);
	glVertex2d(xr, y);
	glEnd();

	for (x = xl; x <= xr; x++)
	{
		getpixel(x, y + dir, c);
		if ((!compaireColors(c, BolderColor)) && (!compaireColors(c, Color)))   x = LineFill(x, y + dir, dir, xl, xr);
	}

	for (x = xl; x<PrevXl; x++)
	{
		getpixel(x, y - dir, c);
		if ((!compaireColors(c, BolderColor)) && (!compaireColors(c, Color)))   x = LineFill(x, y - dir, -dir, xl, xr);
	}

	for (x = PrevXr; x<xr; x++)
	{
		getpixel(x, y - dir, c);
		if ((!compaireColors(c, BolderColor)) && (!compaireColors(c, Color)))  x = LineFill(x, y - dir, -dir, xl, xr);
	}

	return xr;
}


void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINE_LOOP);
	
	glColor3d(255, 0, 255);
	int i, N = 5;
	float X = 200, Y = 200, R = 50;
	float angle;
	float x, y;
	for (i = 0; i < N; i++)
	{
		angle = 2 * 3.1415f * i / N;
		x = R*cos(angle) + X;
		y = R*sin(angle) + Y;
		glVertex2d(R*cos(angle) + X, R*sin(angle) + Y);
	}
	glEnd();
	LineFill(200, 200, 1, 200 , 200);
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("LR13");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}