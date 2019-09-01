#include "Escarabajo.h"
#include <GL/glut.h>
#include <cmath>
#include <iostream>

// Variable global a la instancia actual de CEscarabajo
CEscarabajo* g_pInstanciaActual;

extern "C"
void DrawCallback(){
	g_pInstanciaActual->Draw();
}

extern "C"
void MouseCallback(int nButton, int nState, int nMousex, int nMousey){
	g_pInstanciaActual->OnMouseClick(nButton, nState, nMousex, nMousey);
}

extern "C"
void KeyboardCallback(unsigned char key, int x, int y) {
	g_pInstanciaActual->OnKeyPress(key, x, y);
}

CEscarabajo::CEscarabajo()
{
	nAncho = 640;
	nAlto = 480;
	dDIVERGE = 4;   //valor de divergencia
	nITERMAX = 255; //iteracion maxima

	// Paleta de colores del fractal
	nPaletaR = 10;
	nPaletaG = 5;
	nPaletaB = 1;

	PlanoComplejo.xmin = -2;
	PlanoComplejo.xmax = 1;
	PlanoComplejo.ymin = -1.2;
	PlanoComplejo.ymax = 1.2;

	m_nIdWindow = 0;
}


CEscarabajo::~CEscarabajo()
{
}

void CEscarabajo::Mandelbrot() {

	unsigned int i, j;

	unsigned int iter = 0;

	double Cr_delta = (PlanoComplejo.xmax - PlanoComplejo.xmin) / double(nAncho);
	double Ci_delta = (PlanoComplejo.ymax - PlanoComplejo.ymin) / double(nAlto);

	double Cr;
	double Ci = PlanoComplejo.ymax;

	//PROCESO DE DIAGRAMADO
	glBegin(GL_POINTS); // Inicia dibujado
	for (j = 0; j < nAlto; j++) {

		Cr = PlanoComplejo.xmin;

		for (i = 0; i < nAncho; i++) {

			// Algoritmo usando operaciones entre números reales     

			double Zr = 0;
			double Zi = 0;
			double Tr = 0;
			double Ti = 0;
			unsigned int nITERACION = 0;

			for (; nITERACION < nITERMAX && (Tr + Ti) <= dDIVERGE; ++nITERACION) {
				Zi = 2 * Zr * Zi + Ci;
				Zr = Tr - Ti + Cr;
				Tr = Zr * Zr;
				Ti = Zi * Zi;
			}

			if (nITERACION != nITERMAX) {
				unsigned int nColor = nITERACION + 50;

				float r = float((nPaletaR * (nColor + 1)) % 256) / 256;
				float g = float((nPaletaG * (nColor + 1)) % 256) / 256;
				float b = float((nPaletaB * (nColor + 1)) % 256) / 256;

				glColor3f(r, g, b);
				glVertex2i(i, j);
			}
			else {
				glColor3f(0, 0, 0);
				glVertex2i(i, j);
			}

			Cr += Cr_delta;

		}

		Ci -= Ci_delta;
	}
	glEnd();// Fin de dibujado
	
}

void CEscarabajo::Zoom(double x1, double y1, double x2, double y2) {

	double xmed = 0.5*(x2 + x1);
	double ymed = 0.5*(y2 + y1);

	double Lx = 0.5*std::fabs(x2 - x1); // mitad del ancho del rectangulo de seleccion
	double Ly = double(nAlto) * Lx / double(nAncho);

	double  ex = (PlanoComplejo.xmax - PlanoComplejo.xmin) / double(nAncho);//escalax
	double  ey = (PlanoComplejo.ymax - PlanoComplejo.ymin) / double(nAlto);//escalay

	PlanoComplejo.xmin = PlanoComplejo.xmin + (xmed - Lx) * ex;
	PlanoComplejo.ymax = PlanoComplejo.ymax - (ymed - Ly) * ey;
	PlanoComplejo.xmax = PlanoComplejo.xmin + 2 * Lx * ex;
	PlanoComplejo.ymin = PlanoComplejo.ymax - 2 * Ly * ey;


}
void CEscarabajo::Draw(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const int width = glutGet(GLUT_WINDOW_WIDTH);
	const int height = glutGet(GLUT_WINDOW_HEIGHT);
	glOrtho(0, width, 0, height, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Diagrama el fractal
	Mandelbrot();

	glutSwapBuffers();
}

void CEscarabajo::OnMouseClick(int nButton, int nState, int nMousex, int nMousey) {

	double dSemiAnchoZoom, dSemiAltoZoom;

	if (nButton == GLUT_LEFT_BUTTON && nState == GLUT_DOWN) // Click izquierdo
	{	

		dSemiAnchoZoom = double(nAncho)*0.25;
		dSemiAltoZoom = double(nAlto)*0.25;
		Zoom(nMousex - dSemiAnchoZoom, (nAlto - nMousey) - dSemiAltoZoom, nMousex + dSemiAnchoZoom, (nAlto - nMousey) + dSemiAltoZoom);
	
	}else if (nButton == GLUT_RIGHT_BUTTON && nState == GLUT_DOWN) { // Click derecho
		

		dSemiAnchoZoom = double(nAncho);
		dSemiAltoZoom = double(nAlto);

		Zoom(nMousex - dSemiAnchoZoom, (nAlto - nMousey) - dSemiAltoZoom, nMousex + dSemiAnchoZoom, (nAlto - nMousey) + dSemiAltoZoom);
	}

	glutPostRedisplay();
}

void CEscarabajo::OnKeyPress(unsigned char key, int x, int) {

	switch (key)
	{
	case 13: // Tecla ENTER
	case 27: // Tecla Escape
		glutDestroyWindow(m_nIdWindow);		
		exit(0);		
		break;
	}
}

void CEscarabajo::Display(void)
{
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(nAncho, nAlto);
	m_nIdWindow = glutCreateWindow("Mandelbrot");
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	setupCallback();
	glutMainLoop();
}

void CEscarabajo::setupCallback()
{
	::g_pInstanciaActual = this;
	::glutDisplayFunc(::DrawCallback);
	::glutMouseFunc(::MouseCallback);
	::glutKeyboardFunc(::KeyboardCallback);
}
