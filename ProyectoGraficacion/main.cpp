#include "glew.h"
#include "glut.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "Vertice.h"
#include "Cara.h"
#include "Obj3D.h"
#include <math.h>
#include <stdarg.h>
void multmat(float mat[4][4], float iter, float iter2, float iter3);
#define GL_GLEXT_PROTOTYPES
using namespace std;
void display();
void update(int);
void specialKeys();
double rotate_y = 0;
double rotate_x = 0;
void Normalizar(float arr[]);
float productoPunto(float n[], float f[]);
float clamp(float punto, float upper, float lower);
float iluminacion[3] = { 2.0,3.0, 4.0 };
float ambiental[3] = { 1.0,1.0,1.0 };
static Vertice modelo1, modelo2,modelo3, obj[] = { modelo1,modelo2,modelo3 };
static Cara ob, ob1,ob2;
static Obj3D o3;
float foco[3];
static float var;
static float grados = 0.1;
static float cara[5][3];
static float res[4];
float Normal[3];
vector<float>::iterator iter, iter2, iter3, iter4;
vector<vector<double>>puntos { { 0, 0, 0.}, 
								{ 0.1, 0.01, 0 }, 
								{ -0.02, 0.01, 0 },
								{ 0, -0.02, -0.04 } };

float T[4][4] = { 1,   0,  0,  0,
							0,  1,  0,  0,
							0,  0,  1,  0,
							0,  0,  0,  1};
float X[4][4] = { 1,0,0,0,
					   0,cos(grados), -sin(grados), 0,
					   0, sin(grados), cos(grados), 0,
					   0, 0, 0, 1 };
float Y[4][4] = { cos(grados),0 ,sin(grados),0,
					   0,   1,  0,  0,
					   -sin(grados), 0, cos(grados), 0,
					   0, 0, 0, 1 };
float Z[4][4] = { cos(grados),-sin(grados),0,0,
					   sin(grados), cos(grados), 0,0,
					   0, 0, 1, 0,
					   0, 0, 0, 1 };

float x = 0, y = 0, t = 0,z=0;

void rotar(int i);



void rotar(int i)
{
	int contp = 0;
	for (iter = o3.objs[i].begin(), iter2 = o3.objs[i].begin() + 1, iter3 = o3.objs[i].begin() + 2; iter3 != o3.objs[i].end() - 1; ++iter, ++iter2, ++iter3) {
		//cout << (*iter) << " " << (*iter2) << " " << (*iter3) << endl;
		multmat(Y, *iter, *iter2, *iter3);
		*iter = res[0];
		*iter2 = res[1];
		*iter3 = res[2];
		iter += 2;
		iter2 += 2;
		iter3 += 2;
	}
}

void multmat(float mat[4][4], float iter, float iter2, float iter3)
{
	res[0] = mat[0][0] * iter +
		mat[0][1] * iter2 +
		mat[0][2] * iter3 +
		mat[0][3] * 1;

	res[1] = mat[1][0] * iter +
		mat[1][1] * iter2 +
		mat[1][2] * iter3 +
		mat[1][3] * 1;

	res[2] = mat[2][0] * iter +
		mat[2][1] * iter2 +
		mat[2][2] * iter3 +
		mat[2][3] * 1;

	res[3] = 1;
}

void bezier()
{
	T[0][3] = pow((1 - t), 3) * puntos[0][0] + 3 * t * pow((1 - t), 2) * puntos[1][0] + 3 * pow(t, 2) * puntos[2][0] * (1 - t) + pow(t, 3) * puntos[3][0];
	T[1][3] = pow((1 - t), 3) * puntos[0][1] + 3 * t * pow((1 - t), 2) * puntos[1][1] + 3 * pow(t, 2) * puntos[2][1] * (1 - t) + pow(t, 3) * puntos[3][1];
	T[2][3] = pow((1 - t), 3) * puntos[0][2] + 3 * t * pow((1 - t), 2) * puntos[1][2] + 3 * pow(t, 2) * puntos[2][2] * (1 - t) + pow(t, 3) * puntos[3][2];
	t = t + 0.01;
		for (iter = o3.objs[1].begin(), iter2 = o3.objs[1].begin() + 1, iter3 = o3.objs[1].begin() + 2; iter3 != o3.objs[1].end() - 1; ++iter, ++iter2, ++iter3) {

			multmat(T, *iter, *iter2, *iter3);
			*iter = res[0];
			*iter2 = res[1];
			*iter3 = res[2];
			iter += 2;
			iter2 += 2;
			iter3 += 2;
		}
}

void getNormal(int objeto, int cara)
{
	int scx, scy, scz;
	int a1=0,p=0,l;
	float cx, cy, cz,con=0;
	vector<float> a,b,todo, vert1, vert2, vert3;
	double aux[3], aux2[3], aux3[3], va[3],vb[3],puntoplano[3];
	vector<float>::iterator piter, piter2, piter3;	
	piter = o3.objs[objeto].begin()+2;
	float v1, v2, v3;
	a= obj[objeto].getfvd();
	b= obj[objeto].getvd();

			v1 = a.at(cara);
			v2 = a.at(cara + 1);
			v3 = a.at(cara + 2);
			cout << v1 << " " << v2 << " " << v3 << "\n" << endl;
			aux[0] = b.at(v1);
			aux[1] = b.at(v1 + 1);
			aux[2] = b.at(v1 + 2);

			aux2[0] = b.at(v2);
			aux2[1] = b.at(v2 + 1);
			aux2[2] = b.at(v2 + 2);

			aux3[0] = b.at(v3);
			aux3[1] = b.at(v3 + 1);
			aux3[2] = b.at(v3 + 2);


			va[0] = (aux2[0] - aux[0]);
			va[1] = (aux2[1] - aux[1]);
			va[2] = (aux2[2] - aux[2]);

			vb[0] = (aux3[0] - aux[0]);
			vb[1] = (aux3[1] - aux[1]);
			vb[2] = (aux3[2] - aux[2]);

			cx = va[1] * vb[2] - va[2] * vb[1];
			cy = va[2] * vb[0] - va[0] * vb[2];
			cz = va[0] * vb[1] - va[1] * vb[0];

			Normal[0] = cx;
			Normal[1] = cy;
			Normal[2] = cz;
			Normalizar(Normal);

			puntoplano[0] = (aux[0] + aux3[0] / 2);
			puntoplano[1] = (aux[1] + aux3[1] / 2);
			puntoplano[2] = (aux[2] + aux3[2] / 2);

			foco[0] = iluminacion[0] - puntoplano[0];
			cout << foco[0] << " ";
			foco[1] = iluminacion[1] - puntoplano[1];
			cout << foco[1] << " ";
			foco[2] = iluminacion[2] - puntoplano[2];
			cout << foco[2] << " " << endl;
	
}


void Normalizar(float arr[])
{
	float magnitud;
	magnitud = sqrt(pow(arr[0], 2) + pow(arr[1], 2) + pow(arr[2], 2));
	arr[0] = arr[0] / magnitud;
	arr[1] = arr[1] / magnitud;
	arr[2] = arr[2] / magnitud;
}


float productoPunto(float n[], float f[])
{
	float P;
	P = (n[0] * f[0] + n[1] * f[1] + n[2] * f[2]);
	return P;
}

float clamp(float punto, float upper, float lower)
{
	return min(upper, max(punto, lower));
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	float color1, color2, color3;
	float PP1, PP2, PP3;
	int carac1=0, carac2=0, carac3=0;
	for (int m = 0;m < 3;m++) {		
		int cont2 = 0;
		if (m == 1) {

			
			if (t < 1.2)
				bezier();
			
		}
		else if (m == 2) {
			//glColor3f(0.1, 0.3, 0.0);//piso
			getNormal(2, carac2);
			Normalizar(foco);
			PP2 = productoPunto(Normal, foco);
			PP2 = clamp(PP2, 1.0, 0.0);
			color1 = 0.1 * ambiental[0] * PP2;
			color2 = 0.3 * ambiental[1] * PP2;
			color3 = 0.0 * ambiental[2] * PP2;
			glColor3f(color1, color2, color3);
			
		}
		for (iter = o3.objs[m].begin(), iter2 = o3.objs[m].begin() + 1, iter3 = o3.objs[m].begin() + 2; iter3 != o3.objs[m].end() - 1; ++iter, ++iter2, ++iter3) 
		{
			glBegin(GL_POLYGON);		
			
			glVertex3f(*iter, *iter2, *iter3);

			//cout << *iter << "/ " << *iter2 << " " << *iter3 << endl;
			cont2++;
			
			if (cont2 == 4)
			{			
				glEnd();
				cont2 = 0;



				if (m == 0)
				{
					getNormal(0, carac3);
					Normalizar(foco);
					PP3 = productoPunto(Normal, foco);
					PP3 = clamp(PP3, 1.0, 0.0);
					color1 = 1.0 * ambiental[0] * PP3;
					color2 = 0.0 * ambiental[1] * PP3;
					color3 = 0.1 * ambiental[2] * PP3;
					glColor3f(color1, color2, color3);
				}
				if (m == 1)
				{
					getNormal(1, carac1);
					Normalizar(foco);
					PP1 = productoPunto(Normal, foco);
					PP1 = clamp(PP1, 1.0, 0.0);
					color1 = 0.5 * ambiental[0] * PP1;
					color2 = 0.0 * ambiental[1] * PP1;
					color3 = 1.0 * ambiental[2] * PP1;
					glColor3f(color1, color2, color3);//avion

				}

				carac1++;
				carac2++;
				carac3++;
			}
			iter += 2;iter2 += 2;iter3 += 2;			
		}
		carac1 = 0;
		carac2 = 0;
		carac3 = 0;
	}
	rotar(1);
	rotar(0);
	glutSwapBuffers();
	glFlush();
	grados = grados + 10;
}

void init(void)
{
	glClearColor(0.6, 0.6, 0.6, 0.7);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);
}

void specialKeys(int key, int x, int y) {

	if (key == GLUT_KEY_RIGHT)
		rotate_y += 5;
	else if (key == GLUT_KEY_LEFT)
		rotate_y -= 5;
	else if (key == GLUT_KEY_UP)
		rotate_x += 5;
	else if (key == GLUT_KEY_DOWN)
		rotate_x -= 5;
	else if (key == GLUT_KEY_F1)
	{ 
		ambiental[0]++;
		ambiental[1]++;
		ambiental[2]++;}
	else if (key == GLUT_KEY_F2)
	{
		ambiental[0]--;
		ambiental[1]--;
		ambiental[2]--; 
	}
	else if (key == GLUT_KEY_F3)
	{
		iluminacion[0]++;
		iluminacion[1]++;
		iluminacion[2]++;
	}
	else if (key == GLUT_KEY_F4)
	{
		iluminacion[0]--;
		iluminacion[1]--;
		iluminacion[2]--;
	}

	glutPostRedisplay();
	
}

int main(int argc, char** argv)
{
	obj[1].leervertice("avion.obj");
	obj[0].leervertice("bote.obj");
	obj[2].leervertice("piso.obj");
	o3.objs.push_back(ob.carga(obj[0]));
	o3.objs.push_back(ob1.carga(obj[1]));
	o3.objs.push_back(ob2.carga(obj[2]));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(450, 450);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("no tires basura");
	glutTimerFunc(100, update, 0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	init();
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);
	glutMainLoop();
	return 0;
}

void update(int) {
	if (grados > 10) {
		glutPostRedisplay();
		glutTimerFunc(50, update, 0);
	}
}



