#include "stdafx.h"
#include <windows.h>
//	������������ ���� ��� ���������� �������������� OpenGL - glut
#include "glut.h"
#include <stdio.h> 
#include <malloc.h> 

//	���������� ����������� ���������� - ������ ������� ������ ������:
//	������ w � ����� h
static int w = 0, h = 0;

static float rtrX = 0.0f;
static float rtrY = 0.0f;
static float rtrZ = 0.0f;
#define GL_BGR 0x80E0


GLuint  textura_id;
int sample = 1;

int angle = 0; // ���� ��������


struct textura_struct
{
	int W;
	int H;
	unsigned char *Image;
}get_textura;

int LoadTexture(char *FileName)
{
	FILE *F;
	/* ��������� ���� */
	if ((F = fopen(FileName, "rb")) == NULL)
		return 0;
	/*������������ � bmp-����� �� ������ �������, � ��������� ������ � ������ */
	fseek(F, 18, SEEK_SET);
	fread(&(get_textura.W), 2, 1, F);
	fseek(F, 2, SEEK_CUR);
	fread(&(get_textura.H), 2, 1, F);

	printf("%d x %d\n", get_textura.W, get_textura.H);

	/* �������� ������ ��� �����������. ���� ������ �� ����������, ��������� ���� � ������� � ������� */
	if ((get_textura.Image = (unsigned char *)malloc(sizeof(unsigned char)* 3 * get_textura.W * get_textura.H)) == NULL)
	{
		fclose(F);
		return 0;
	}
	/* ��������� ����������� � ������ �� 3 ����, �� ���� RGB ��� ������� ������� */
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

//	������� ���������� ��� ��������� � ������� ���� ����������
void Init(void) {
	glShadeModel(GL_SMOOTH);            // ��������� ������� �������� �����������
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);          // ������� ������ � ������ ����
	glClearDepth(1.0f);              // ��������� ������� ������ �������
	glEnable(GL_DEPTH_TEST);            // ��������� ���� �������
	glDepthFunc(GL_LEQUAL);            // ��� ����� �������
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);      // ��������� � ���������� �����������



	/*� ������ ����, �� ������� �������� ������ �������� ����� ��������� ������������� (0.5f).
	��������� ��� ����� - 0.5f, �� ������� ���� ������� ������� ����� ������ (�������� ����) � ����� (������ �������).
	��������� � ������ ��������� �������, ����� � ������� ����� ������� �� ������� (0.0f) �� ������ (1.0f). ��� �������� ����� �����, ��� ��� ���������� �����, ����� ����� �������.*/
	GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f }; // �������� �������� �����

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);    // ��������� �������� �����
	/*����� �� ������ ������������� ���������� �����, ������� �������� ����� ����� ���� ����� ������.
	�� ������ ������������� ���������� ����� � LightDiffuse. ��������, ������� �� ��������� � ���� ������, ����� ������������ (����� ���� ������ �������������).*/
	GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // �������� ���������� ����� ( ����� )

	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);    // ��������� ���������� �����
	GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f };     // ������� ����� 
	/*������ �� ������ ������� ��������� �����. �� ��������� ������� � LightPosition.
	��������, ������� �� ��������� � ���� ������, ����� ������������ (������ � ������ �������� �����, 0.0f �� x, 0.0f �� y, � 2 ������� ������ � ����������� {������� �� �����} �� ��� z).*/
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);   // ������� �����
	/*�������, �� ��������� �������� ����� ����� ����. �� �� ��������� GL_LIGHTING, ������� �� ��� �� ������� �������� ���������.
	���� ����������, � ��������������, � ���� ��������, �� ���� �� �� ��������� GL_LIGHTING, ��������� �� ����� ��������.*/

	glEnable(GL_LIGHT1); // ���������� ��������� ����� ����� ����
	glEnable(GL_LIGHTING); // �������� ���������
}	//	void Init(void)


void DrawGLScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// ������� ������ � ������ �������
	glLoadIdentity();            
	gluLookAt(0,-30,-40, 0,0,0, 1,0,0);// ����� ���������
	glTranslatef(0.0f, 0.0f, -6.0f);                 // ����� ����� � ������ ������

	glRotatef(rtrY, 0.0f, 1.0f, 0.0f);                 // �������� �������� �� ��� Y
	glRotatef(rtrX, 1.0f, 0.0f, 0.0f);				    //�������� �� ��� X
	glRotatef(rtrZ, 0.0f, 0.0f, 1.0f);				//�������� �� ��� Z
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura_id);

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.3f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.7f); glVertex3f(5.0f, 0.0f, 0.0f);
	glTexCoord2f(0.5f, 1.0f); glVertex3f(10.0f, 0.0f, 5.0f);
	glTexCoord2f(0.0f, 0.7f); glVertex3f(5.0f, 0.0f, 10.0f);
	glTexCoord2f(0.0f, 0.3f); glVertex3f(0.0f, 0.0f, 10.0f);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(-5.0f, 0.0f, 5.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0.0f, 20.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f, 20.0f, 10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f, 20.0f, 10.0f);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 20.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(5.0f, 0.0f, 0.0f);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, 20.0f, 10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0f, 0.0f, 5.0f);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, 0.0f, 5.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(5.0f, 0.0f, 10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f, 20.0f, 10.0f);
	glEnd();
	glBegin(GL_QUADS);
	
	glTexCoord2f(0.0f, 0.0f); glVertex3f(5.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, 0.0f, 5.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f, 20.0f, 10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 20.0f, 0.0f);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-5.0f, 0.0f, 5.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 20.0f, 10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 20.0f, 0.0f);

	glTexCoord2f(0.0f, 0.8f); glVertex3f(5.0f, 0.0f, 10.0f);
	glTexCoord2f(0.0f, 0.3f); glVertex3f(0.0f, 0.0f, 10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, 20.0f, 10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 20.0f, 10.0f);
	glEnd();
	
	glFlush();
	//	������ ������� ������ � �������� ������
	glutSwapBuffers();
}


void Reshape(int width, int height) {
	//	�������� ������� ���� � ���������� ����������
	w = width;
	h = height;
	//	����� ����� OpenGL � ����� ������� ����� ������������� �������-
	//	�� - � ������ ������: �� ����
	glViewport(0, 0, w, h);
	//	��������� ������� ������� - ������� ������������ ��������������
	glMatrixMode(GL_PROJECTION);
	//	������� ������� ������������ �������������� ���������
	glLoadIdentity();
	//	�������� ������� �������������� �������������� ������ �� �����-
	//	���� ���� ������, ��������� ������ � ������ ������� � �������/
	//	������ ���������� ���������� � ���������� ������� � ������� ��-
	//	�������� ����������
	gluPerspective(70.0f, w / h, 0.1f, 100);
	//	��������� ������� - ������� �������� ��������������, ����� �����
	//	� ��������� �� ����� �������� ������ � ���
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();

}	//	void Reshape(int width, int height)

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '1':
		rtrY += 0.5f;             // �������� ���������� �������� ��� ������������ 
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
	default:
		break;
	}
}
//	�������� ����� ����� � ���������� - ������� ������� main
int main(int argc, char *argv[]) {
	//	���������������� ��� glut
	glutInit(&argc, argv);
	//	���������� ��������� ������� ����
	glutInitWindowSize(600, 600);
	//	���������� ��������� ���� - ������� ������������ � ���������
	//	����� RGBA
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	//	������� ���� � ���������� OpenGL
	glutCreateWindow("OpenGL");

	//	������ glut �������, ������� ����� �������� ������ ����
	glutDisplayFunc(DrawGLScene);
	//	������ glut �������, ������� ����� ���������� ��� ���������
	//	������� ���� ����������
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyboard);
	if (LoadTexture((char *)"Tulips.bmp") != 1){ printf("�� ������� ��������� �����������\n"); }
	//	������� ������� Init() ����� ��� ��� ������� � ������� ����
	Init();
	//	����� � ������� ���� ����������
	glutMainLoop();

	//	���������� �������� ������ ����
	return 0;
}	//	int main(int argc, char *argv[])
