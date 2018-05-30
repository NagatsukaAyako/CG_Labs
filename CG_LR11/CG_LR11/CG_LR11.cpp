#include "stdafx.h"
#include <windows.h>
//	Заголовочный файл для библиотеки инструментария OpenGL - glut
#include "glut.h"
#include <stdio.h> 
#include <malloc.h> 

//	Глобальные статические переменные - хранят текущий размер экрана:
//	ширина w и длина h
static int w = 0, h = 0;

static float rtrX = 0.0f;
static float rtrY = 0.0f;
static float rtrZ = 0.0f;
#define GL_BGR 0x80E0


GLuint  textura_id;
int sample = 1;

int angle = 0; // угол вращения


struct textura_struct
{
	int W;
	int H;
	unsigned char *Image;
}get_textura;

int LoadTexture(char *FileName)
{
	FILE *F;
	/* Открываем файл */
	if ((F = fopen(FileName, "rb")) == NULL)
		return 0;
	/*Перемещаемся в bmp-файле на нужную позицию, и считываем ширину и длинну */
	fseek(F, 18, SEEK_SET);
	fread(&(get_textura.W), 2, 1, F);
	fseek(F, 2, SEEK_CUR);
	fread(&(get_textura.H), 2, 1, F);

	printf("%d x %d\n", get_textura.W, get_textura.H);

	/* Выделяем память под изображение. Если память не выделилась, закрываем файл и выходим с ошибкой */
	if ((get_textura.Image = (unsigned char *)malloc(sizeof(unsigned char)* 3 * get_textura.W * get_textura.H)) == NULL)
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

//	Функция вызываемая при вхождении в главный цикл приложения
void Init(void) {
	glShadeModel(GL_SMOOTH);            // Разрешить плавное цветовое сглаживание
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);          // Очистка экрана в черный цвет
	glClearDepth(1.0f);              // Разрешить очистку буфера глубины
	glEnable(GL_DEPTH_TEST);            // Разрешить тест глубины
	glDepthFunc(GL_LEQUAL);            // Тип теста глубины
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);      // Улучшение в вычислении перспективы



	/*в строке ниже, мы зададим значение белого фонового света половиной интенсивности (0.5f).
	Поскольку все числа - 0.5f, мы получим свет средней яркости между черным (выключен свет) и белым (полная яркость).
	Смешанные в равных значениях красный, синий и зеленый дадут оттенки от черного (0.0f) до белого (1.0f). Без фонового света пятна, где нет диффузного света, будут очень темными.*/
	GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f }; // Значения фонового света

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);    // Установка Фонового Света
	/*Затем мы задаем интенсивность диффузного света, который источник света номер один будет давать.
	Мы задали интенсивность диффузного света в LightDiffuse. Значения, которые мы поместили в этот массив, будут использованы (белый свет полной интенсивности).*/
	GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Значения диффузного света ( НОВОЕ )

	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);    // Установка Диффузного Света
	GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f };     // Позиция света 
	/*Теперь мы задаем позицию источника света. Мы поместили позицию в LightPosition.
	Значения, которые мы поместили в этот массив, будут использованы (справо в центре передней грани, 0.0f по x, 0.0f по y, и 2 единицы вперед к наблюдателю {выходит за экран} по оси z).*/
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);   // Позиция света
	/*Наконец, мы разрешаем источник света номер один. Мы не разрешили GL_LIGHTING, поэтому Вы еще не увидите никакого освещения.
	Свет установлен, и позиционирован, и даже разрешен, но пока мы не разрешили GL_LIGHTING, освещение не будет работать.*/

	glEnable(GL_LIGHT1); // Разрешение источника света номер один
	glEnable(GL_LIGHTING); // включаем освещение
}	//	void Init(void)


void DrawGLScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Очистка экрана и буфера глубины
	glLoadIdentity();            
	gluLookAt(0,-30,-40, 0,0,0, 1,0,0);// Сброс просмотра
	glTranslatef(0.0f, 0.0f, -6.0f);                 // Сдвиг влево и вглубь экрана

	glRotatef(rtrY, 0.0f, 1.0f, 0.0f);                 // Вращение пирамиды по оси Y
	glRotatef(rtrX, 1.0f, 0.0f, 0.0f);				    //Вращение по оси X
	glRotatef(rtrZ, 0.0f, 0.0f, 1.0f);				//Вращение по оси Z
	
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
	//	Меняем местами задний и передний буферы
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
	glutPostRedisplay();

}	//	void Reshape(int width, int height)

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '1':
		rtrY += 0.5f;             // Увеличим переменную вращения для треугольника 
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
	glutInitWindowSize(600, 600);
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
	if (LoadTexture((char *)"Tulips.bmp") != 1){ printf("Не удалось загрузить изображение\n"); }
	//	Вызовем функцию Init() перед тем как входить в главный цикл
	Init();
	//	Войти в главный цикл приложения
	glutMainLoop();

	//	Возвращаем значение равное нулю
	return 0;
}	//	int main(int argc, char *argv[])
