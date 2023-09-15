#include <Windows.h> 
#include <GL/glut.h>
#include<gl/GL.h>
#include<math.h>

// func decleration......
void init();
void display();
void timer(int);
void reshape(int, int);
void draw_sun(float cx, float cy, float r, int noop, GLenum mode);
void Draw_road(GLint minX, GLint maxX, GLint step, GLenum GL_TYPE, float PointSize);

// constant decleration

const double pi = 3.14159265;
float x_trans = 0;
bool x_trans_flag = true;

//main function
int main(int argc, char** argv)  //parameters through which the Script is passed to another function
{
	glutInit(&argc, argv);  //initialization of the GLU Library

	glutInitDisplayMode(GLUT_RGB); //choose from diffrent modes that will be displayed in the screen like negative, RGB and gray scale mode

	glutInitWindowPosition(150, 150);    //set the x and y points at which the console screen will open on the window         
	
	glutInitWindowSize(1000, 500);   //set window size of the console screen	
	
	glutCreateWindow("sunrise");   //the titel of my window



	//function Calling

	glPointSize(4.0);
	init();
	timer(0);
	glutDisplayFunc(display); //does not take paramaters but takes a prepared fuction to display on screen
	glutReshapeFunc(reshape);
	glutMainLoop();   //runs the programm as long as the user has not closed it
	gluOrtho2D(-500, 500, -250, 250);

	return 0;
}

//function Implementation 

void draw_sun(float cx, float cy, float r, int noop, GLenum mode) {

	glBegin(mode);

	for (int i = 0; i < noop; i++) {
		float	ang = 2 * pi * i / noop;
		glVertex2d(cx + cos(ang - 150) * r, cy + sin(ang - 150) * r);
	}
	glEnd();
}

void Draw_road(GLint minX, GLint maxX, GLint step, GLenum GL_TYPE, float PointSize) {
	glBegin(GL_TYPE);


	for (GLint i = minX; i <= maxX; i += step) {
		glPointSize(PointSize);
		glVertex2f(i, -150);
	}
	glEnd();
}

// display function
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);  // evacuating the color buufer fist which exists in the GPU in order to clear the screen


	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(900, 0); // drawing in 2 dimentions x and y
	glVertex2f(900, -150);
	glVertex2f(500, -150);
	glVertex2f(500, 0);
	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(670, -90);
	glVertex2f(670, -140);
	glVertex2f(730, -140);
	glVertex2f(730, -90);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(550, -30);
	glVertex2f(550, -60);
	glVertex2f(650, -60);
	glVertex2f(650, -30);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(850, -30);
	glVertex2f(850, -60);
	glVertex2f(750, -60);
	glVertex2f(750, -30);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	Draw_road(-1000, 1000, 10, GL_POINTS, 1);

    // die farbe der sonne
	glColor3f(7.0, 0.0, 3.0);
	draw_sun(x_trans - 900, 200, 80, 600, GL_POLYGON);

	if (x_trans_flag) {
		x_trans = x_trans + 10;
	}
	else
	{
		x_trans = x_trans - 10;
	}
	if (x_trans > 2000)
	{
		x_trans_flag = false;
	}
	else if (x_trans < -400)
	{
		x_trans_flag = true;
	}
	glFlush();
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-500, 500, -250, 250);

}

void timer(int value)
{
	glutTimerFunc(33, timer, 0);
	glutPostRedisplay();
}


// reshape function

void  reshape(int w, int h) // it is a Fuction only organized to preserve the state of the drawn shape, so that it can not be suddelny wider or longer
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	GLfloat a = (GLfloat)w / (GLfloat)h;
	glLoadIdentity();  //stops the fuction of projection Matrix. 
	if (w >= h)  // if width is larger than height, multiply the width by an aspect ratio to return it back to its original state
	{
		gluOrtho2D(-(500) * a, (500) * a, -(250), 250); 
	}
	else
	{
		gluOrtho2D(-(-500), 500, -(250) / a, (250) / a);   //the origin Point , where (-x,+x,-y,+y)
	}
}
