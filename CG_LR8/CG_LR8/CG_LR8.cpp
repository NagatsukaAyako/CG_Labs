#include "stdafx.h"
#include "glut.h"
//	Подключить заголовочный файл для работы с Windows - требуется для
//	заголовочных файлов OpenGL
//#include <windows.h>
//	Заголовочный файл для библиотеки инструментария OpenGL - glut

//	Глобальные статические переменные - хранят текущий размер экрана:
//	ширина w и длина h
static int w = 0, h = 0;
static float trnX = 0.0f;
static float trnY = 0.0f;
static float trnZ = 0.0f;
static float rtrX = 0.0f;
static float rtrY = 0.0f;
static float rtrZ = 0.0f;
static float sclX = 1.0f;
static float sclY = 1.0f;
static float sclZ = 1.0f;

//	Функция вызываемая при вхождении в главный цикл приложения
void Init(void) {
	glShadeModel(GL_SMOOTH);            // Разрешить плавное цветовое сглаживание
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);          // Очистка экрана в черный цвет
	glClearDepth(1.0f);              // Разрешить очистку буфера глубины
	glEnable(GL_DEPTH_TEST);            // Разрешить тест глубины
	glDepthFunc(GL_LEQUAL);            // Тип теста глубины
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);      // Улучшение в вычислении перспективы
}	//	void Init(void)


void DrawGLScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Очистка экрана и буфера глубины
	glLoadIdentity();                               // Сброс просмотра
	glTranslatef(trnX, trnY, trnZ);                 // Сдвиг влево и вглубь экрана
	glRotatef(rtrY, 0.0f, 1.0f, 0.0f);              
	glRotatef(rtrX, 1.0f, 0.0f, 0.0f);				  
	glRotatef(rtrZ, 0.0f, 0.0f, 1.0f);
	glScalef(sclX, sclZ, sclY);

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
	glColor3f(0.0f, 1.0f, 0.0f); // Синий
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(-1.0f, 2.0f, 1.0f);
	glVertex3f(1.0f, 2.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f); // Синий
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f); // Синий
	glVertex3f(-1.0f, 2.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, 0.0f, 0.5f);
	glColor3f(0.0f, 1.0f, 0.0f); // Синий
	glVertex3f(1.0f, 0.0f, 0.5f);
	glVertex3f(0.5f, 0.0f, 1.0f);
	glVertex3f(1.0f, 2.0f, 1.0f);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 1.0f); // Синий
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.5f);
	glVertex3f(1.0f, 2.0f, 1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f); // Синий
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.5f);
	glVertex3f(-1.0f, 2.0f, 1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f); // Синий
	glVertex3f(0.5f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, 2.0f, 1.0f);
	glVertex3f(1.0f, 2.0f, 1.0f);
	glEnd();
	
	glFlush();
	glutSwapBuffers();
}

void Reshape(int width, int height) {
	//	Сохраним размеры окна в глобальных переменных
	w = width;
	h = height;
	//	Дадим знать OpenGL в какую область будет производиться отрисов-
	//	ка - в данном случае: всё окно
	glViewport(0, 0, w, h);
	//	Установим текущую матрицу - матрицу проективного преобразования
	glMatrixMode(GL_PROJECTION);
	//	Сделаем матрицу проективного преобразования единичной
	glLoadIdentity();
	//	Применим матрицу перспективного преобразования исходя из задан-
	//	ного угла обзора, отношения ширины к высоте боковых и врехних/
	//	нижних отсекающих плоскостей и расстояния ближней и дальней от-
	//	секающих плоскостей
	gluPerspective(70.0f, w / h, 0.1f, 100);
	//	Установим текущей - матрицу видового преобразования, чтобы далее
	//	В программе мы могли работать только с ней
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
	default:
		break;
	}
}
//	Основная точка входа в приложение - главная функция main
int main(int argc, char *argv[]) {
	//	Инициализировать сам glut
	glutInit(&argc, argv);
	//	Установить начальные размеры окна
	glutInitWindowSize(800, 600);
	//	Установить параметры окна - двойная буфферизация и поддержка
	//	цвета RGBA
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	//	Создать окно с заголовком OpenGL
	glutCreateWindow("OpenGL");

	//	Укажем glut функцию, которая будет рисовать каждый кадр
	glutDisplayFunc(DrawGLScene);
	//	Укажем glut функцию, которая будет вызываться при изменении
	//	размера окна приложения
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyboard);

	//	Вызовем функцию Init() перед тем как входить в главный цикл
	Init();
	//	Войти в главный цикл приложения
	glutMainLoop();

	//	Возвращаем значение равное нулю
	return 0;
}	//	int main(int argc, char *argv[])
