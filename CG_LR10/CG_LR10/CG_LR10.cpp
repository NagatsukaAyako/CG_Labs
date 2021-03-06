#include "stdafx.h"
#include <stdlib.h>
#include "glut.h"
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <math.h>
#include <stdio.h> 
#include <malloc.h> 

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")

static int w = 0, h = 0;
static float Angle = 0.0f, scaleX = 1, scaleY = 1, translate = 0;
static float eye1 = 0.0f, eye2 = 0.0f, eye3 = 0.0f;

#define GL_BGR 0x80E0
GLuint  textura_id;
int sample = 1;
struct textura_struct
{
	int W;
	int H;
	unsigned char *Image;
}get_textura;

void Init(void) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void Update(void) {
	Angle += 0.05f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	Загрузим единичную матрицу видового преобразования
	glLoadIdentity();
	gluLookAt(100, 100, 100, eye1, eye2, eye3, 0.0f, 1.0f, 0.0f);
	glRotatef((GLfloat)Angle, 0.0f, 1.0f, 0.0f);
	glScalef(scaleX, scaleY, 1.0);
	glTranslatef(translate, translate, 0.0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura_id);
	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1);
	glVertex3f(75.0f, 0.0f, 50.0f);
	glTexCoord2d(0, 1);
	glVertex3f(-75.0f, 0.0f, 50.0f);
	glTexCoord2d(0, 0.5);
	glVertex3f(-75.0f, 0.0f, 0.0f);
	glTexCoord2d(0.3, 0.5);
	glVertex3f(-25.0f, 0.0f, 0.0f);
	glTexCoord2d(0.3, 0);
	glVertex3f(-25.0f, 0.0f, -50.0f);
	glTexCoord2d(1, 0);
	glVertex3f(75.0f, 0.0f, -50.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 5.0, -100.0);
	glVertex3f(0, 5.0, 100.0);
	glEnd();
	glLineWidth(5);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(3, 65520);
	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(5);
	glVertex3f(100, 5.0, -100.0);
	glVertex3f(-100, 5.0, 100.0);
	glEnd();
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_LINE_STIPPLE);

	//Прорисовка осей
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, 0.0, 0.0);
	glVertex3f(0, 10.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, 0.0);
	glVertex3f(0, 0.0, 10.0);
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
	gluPerspective(65.0f, w / h, 1.0f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int LoadTexture(char *FileName)
{
	FILE *F;
	if ((F = fopen(FileName, "rb")) == NULL)
		return 0;
	/*Перемещаемся в bmp-файле на нужную позицию, и считываем ширину и длинну */
	fseek(F, 18, SEEK_SET);
	fread(&(get_textura.W), 2, 1, F);
	fseek(F, 2, SEEK_CUR);
	fread(&(get_textura.H), 2, 1, F);

	printf("%d x %d\n", get_textura.W, get_textura.H);

	/* Выделяем память под изображение. Если память не выделилась, закрываем файл и выходим с ошибкой */
	if ((get_textura.Image = (unsigned char *)malloc(sizeof(unsigned char) * 3 * get_textura.W * get_textura.H)) == NULL)
	{
		fclose(F);
		return 0;
	}
	/* Считываем изображение в память по 3 бита, то бишь RGB для каждого пикселя */
	fseek(F, 30, SEEK_CUR);
	fread(get_textura.Image, 3, get_textura.W * get_textura.H, F);

	glGenTextures(1, &textura_id);
	glBindTexture(GL_TEXTURE_2D, textura_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, get_textura.W, get_textura.H, GL_BGR, GL_UNSIGNED_BYTE, get_textura.Image);
	free(get_textura.Image);
	fclose(F);

	return 1;
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '1':
		Angle -= 45.0f;
		glutPostRedisplay();
		break;
	case '2':
		scaleX *= 2.0f;
		glutPostRedisplay();
		break;
	case '3':
		scaleY *= 2.0f;
		glutPostRedisplay();
		break;
	case '4':
		translate += 10.0f;
		glutPostRedisplay();
		break;
	case 'w':
		eye1 += 10;
		glutPostRedisplay();
		break;
	case 's':
		eye1 -= 10;
		glutPostRedisplay();
		break;
	case 'a':
		eye2 -= 10;
		glutPostRedisplay();
		break;
	case 'd':
		eye2 += 10;
		glutPostRedisplay();
		break;
	case 'q':
		eye3 -= 10;
		glutPostRedisplay();
		break;
	case 'e':
		eye3 += 10;
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
	glutDisplayFunc(Update);
	glutReshapeFunc(Reshape);
	if (LoadTexture((char *)"sky.bmp") != 1) { printf("Не удалось загрузить изображение\n"); }
	glutKeyboardFunc(keyboard);
	Init();
	glutMainLoop();
	return 0;
}
